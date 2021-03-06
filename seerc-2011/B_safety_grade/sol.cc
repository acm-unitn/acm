#include <cstdio>
#include <stack>
#include <queue>
#include <vector>
#include <cassert>
#include <algorithm>

//#define DEBUG
#ifdef DEBUG
#define print(...) fprintf(stdout, __VA_ARGS__); fflush(stdout)
#else
#define print(...)
#endif

#define uint unsigned int
#define MAX_N 100

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
  print("Visita:\n");
  while((val=bfs_walk(source,sink,&s)) > 0)
  {
    print("Cammino aumentante di %d\n",val);
    prev = s.top();
    print("%d ",prev);
    s.pop();
    while(!s.empty())
    {
      next = s.top();
      print("%d ",next);
      s.pop();
      weights[prev][next] -= val;
      //se l'arco all'indietro non esiste ancora lo aggiungo
      if (weights[next][prev] == 0)
        graph[next].add_adj(prev,0);
      weights[next][prev] += val;
      prev = next;
    }
    print("\n");
  }
  // compute max flow, basing on weight of newly-created edges
  // towards the source in the residual capacity graph
  flow = 0;
  print("calcolo flusso totale\n");
  for (uint i=0; i<graph[source].adjs.size(); i++)
  {
    int adj = graph[source].adjs[i];
    print("vicino %d\n",adj);
    print("peso originario %d, dopo flusso %d\n",
          graph[source].weights[i],weights[source][adj]);
    /*int temp;
    for (uint t=0; t<graph[adj].adjs.size(); t++)
      if (graph[adj].adjs[t] == source)
      temp = t;*/
    flow += graph[source].weights[i] - weights[source][adj];
  }
  return flow;
}




int m;

int main(){
  char c;
  int ttttt;
  pair<int,int> edges[1000];
  while(1){
    if ((ttttt=scanf("%i %i", &n, &m))<=0)
      break;

    graph.erase(graph.begin(),graph.end());
    graph.resize(n);

    if(m>0){
      for(int i=0; i<m; i++){
        do {
          scanf("%c",&c);
        } while (c!='(');
        scanf("%i,%i",&(edges[i].first),&(edges[i].second));
        //print("%i,%i",(edges[i].first),(edges[i].second));
        scanf(")");
      }
      sort(edges,edges+m);
      graph[edges[0].first].add_adj(edges[0].second,1);
      graph[edges[0].second].add_adj(edges[0].first,1);
      for(int i=1; i<m; i++){
        if (edges[i-1]!=edges[i]){
          graph[edges[i].first].add_adj(edges[i].second,1);
          graph[edges[i].second].add_adj(edges[i].first,1);
        }
        else {
          graph[edges[i].first].weights[graph[edges[i].first].weights.size() - 1]++;
          graph[edges[i].second].weights[graph[edges[i].second].weights.size() - 1]++;
        }
      }
    }

    /* print("GRAFO\n\n");
    for (int i=0; i<n; i++)
    {
      print("nodo %d, vicini:\n",i);
      for (int j=0; j<(int)graph[i].adjs.size();j++)
        print("(%d,%d) ",graph[i].adjs[j],graph[i].weights[j]);
      print("\n");
      }*/

    int min= (n>1) ? m : 0;
    for (int k=1; k<n; k++){
      for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
          weights[i][j] = 0;
      }
      for (int i=0; i<n; i++){
        for (uint j=0; j<graph[i].adjs.size();j++)
          weights[i][graph[i].adjs[j]] += graph[i].weights[j];
      }
      print("flusso da %i a %i\n", k, 0);
      int val = max_flow(k,0);
      print("flusso da %i a %i:  %i\n", k, 0, val);
      if (val < min)
        min = val;
    }
    printf("%d\n",min);
  }
}
