#include <cstdio>
#include <climits>
#include <vector>
using namespace std;

struct node {
  long long int dist;
  int pred;
  bool flag;
  int id;
};

struct edge {
  int x;
  int y;
  int w;
};

#define MAX_M 9000000

vector<node> nodes;
edge edges[MAX_M];
int e, v;

bool BellmanFord(int start) {
  for (int i = 0; i < v; i++) {
    if (i == start)
      nodes[i].dist = 0;
    else
      nodes[i].dist = INT_MAX;
    nodes[i].pred = -1;
    nodes[i].id = i;
  }

  for (int i = 0; i < v-1; i++)
  {
    for (int j = 0; j < e; j++) {
      if (nodes[edges[j].y].dist > nodes[edges[j].x].dist + edges[j].w) {
        nodes[edges[j].y].dist = nodes[edges[j].x].dist + edges[j].w;
        nodes[edges[j].y].pred = edges[j].x;
      }
    }
  }

  for (int j = 0; j < e; j++)
    if (nodes[edges[j].y].dist > nodes[edges[j].x].dist + edges[j].w)
      return false;

  return true;
}

int main() {
  int x, y, w;
  scanf("%d %d",&v, &e);
  nodes.resize(v);
  for (int i = 0; i < e; i++) {
    scanf("%d %d %d",&x,&y,&w);
    x--;
    y--;
    edges[i].x = x;
    edges[i].y = y;
    edges[i].w = w;
  }

  if (BellmanFord(0)) {
    printf("%lld\n",nodes[v-1].dist);
  }
  else
    printf("ERRORE! C'e` un ciclo negativo\n");
  node* s = &nodes[v-1];
  while (s->pred != -1)
  {
    printf("%d ",s->id);
    s = &nodes[s->pred];
  }
  printf("\n");
  return 0;
}
