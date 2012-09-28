#include <cstdio>
#include <vector>
#include <utility>
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
  vector <int> adjs;
  vector <int> weights;
  bool open;

  void add_adj(int id, int weight) {
    this->adjs.push_back(id);
    this->weights.push_back(weight);
  }
};

vector<node> graph;

void dfs(int node)
// Only visits graph from here. Will not see unreachable nodes!
{
  int adj;
  if (graph[node].open)
  {
    graph[node].open = false;
    // visiting code
    print("Visiting node %d\n", node);
    for (uint i=0; i<graph[node].adjs.size(); i++)
    {
      adj = graph[node].adjs[i];
      dfs(adj);
    }
  }
}

void bfs(int start_node)
// Only visits graph from here. Will not see unreachable nodes!
{
  int node;
  queue<int> q;
  if (graph[start_node].open)
  {
    graph[start_node].open = false;
    q.push(start_node);
  }
  while(!q.empty())
  {
    node = q.front();
    q.pop();
    // visiting code
    print("Visiting node %d\n", node);
    for (uint i=0; i<graph[node].adjs.size(); i++)
    {
        int adj = graph[node].adjs[i];
        if (graph[adj].open)
        {
          graph[adj].open = false;
          q.push(adj);
        }
    }
  }
}

void full_dfs(){
  //dfs call
  for (uint i=0; i<graph.size(); i++)
    graph[i].open = true;
  print("DFS\n");
  for (uint i=0; i<graph.size(); i++)
    dfs(i);
}

void full_bfs(){
  // bfs call
  for (uint i=0; i<graph.size(); i++)
    graph[i].open = true;
  print("BFS\n");
  for (uint i=0; i<graph.size(); i++)
    bfs(i);
}


int main()
{
  bool archi=true; // da non copiare
  int n, m;
  int a,b,w;

  scanf("%d",&n);
  graph.erase(graph.begin(),graph.end());
  graph.resize(n);
  if (archi) //parsa input con archi
  {
    scanf("%d",&m);
    for (int i=0; i<m; i++)
    {
      scanf("%d %d %d",&a,&b,&w);
      graph[a].add_adj(b,w);
    }
  }
  else //parsa input con matrice di 0 1
  {
    for (int i=0; i<n; i++)
    {
      for (int j=0; j<n; j++)
      {
        scanf("%d",&w);
        if (w!=-1) //-1 null value
          graph[i].add_adj(j,w);
      }
      //scanf("\n"); // serve se scansiono con %c
    }
  }
  print("GRAPH:\n");
  for (int i=0; i<n; i++)
  {
    print("Neighbour node %d\n",i);
    for (uint j=0; j< graph[i].adjs.size(); j++)
      print("(%d,%d) ",graph[i].adjs[j],graph[i].weights[j]);
    print("\n");
  }

  full_dfs();
  full_bfs();

  return 0;
}
