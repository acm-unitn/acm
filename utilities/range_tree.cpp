#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <time.h>

#define left(n) ((n+1)*2-1)
#define right(n) ((n+1)*2)

using namespace std;

struct point {
  int x, y;

  point(int x, int y) {
    this->x = x;
    this->y = y;
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

range_tree* rt;

#define N 30

int main()
{
  int a, b, c, d, t;
  point points[N];
  vector<point> output;
  srand ( time(NULL) );
  while (true)
  {
    printf("point\n");
    for (int i=0; i<N; i++)
    {
      points[i].x = rand() % 20 -10;
      points[i].y = rand() % 20 -10;
      printf ("(%d,%d) ",points[i].x,points[i].y);
    }
    printf("\n");
    rt = new range_tree(points,N);
    //rt->print(0,0);
    a = rand()%20-10; b = rand()%20-10;
    if (a>b) {t=a; a=b; b=t;}
    c = rand()%20-10; d = rand()%20-10;
    if (c>d) {t=c; c=d; d=t;}
    printf("search [%d,%d]x[%d,%d]\n",a,b,c,d);
    rt->find(a,b,c,d,&output);
    printf("result:\n");
    for (int i=0; i<(int)output.size(); i++)
      printf("(%d,%d) ",output[i].x,output[i].y);
    printf("\n");
    delete rt;
    output.erase(output.begin(),output.end());
    getchar();
  }
  return 0;
}
