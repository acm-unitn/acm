#include <cstdio>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

struct node {
  bool aperto;
  bool visited;
  int max;
  vector<int> vicini;
  vector<int> pesi;
  int mancante;
  int peso_mancante;
};

#define MAX_Q 1000
#define uint unsigned int

int n, m;
vector<node> graph;
int query[MAX_Q][2];
int start, end;

#define DEBUG
#ifdef DEBUG
#define print(...) fprintf(stdout, __VA_ARGS__)
#else
#define print(...)
#endif

int visita(int nodo, int mancante, int peso_mancante)
{
  if (nodo == end)
    return 0;
  else if (graph[nodo].visited)
  {
    int res;
    if (graph[nodo].mancante != -1)
    {
      res = max(graph[graph[nodo].mancante].max, graph[nodo].peso_mancante);
      graph[nodo].max = min(graph[nodo].max,res);
    }
    return graph[nodo].max;
  }
  else
  {
    print("visito %d\n",nodo);
    int res, min = INT_MAX;
    graph[nodo].aperto = true;
    graph[nodo].mancante = mancante;
    graph[nodo].peso_mancante = peso_mancante;
    for (uint i=0; i<graph[nodo].vicini.size(); i++)
    {
      if (!graph[graph[nodo].vicini[i]].aperto)
      {
        res = max(visita(graph[nodo].vicini[i],nodo,graph[nodo].pesi[i]),
                  graph[nodo].pesi[i]);
        print("al nodo %d il nodo %d ritorna %d\n",nodo,graph[nodo].vicini[i],res);
        if (res < min)
          min = res;
      }
    }
    graph[nodo].max = min;
    graph[nodo].aperto = false;
    graph[nodo].visited = true;
    return min;
  }
}

int main()
{
  int t, a, b, p, q, max;
  scanf("%d",&t);
  for (int k=0; k<t; k++)
  {
    scanf("%d %d",&n,&m);
    graph.erase(graph.begin(),graph.end());
    graph.resize(n+1);
    for (int i=0; i<m; i++)
    {
      scanf("%d %d %d",&a,&b,&p);
      graph[a].vicini.push_back(b);
      graph[a].pesi.push_back(p);
      graph[b].vicini.push_back(a);
      graph[b].pesi.push_back(p);
    }
    scanf("%d",&q);
    for (int i=0; i<q; i++)
    {
      scanf("%d %d",&(query[i][0]),&(query[i][1]));
    }
    printf("Case %d\n",k+1);
    for (int i=0; i<q; i++)
    {
      for (int j=0; j<=n; j++)
      {
        graph[j].visited = false;
        graph[j].aperto = false;
        graph[j].mancante = -1;
        graph[j].max = -1;
      }
      start = query[i][0];
      end = query[i][1];
      max = visita(query[i][0], -1, -1);
      printf("%d\n",max);
    }
  }
  return 0;
}
