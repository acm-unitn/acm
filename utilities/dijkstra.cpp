#include <cstdio>
#include <vector>
#include <queue>

#define DEBUG
#ifdef DEBUG
#define print(...) fprintf(stderr, __VA_ARGS__)
#else
#define print(...)
#endif

#define uint unsigned int

using namespace std;

struct node {
  int id;
  int dist;
  int previous;
  bool closed;

  vector <int> adjs;
  vector <int> weights;

  void add_adj(int id, int weight) {
    this->adjs.push_back(id);
    this->weights.push_back(weight);
  }

  int operator() (const node* a, const node* b) {
    return a->dist > b->dist;
  }
};

int n;
priority_queue<node*,vector<node*>,node> q;
vector<node> graph;

void dijkstra(int source)
{
  int alt;
  for (int i=0; i<n; i++)
  {
    graph[i].id = i;
    graph[i].dist = -1;
    graph[i].previous = -1;
    graph[i].closed = false;
  }
  graph[source].dist = 0;
  q.push(&graph[source]);
  while (!q.empty())
  {
    node* u = q.top();
    q.pop();
    if (!u->closed)
    {
      u->closed = true;
      for (uint i=0; i<u->adjs.size(); i++)
      {
        int adj = u->adjs[i];
        alt = u->dist + u->weights[i];
        if (alt < graph[adj].dist || graph[adj].dist == -1)
        {
          graph[adj].dist = alt;
          graph[adj].previous = u->id;
          q.push(&graph[adj]);
        }
      }
    }
  }
}

int main()
{
  int m;
  int a,b,w;

  scanf("%d",&n);
  graph.erase(graph.begin(),graph.end());
  graph.resize(n);
  scanf("%d",&m);
  for (int i=0; i<m; i++)
  {
    scanf("%d %d %d",&a,&b,&w);
    graph[a].add_adj(b,w);
    graph[b].add_adj(a,w);
  }
  print("GRAPH:\n");
  for (int i=0; i<n; i++)
  {
    print("Neighbour node %d\n",i);
    for (uint j=0; j< graph[i].adjs.size(); j++)
      print("(%d,%d) ",graph[i].adjs[j],graph[i].weights[j]);
    print("\n");
  }
  dijkstra(0);
  for (int i=0; i<n; i++)
    printf("nodo %d distanza %d\n",i,graph[i].dist);
  return 0;
}
