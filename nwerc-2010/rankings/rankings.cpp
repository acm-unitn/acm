#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#define MAX_N 500

using namespace std;

struct nodo {
  int posizione;
  bool visitato;
  vector<int> vicini;
};

int n, m, posizione_prec, index_prec;
int ranking[MAX_N];
int rank_out[MAX_N+1];
int entranti[MAX_N+1];
bool adiacenza[MAX_N+1][MAX_N+1];
bool impossible;
vector<nodo> grafo;
queue<int> liberi;

int main()
{
  int t,a,b,nod,pos_prec,quanti;

  scanf("%d",&t);
  for (int k=0; k<t; k++)
  {
    scanf("%d",&n);
    for (int i=1; i<=n; i++)
      for (int j=1; j<=n; j++)
	adiacenza[i][j] = false;
    for (int i=0; i<n; i++)
      scanf("%d",&ranking[i]);
    for (int i=0; i<n-1; i++)
      for (int j=i+1; j<n; j++)
	adiacenza[ranking[i]][ranking[j]] = true;
    scanf("%d",&m);
    for (int i=0; i<m; i++)
    {
      scanf("%d %d",&a,&b);
      adiacenza[a][b] = !adiacenza[a][b];
      adiacenza[b][a] = !adiacenza[b][a];
    }
    grafo.resize(n+1);
    for (int i=1; i<=n; i++)
    {
      entranti[i] = 0;
      rank_out[i] = -1;
      grafo[i].visitato = false;
      grafo[i].vicini.erase(grafo[i].vicini.begin(),grafo[i].vicini.end());
    }
    for (int i=1; i<=n; i++)
      for (int j=1; j<=n; j++)
	if (adiacenza[i][j])
	{
	  entranti[j] ++;
	  grafo[i].vicini.push_back(j);
	}
    while (!liberi.empty())
      liberi.pop();
    for (int i = 1; i<=n; i++)
      if (entranti[i] == 0)
      {
	grafo[i].posizione = 1;
	liberi.push(i);
      }
    impossible = liberi.empty();
    pos_prec = 0;
    quanti = 0;
    while(!liberi.empty() && !impossible)
    {
      nod = liberi.front();
      quanti ++;
      grafo[nod].visitato = true;
      liberi.pop();
      if(grafo[nod].posizione == pos_prec)
	rank_out[grafo[nod].posizione] = -1;
      else
	rank_out[grafo[nod].posizione] = nod;
      for (int i=0; i<(int)grafo[nod].vicini.size(); i++)
      {
	int id_figlio = grafo[nod].vicini[i];
	if (grafo[id_figlio].visitato)
	{
	  impossible = true;
	  break;
	}
	entranti[id_figlio]--;
	if (entranti[id_figlio] == 0)
	{
	    grafo[id_figlio].posizione = grafo[nod].posizione +1;
	    liberi.push(id_figlio);
	}
      }
    }
    if (impossible || quanti < n)
      printf("IMPOSSIBLE");
    else
      for (int i=1; i<=n; i++)
      {
	if (rank_out[i] == -1)
	  printf("?");
	else
	  printf("%d",rank_out[i]);
	if (i!=n)
	  printf(" ");
      }
    printf("\n");
  }
}
