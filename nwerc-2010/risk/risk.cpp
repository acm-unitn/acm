#include <cstdio>
#include <vector>
#include <climits>
#include <stack>
#include <queue>
#include <cassert>

#define MAX_N 101
#define NODES MAX_N*2+2
#define uint unsigned int

#define DEBUG
#ifdef DEBUG
#define print(...) fprintf(stdout, __VA_ARGS__)
#else
#define print(...)
#endif

using namespace std;

struct node {
  vector <int> adjs;
  vector <int> weights;
  bool open;

  void add_adj(int id, int weight) {
    this->adjs.push_back(id);
    this->weights.push_back(weight);
  }
};

int n, nodes, s, p, n_confine;
vector<node> graph;
int weights[NODES][NODES];
bool enemy[MAX_N];
bool confine[MAX_N];

int bfs_walk(int source, int dest, stack<int>* path)
// true if dest is reachable
// if true, path is erased and properly filled
{
  bool finished = false;
  int node, min;
  int previous[NODES];
  queue<int> q;
  for (int i=0; i<nodes; i++)
    graph[i].open = true;
  graph[source].open = false;
  previous[source] = -1;
  q.push(source);
  while(!q.empty() && !finished)
  {
    node = q.front();
    q.pop();
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

int binary_search(int a, int b)
{
  int alfa, flusso;
  alfa = (a+b) / 2;
  alfa+= ((a+b)%2==0) ? 0 : 1;

  if (a==b)
    return a + 1;

  for (int i=0; i<n; i++)
  {
    if (confine[i])
    {
      if (graph[i].adjs.back() != p)
        graph[i].add_adj(p,alfa);
      weights[i][p] = alfa;
    }
  }

  flusso = max_flow(s, p);

  for (int i=0; i<nodes; i++)
    for (int j=0; j<(int)graph[i].adjs.size(); j++)
      weights[i][graph[i].adjs[j]] = graph[i].weights[j];

  if (flusso < n_confine*alfa)
    return binary_search(a,alfa-1);
  else
    return binary_search(alfa,b);
}


int main()
{
  int t, a, tot_arm, res;
  char c;
  scanf("%d\n",&t);
  for (int k=0; k<t; k++)
  {
    scanf("%d\n",&n);
    nodes = n*2+2;
    s = n*2;
    p = n*2+1;
    n_confine = 0;
    graph.erase(graph.begin(),graph.end());
    graph.resize(nodes);
    for (int i=0; i<n; i++)
    {
      enemy[i] = false;
      confine[i] = false;
    }
    for (int i=0; i<nodes; i++)
      for (int j=0; j<nodes; j++)
        weights[i][j] = 0;
    tot_arm = 0;
    for (int i=0; i<n; i++)
    {
      scanf("%d",&a);
      tot_arm += a;
      if (a==0)
      {
        enemy[i] = true;
      }
      else
      {
        weights[i][i+n] = a;
        graph[i].add_adj(i+n, a);
      }
    }
    scanf("\n");
    for (int i=0; i<n; i++)
    {
      for (int j=0; j<n; j++)
      {
        scanf("%c",&c);
        if (c=='Y')
        {
          if (!enemy[i])
          {
            if (enemy[j])
            {
              if (!confine[i])
                n_confine++;
              confine[i] = true;
            }
            else
            {
              weights[i+n][j] = weights[i][i+n];
              graph[i+n].add_adj(j, weights[i][i+n]);
            }
          }
        }
      }
      scanf("\n");
    }
    for (int i=0; i<n; i++)
    {
      if (!enemy[i])
      {
        weights[s][i] = weights[i][i+n] - 1;
        graph[s].add_adj(i,weights[i][i+n] - 1);
      }
    }
    res = binary_search(0,tot_arm/n_confine);
    printf("%d\n",res);
  }
  return 0;
}
