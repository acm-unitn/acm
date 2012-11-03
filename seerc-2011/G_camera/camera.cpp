#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>

#define left(n) ((n+1)*2-1)
#define right(n) ((n+1)*2)


#define MAX_N 100000

using namespace std;

bool outdated[MAX_N];

struct point {
  int x, y, index, price;

  point(int x, int y) {
    this->x = x;
    this->y = y;
  }

  point(int x, int y, int price, int index) {
    this->x = x;
    this->y = y;
    this->index = index;
    this->price = price;
  }

  point() {}
};

bool by_x(const point& a, const point& b)
{
	return a.x < b.x;
}

bool by_y(const point& a, const point& b)
{
	return a.y < b.y;
}

bool by_price(const point& a, const point& b)
{
	return a.price > b.price;
}

struct node {
  //intervallo (l,r) ricoperto sull'asse x
  int l, r;
  //punti ordinati secondo asse y
  vector<point> points;
  bool leave;
};


class range_tree {
  vector<node*> tree;

  void build_node(int l, int r, point* points, int pos) {
    node* nodo = new node();

    nodo->l = points[l].x;
    nodo->r = points[r].x;
    if (nodo->l == nodo->r)
    {
      nodo->leave = true;
      for (int i=l; i<=r; i++)
        nodo->points.push_back(points[i]);
      sort(nodo->points.begin(),nodo->points.end(),by_y);
    }
    else
    {
      nodo->leave = false;
      int m = (l+r)/2;
      build_node(l,m,points,left(pos));
      build_node(m+1,r,points,right(pos));
      nodo->points.resize(tree[left(pos)]->points.size()+
                          tree[right(pos)]->points.size());
      merge(tree[left(pos)]->points.begin(),
            tree[left(pos)]->points.end(),
            tree[right(pos)]->points.begin(),
            tree[right(pos)]->points.end(),
            nodo->points.begin(),
            by_y);
    }
    if ((int) tree.size() < pos+1)
      tree.resize(pos+2);
    tree[pos] = nodo;
  }

  void find_recursive(int pos, int x1, int x2, int y1, int y2, vector<point>* output){
    node* nodo = tree[pos];
    //se l'intervallo del nodo è contenuto nell'intervallo cercato
    //predi tutti
    if (nodo->l >= x1 &&  nodo->r <= x2) {
      vector<point>::iterator a = lower_bound(nodo->points.begin(),
                                              nodo->points.end(),
                                              point(0,y1),
                                              by_y);
      vector<point>::iterator b = upper_bound(nodo->points.begin(),
                                              nodo->points.end(),
                                              point(0,y2),
                                              by_y) --;
      while (a!=b) {
        if (!outdated[a->index])
            output->push_back(*a);
        a++;
      }
    }
    //se l'intervallo del nodo interseca l'intervallo cercato
    //cerca nel figlio destro e nel sinistro
    else if (nodo->l <= x2 && x1 <= nodo->r) {
      find_recursive(left(pos),x1,x2,y1,y2,output);
      find_recursive(right(pos),x1,x2,y1,y2,output);
    }
    //se sono disgiunti non fai niente
  }

public:
  //points array di punti, n numero di punti
  range_tree(point* points, int n) {
    sort(points,points+n,by_x);
    tree.resize(n);
    build_node(0,n-1,points,0);
  }

  ~range_tree() {
    for (unsigned int i=0; i<tree.size(); i++)
      delete tree[i];
    tree.erase(tree.begin(),tree.end());
  }

  void find(int x1, int x2, int y1, int y2, vector<point>* output) {
    find_recursive(0,x1,x2,y1,y2,output);
  }

  void print(int pos, int lev) {
    if (tree[pos]->leave) {
      for (int i=0; i<lev; i++) printf("   ");
      printf("Intervallo %d %d -> ",tree[pos]->l,tree[pos]->r);
      for (int i=0; i<(int)tree[pos]->points.size();i++)
        printf(" (%d,%d)",tree[pos]->points[i].x,tree[pos]->points[i].y);
      printf("\n");
    }
    else {
      print(left(pos),lev+1);
      for (int i=0; i<lev; i++) printf("   ");
      printf("Intervallo %d %d -> ",tree[pos]->l,tree[pos]->r);
      for (int i=0; i<(int)tree[pos]->points.size();i++)
        printf(" (%d,%d)",tree[pos]->points[i].x,tree[pos]->points[i].y);
      printf("\n");
      print(right(pos),lev+1);
    }
  }
};

int n, m;
int dati[MAX_N][4];
point macchine[MAX_N];
priority_queue<point, vector<point>, bool(*)(const point&,const point&)> q(&by_price);

int main()
{
  double ratio;
  bool primo;
  range_tree* rt;
  int t, x, y, price, minx, miny;
  char c;
  vector<point> output;
  scanf("%d\n",&t);
  for (int k=0; k<t; k++)
  {
    //printf("Caso %d\n",k);
    scanf("%d\n",&n);
    m = 0;
    miny=minx = INT_MAX;
    for (int i=0; i<n; i++)
    {
      scanf("%c",&c);
      if (c=='P')
      {
        scanf("%d %lf %d\n",&x,&ratio,&price);
        y = (int) (ratio * 1000000.0);
        dati[i][0] = 1;
        dati[i][1] = x;
        if (x<minx)
          minx=x;
        dati[i][2] = y;
        if (y<miny)
          miny=y;
        dati[i][3] = price;
        macchine[m].x = x;
        macchine[m].y = y;
        macchine[m].index = i;
        m++;
      }
      else
      {
        scanf("\n");
        dati[i][0] = 0;
      }
    }
    rt = new range_tree(macchine,m);
    //rt->print(0,0);
    for (int i=0; i<n; i++)
      outdated[i] = false;
    primo = true;
    for (int i=0; i<n; i++)
    {
      //printf("riga %d\n",i);
      if (dati[i][0] == 1)
      {
        //printf("%d,%d\n",dati[i][1],dati[i][2]);
        if (!outdated[i])
        {
          output.erase(output.begin(),output.end());
          rt->find(minx,dati[i][1],miny,dati[i][2],&output);
          for (int j=0; j<(int)output.size(); j++)
          {
            if (output[j].x < dati[i][1] || output[j].y < dati[i][2])
            {
              //printf("outdated: %d (%d,%d)\n",output[j].index,output[j].x,output[j].y);
              outdated[output[j].index] = true;
            }
          }
          while (!q.empty() && outdated[q.top().index])
            q.pop();
          q.push(point(dati[i][1],dati[i][2],dati[i][3],i));
        }
        //printf("scelta: %d (%d,%d)\n",q.top().index,q.top().x,q.top().y);
      }
      else
      {
        if (!primo)
          printf(" ");
        primo = false;
        if (q.empty())
          printf("-1");
        else
          printf("%d",q.top().index+1);
      }
    }
    printf("\n");
    while (!q.empty())
      q.pop();
  }
  return 0;
}
