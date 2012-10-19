#include <cassert>
#include <stack>
#include <queue>
#include <vector>
#include <stdio.h>

using namespace std;

#define DEBUG
#ifdef DEBUG
#define print(...) fprintf(stderr, __VA_ARGS__)
#else
#define print(...)
#endif

#define uint unsigned int
#define MAX_N 1000

struct node {
  vector <int> adjs;
  vector <int> weights;
  bool open;

  void add_adj(int id, int weight) {
    this->adjs.push_back(id);
    this->weights.push_back(weight);
  }
};

int n;
vector<node> graph;
int weights[MAX_N][MAX_N];

int bfs_walk(int source, int dest, stack<int>* path)
// true if dest is reachable
// if true, path is erased and properly filled
{
  bool finished = false;
  int node, min;
  int previous[MAX_N];
  queue<int> q;
  for (int i=0; i<n; i++)
    graph[i].open = true;
  graph[source].open = false;
  previous[source] = -1;
  q.push(source);
  while(!q.empty() && !finished)
  {
    node = q.front();
    q.pop();
    print("Visiting node %d\n", node);
    for (uint i=0; i<graph[node].adjs.size() && !finished; i++)
    {
      int adj = graph[node].adjs[i];
      assert(weights[node][adj] >= 0);
      if (weights[node][adj] != 0) { // NB even if adj is here, this does not
                                    // mean the edge actually exists
        if (graph[adj].open)
        {
          graph[adj].open = false;
          previous[adj] = node;
          q.push(adj);
          if (adj==dest)
            finished = true;
        }
      }
    }
  }
  if (finished) {
    min = weights[previous[dest]][dest];
    node = dest;
    while (node != source) {
      path->push(node);
      if (weights[previous[node]][node] < min)
        min = weights[previous[node]][node];
      node = previous[node];
    }
    path->push(source);
    return min;
  }
  return 0;
}

int max_flow(int source, int sink)
{
  stack<int> s;
  int prev, next, val, flow;
  while((val=bfs_walk(source,sink,&s)) > 0)
  {
    prev = s.top();
    s.pop();
    while(!s.empty())
    {
      next = s.top();
      s.pop();
      weights[prev][next] -= val;
      //se l'arco all'indietro non esiste ancora lo aggiungo
      if (weights[next][prev] == 0)
        graph[next].add_adj(prev,0);
      weights[next][prev] += val;
      prev = next;
    }
  }
  // compute max flow, basing on weight of newly-created edges
  // towards the source in the residual capacity graph
  flow = 0;
  for (uint i=0; i<graph[source].adjs.size(); i++)
  {
    int adj = graph[source].adjs[i];
    flow += weights[adj][source];
  }
  return flow;
}

int main()
{
  int w;
  int flusso;

  scanf("%d",&n);
  graph.erase(graph.begin(),graph.end());
  graph.resize(n);
  for (int i=0; i<n; i++)
  {
    for (int j=0; j<n; j++)
    {
      scanf("%d",&w);
      weights[i][j] = w;
      if (w != 0)
        graph[i].add_adj(j, w);
    }
  }
  print("GRAPH:\n");
  for (int i=0; i<n; i++)
  {
    print("Neighbour node %d\n",i);
    for (int j=0; j< n; j++)
      print("%d ",weights[i][j]);
    print("\n");
  }

  flusso = max_flow(0, n-1);
  printf("Flusso massimo %d\n",flusso);

  return 0;
}
