#include<cstdio>
#include<vector>
#include<map>
#include<utility>
#include<iostream>

#define MAX_N 50001
typedef long long int lint;

//#define DEBUG
#ifdef DEBUG
#define print(...) fprintf(stdout, __VA_ARGS__)
#else
#define print(...)
#endif

using namespace std;

struct node {
  bool closed;
  vector<int> vicini;
  vector<int> pesi;
  map<int,pair<lint,int> > costi;
  lint totale;
  int volte;
};

int n,m;
node grafo[MAX_N];

void visita(int nodo, int padre)
{
  static lint c;
  static int figlio;
  static int v;
  for (int i=0; i<(int) grafo[nodo].vicini.size(); i++)
  {
    figlio = grafo[nodo].vicini[i];
    if (figlio != padre)
    {
      v = grafo[nodo].volte-grafo[nodo].costi[figlio].second;
      c = grafo[nodo].totale-grafo[nodo].costi[figlio].first+
        v * (lint)grafo[nodo].pesi[i];
      grafo[figlio].volte += v;
      grafo[figlio].totale += c;
      visita(figlio,nodo);
    }
  }
}


pair<lint,int> costo(int nodo, int padre)
{
  static pair<lint,int> tmp;
  static int v;
  static lint c;
  int vicino;

  print("visito %d padre %d\n",nodo,padre);
  fflush(stdout);
  for (int i=0; i<(int)grafo[nodo].vicini.size(); i++)
  {
    vicino = grafo[nodo].vicini[i];
    print("vicino %d\n",vicino);
    if (vicino!=padre)
    {
      print("non lo ho\n");
      tmp = costo(vicino, nodo);
      v = tmp.second;
      c = tmp.first + v*(lint)grafo[nodo].pesi[i] ;
      //print("nodo %d vicino %d aggiungo %lld\n",nodo,vicino,c);
      grafo[nodo].costi[vicino] = pair<lint,int>(c,v);
      grafo[nodo].totale += c;
      grafo[nodo].volte += v;
    }
  }
  //print("nodo %d, ritorno %lld volte %lld\n",nodo,grafo[nodo].totale,
  //      grafo[nodo].volte);
  return pair<lint,int>(grafo[nodo].totale,grafo[nodo].volte);
}


int main()
{
  int c, a, b, t;
  lint min;
  scanf("%d",&c);
  for (int k=0; k<c; k++)
  {
    scanf("%d",&n);
    for (int i=1; i<=n; i++)
    {
      grafo[i].vicini.erase(grafo[i].vicini.begin(),grafo[i].vicini.end());
      grafo[i].pesi.erase(grafo[i].pesi.begin(),grafo[i].pesi.end());
      grafo[i].costi.erase(grafo[i].costi.begin(),grafo[i].costi.end());
      grafo[i].totale = 0;
      grafo[i].volte = 0;
    }
    for (int i=0; i<n-1; i++)
    {
      scanf("%d %d %d",&a,&b,&t);
      grafo[a].vicini.push_back(b);
      grafo[b].vicini.push_back(a);
      grafo[a].pesi.push_back(t);
      grafo[b].pesi.push_back(t);
    }
    scanf("%d",&m);
    for (int i=0; i<m; i++)
    {
      scanf("%d %d\n",&a,&b);
      grafo[a].volte = b;
    }
    for (int i=1; i<=n; i++)
    {
      print("nodo %d\n",i);
      for (int j=0; j<(int)grafo[i].vicini.size(); j++)
        print("(%d,%d) ",grafo[i].vicini[j],grafo[i].pesi[j]);
      print("\n");
    }
    costo(1,-1);
    visita(1,-1);
    min = grafo[1].totale;
    for (int i=1; i<=n; i++)
      if (grafo[i].totale < min)
      {
        min = grafo[i].totale;
      }
    //printf("%lld\n",min*2);
    cout << min*2 <<endl;
    int first_written = 0;
    for (int i=1; i<=n; i++)
      if (grafo[i].totale==min)
      {
        if (first_written){
          printf(" ");
        }
        printf("%d",i);
        first_written = 1;
      }
    printf("\n");
  }
  return 0;
}
