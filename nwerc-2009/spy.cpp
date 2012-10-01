#include<cstdio>
#include<cmath>

#define MAX_N 10000000

using namespace std;

int n;
bool primi[MAX_N];
bool vive[7];
char costr[7];
char cifre[7];

int num(int messe)
{
  int ret;
  ret = 0;
  for (int i=0; i<messe; i++)
    ret += (costr[i] - '0') * pow(10,messe-i-1);
  return ret;
}


int perm(int messe, int eff)
{
  int quanti = 0;
  if (messe == n){
    printf("##### %d ",num(eff));
    for (int i=0; i< eff; i++)
      printf("%c",costr[i]);
    printf("\n");
    return (primi[num(eff)])?1:0;
  }
  else {
    printf("chiamata %d %d lascio vuoto\n",messe,eff);
    quanti += perm(messe+1,eff);
    for (int i=0; i<n; i++) {
      if (vive[i]) {
        vive[i] = false;
        costr[eff] = cifre[i];
        printf("chiamata %d %d metto %c\n",messe,eff,cifre[i]);
        quanti += perm(messe+1,eff+1);
        vive[i] = true;
      }
    }
    return quanti;
  }
}

int main()
{
  int t,quanti;
  char c;
  for (int i=2; i<MAX_N; i++) {
    primi[i] = true;
  }
  primi[0] = false;
  primi[1] = false;
  for (int i=2; i<MAX_N; i++) {
    if (primi[i])
      for (int j=i*2; j<MAX_N; j+=i)
        primi[j] = false;
  }
  for (int i=0; i< 50; i++)
    if (primi[i])
      printf("%d ",i);
  printf("\n");
  scanf("%d\n",&t);
  for (int k=0; k<t; k++){
    scanf("%c",&c);
    n = 0;
    while (c != '\n') {
      cifre[n] = c;
      n++;
      scanf("%c",&c);
    }
    printf("caso %d, lette %d cifre\n",k,n);
    for (int i=0; i<n; i++)
      printf("%c\n",cifre[i]);
    for (int i=0; i<n; i++)
      vive[i] = true;
    quanti = perm(0,0);
    printf("%d\n",quanti);
  }
  return 0;
}
