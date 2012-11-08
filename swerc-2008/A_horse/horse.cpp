#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct node {
  int parent;
  int rank;
  vector<int> vicini;
  vector<int> pesi;
};

#define uint unsigned int
struct mfset {
  vector<node> *nodes;

  mfset(vector<node> *nodes) {
    this->nodes = nodes;
    for (uint i=0; i<nodes->size(); i++)
    {
      (*this->nodes)[i].parent = i;
      (*this->nodes)[i].rank = 0;
    }
  }

  int find(int x) {
    if ((*nodes)[x].parent != x)
      (*nodes)[x].parent = this->find((*nodes)[x].parent);
    return (*nodes)[x].parent;
  }

  void merge(int x, int y) {
    int xRoot = this->find(x);
    int yRoot = this->find(y);
    if (xRoot == yRoot)
      return;

    if ((*nodes)[xRoot].rank < (*nodes)[yRoot].rank)
      (*nodes)[xRoot].parent = yRoot;
    else if ((*nodes)[xRoot].rank > (*nodes)[yRoot].rank)
      (*nodes)[yRoot].parent = xRoot;
    else
    {
      (*nodes)[yRoot].parent = xRoot;
      (*nodes)[xRoot].rank = (*nodes)[xRoot].rank + 1;
    }
  }
};

struct edge {
  int a, b, peso;
};

bool operator<(const edge& a, const edge& b) {
  return a.peso<b.peso;
}

#define MAX_Q 1000

int n, m, q;
vector<node> graph;
vector<edge> edges;
int query[MAX_Q][3];

//#define DEBUG
#ifdef DEBUG
#define print(...) fprintf(stdout, __VA_ARGS__)
#else
#define print(...)
#endif

void solve()
{
  int collegati = 0;
  mfset *mf = new mfset(&graph);
  for (int i=0; i<m && collegati<q; i++)
  {
    print("estraggo arco %d %d %d\n",edges[i].a,edges[i].b,edges[i].peso);
    mf->merge(edges[i].a,edges[i].b);
    for (int j=0; j<q; j++)
    {
      if (query[j][2]==-1)
      {
        if (mf->find(query[j][0])==mf->find(query[j][1]))
        {
          print("%d e %d sono stati collegati, peso %d\n",query[j][0],
                query[j][1],
                edges[i].peso);
          collegati++;
          query[j][2] = edges[i].peso;
        }
      }
    }
  }
}

int main()
{
  int t, a, b, p;
  scanf("%d",&t);
  for (int k=0; k<t; k++)
  {
    scanf("%d %d",&n,&m);
    graph.erase(graph.begin(),graph.end());
    graph.resize(n);
    edges.resize(m);
    for (int i=0; i<m; i++)
    {
      scanf("%d %d %d",&a,&b,&p);
      a -= 1;
      b -= 1;
      edges[i].a = a;
      edges[i].b = b;
      edges[i].peso = p;
      graph[a].vicini.push_back(b);
      graph[a].pesi.push_back(p);
      graph[b].vicini.push_back(a);
      graph[b].pesi.push_back(p);
    }
    scanf("%d",&q);
    for (int i=0; i<q; i++)
    {
      scanf("%d %d",&a,&b);
      a -= 1;
      b -= 1;
      query[i][0] = a;
      query[i][1] = b;
      query[i][2] = -1;
    }
    sort(edges.begin(),edges.end());
    solve();
    printf("Case %d\n",k+1);
    for (int i=0; i<q; i++)
      printf("%d\n",query[i][2]);
  }
  return 0;
}
