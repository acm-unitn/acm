#include<cstdio>

#define MAX_N 10000

//#define DEBUG
#ifdef DEBUG
#define print(...) fprintf(stdout, __VA_ARGS__)
#else
#define print(...)
#endif

using namespace std;

int tiles[MAX_N+1];
int num[6];

void metti_tile(int pos, int v1, int v2, int v3)
{
  int i;
  bool min=false;
  bool vivo[6]={true,true,true,true,true,true};
  vivo[tiles[v1]] = false;
  vivo[tiles[v2]] = false;
  vivo[tiles[v3]] = false;
  print("morti %d %d %d\n",tiles[v1],tiles[v2],tiles[v3]);
  //for (int i=1; i<=5; i++)
//    print("(%d %d) \n",i,num[i]);
  print("\n");
  for (i=1; i<=5 && !min; i++)
  {
    if (vivo[i])
    {
      min = true;
      for (int j=1; j<=5; j++)
        if (vivo[j] && num[j]<num[i])
          min=false;
    }
  }
  num[i-1]++;
  tiles[pos] = i-1;
}

void metti_tile(int pos, int v1, int v2)
{
  metti_tile(pos,v1,v2,v2);
}

int main()
{
  int c, n, lato, giro, posizione, lunghezza_lato, confinante1, confinante2;
  for (int i=0; i<=6; i++)
    num[i] = 1;
  tiles[0] = 1;
  tiles[1] = 2;
  tiles[2] = 3;
  tiles[3] = 4;
  tiles[4] = 5;
  tiles[5] = 2;
  tiles[6] = 3;
  num[2]++;
  num[3]++;
  giro = 2;
  lato = 1;
  posizione = 1;
  lunghezza_lato = 2;
  for (int i=7; i<=MAX_N; i++)
  {
    print("indice %d\n",i);
    if (posizione==1 && lato==1)
    {
      //print("confino con %d %d\n",i-(giro-1)*6,i-1);
      metti_tile(i,i-(giro-1)*6,i-1);
      confinante1 = i-(giro-1)*6;
      confinante2 = i-(giro-1)*6+1;
      posizione++;
    }
    else if (posizione == lunghezza_lato && lato==6)
    {
      //print("confino con %d %d %d\n",i-1,confinante1,confinante2);
      metti_tile(i,i-1,confinante1,confinante2);
      posizione = 1;
      giro ++;
      lato = 1;
      lunghezza_lato++;
    }
    else if (posizione == lunghezza_lato)
    {
      //print("confingo con %d e %d\n",confinante1,i-1);
      metti_tile(i,confinante1,i-1);
      posizione = 1;
      lato++;
    }
    else
    {
      //print("confingo con %d %d e %d\n",confinante1,confinante2,i-1);
      metti_tile(i,confinante1,confinante2,i-1);
      confinante1++;
      confinante2++;
      posizione++;
    }
    print("metto %d\n",tiles[i]);
  }
  scanf("%d",&c);
  for (int k=0; k<c; k++)
  {
    scanf("%d",&n);
    printf("%d\n",tiles[n-1]);
  }
  return 0;
}
