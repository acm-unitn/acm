#include <cstdio>
#include <vector>
#include <utility>
#include <queue>
#include <vector>


#ifdef DEBUG
#define print(...) fprintf(stderr, __VA_ARGS__)
#else
#define print(...)
#endif

#define uint unsigned int
#define lint long long int

using namespace std;

struct node {
  vector <int> adjs;
  vector <lint> weights;
  bool open;

  void add_adj(int id, lint weight) {
    this->adjs.push_back(id);
    this->weights.push_back(weight);
  }
};

vector<node> graph;

lint max_global = 0;

lint dfs(int node) {
  int adj;
  lint res = 0;
  lint tmp;
  if (graph[node].open) {
    graph[node].open = false;
    // visiting code
    for (uint i=0; i<graph[node].adjs.size(); i++)
    {
      adj = graph[node].adjs[i];
      print("Visiting node %d, child %d\n", node, adj);
      if(! graph[adj].open)
	continue; // needed, or I will find my parent between my children
      tmp = dfs(adj) + graph[node].weights[i];
      if (tmp > 0)
	res += tmp;
      print(" - tmp = %d, res = %lld\n", tmp, res);
    }
    if (res > max_global)
      max_global = res;
    return res;
  }
  else {
    // does not affect max
    return 0;
  }
}

void full_dfs(){
  for (uint i=0; i<graph.size(); i++)
    graph[i].open = true;
  
  for (uint i=0; i<graph.size(); i++) {
    dfs(i);
  }
  printf("%lli\n", max_global);
}

int remap_inv[200001];

int main()
{
  int n, m;
  int a, b;
  lint w;
  
  while (true) {
    n = 0;
    max_global = 0;
    scanf("%d",&m);
    if (m == 0){
      break;
    }
    for(int i=0; i<200001; i++)
      remap_inv[i] = -1;
    graph.erase(graph.begin(),graph.end());
    //graph.resize(n);

    for (int i=0; i<m; i++) {
      scanf("%d %d %lld",&a,&b,&w);

      if (remap_inv[a] == -1){
	remap_inv[a] = n;
	n++;
	graph.resize(n);
      }
      if (remap_inv[b] == -1){
	remap_inv[b] = n;
	n++;
	graph.resize(n);
      }
      a = remap_inv[a];
      b = remap_inv[b];

      graph[a].add_adj(b,w);
      graph[b].add_adj(a,w);
    }

    full_dfs();
  
  }
  return 0;
}
