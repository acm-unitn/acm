#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define MAX_N 100
#define MAX_R 30
#define MAX_M 10000
//#define DEBUG
#ifdef DEBUG
#define print(...) fprintf(stderr, __VA_ARGS__)
#else
#define print(...)
#endif

struct node {
  bool open;
  int dist;
  vector<int> adjs;
};

int n;
vector<node> graph;
long double mem[MAX_N+1][MAX_M+1];
int couples[1000][3];

int bfs(int start_node, int end_node)
{
  int node;
  queue<int> q;
  for (int i=0; i<n; i++)
    graph[i].open = true;
  graph[end_node].dist = -1;
  graph[start_node].open = false;
  graph[start_node].dist = 0;
  q.push(start_node);
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
          graph[adj].dist = graph[node].dist +1;
          if (adj == end_node)
            return graph[adj].dist;
          print("node %d distanza %d\n",adj,graph[adj].dist);
          q.push(adj);
        }
    }
  }
  return 0;
}

int main()
{
  char c;
  int t, dist, r, max_m, co;
  scanf("%d",&t);
  for (int z=0; z<t; z++)
  {
    scanf("%d",&n);
    scanf("%d\n",&r);
    graph.erase(graph.begin(),graph.end());
    graph.resize(n);
    for (int i=0; i<n; i++)
    {
      for (int j=0; j<n; j++)
      {
        scanf("%c",&c);
        if (c=='Y')
        {
          graph[i].adjs.push_back(j);
        }
      }
      scanf("\n");
    }
    printf("Case %d\n",z+1);
    /*
    for (int i=0; i<n; i++)
    {
      printf("Nodo %d\n",i);
      for (int j=0; j<(int)graph[i].adjs.size(); j++)
        printf("%d ",graph[i].adjs[j]);
      printf("\n");
      }*/
    scanf("%d",&co);
    max_m = 0;
    for (int i=0; i<co; i++)
    {
      scanf("%d %d %d\n",&(couples[i][0]),&(couples[i][1]),&(couples[i][2]));
      couples[i][0]--;
      couples[i][1]--;
      if (couples[i][2]>max_m)
        max_m = couples[i][2];
    }
    for (int j=0; j<=max_m; j++)
      mem[0][j] = 1;
    for (int i=1; i<=n; i++)
    {
      for (int j=0; j<=max_m; j++)
      {
        mem[i][j] = 0;
        for (int k=1; k<=min(r,j); k++)
          mem[i][j] += mem[i-1][j-k];
        mem[i][j] /= (long double)r;
      }
    }
    for (int i=0; i<co; i++)
    {
      dist = bfs(couples[i][0],couples[i][1]);
      print("coppia %d %d budget %d dist %d\n",couples[i][0],couples[i][1]
             ,couples[i][2],dist);
      printf("%Lf\n",mem[dist][couples[i][2]]);
    }
    printf("\n");
  }
  return 0;
}
