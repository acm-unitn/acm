#include <cstdio>
#include <vector>

using namespace std;

struct node {
  int parent;
  int rank;
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

using namespace std;
vector<node> graph;

int main()
{
  int a,b,n,choice;
  mfset *m;
  printf("Number of nodes?\n");
  scanf("%d",&n);
  graph.resize(n);
  m = new mfset(&graph);
  while (true)
  {
    printf("1 -> merge\n2 -> find\n");
    scanf("%d",&choice);
    if (choice==1)
    {
      printf("elementi da mergiare?\n");
      scanf("%d %d",&a,&b);
      m->merge(a,b);
    }
    else
    {
      printf("elemento di cui cercare rappresentatnte?\n");
      scanf("%d",&a);
      b = m->find(a);
      printf("è %d\n",b);
    }
  }
  return 0;
}
