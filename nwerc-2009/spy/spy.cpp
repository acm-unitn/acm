#include<cstdio>
#include<cmath>
#include<stack>

#define MAX_N 10000000

//#define DEBUG
#ifdef DEBUG
#define print(...) fprintf(stderr, __VA_ARGS__)
#else
#define print(...)
#endif

using namespace std;

int n;
bool primi[MAX_N];
bool vive[7];
char costr[7];
char cifre[7];
stack<int> s;

int num(int messe)
{
  int ret;
  ret = 0;
  for (int i=0; i<messe; i++)
    ret += (costr[i] - '0') * pow(10,messe-i-1);
  return ret;
}


int perm(int messe, int da_mettere)
{
  int quanti = 0;
  int t;
  if (messe == da_mettere)
  {
    print("##### %d ",num(messe));
    for (int i=0; i< messe; i++)
      print("%c",costr[i]);
    print("\n");
    t = num(messe);
    if (primi[t])
    {
      s.push(t);
      primi[t] = false;
      return 1;
    }
    else
      return 0;
  }
  else
  {
    for (int i=0; i<n; i++) {
      if (vive[i] && (cifre[i]!='0' || messe != 0)) {
        vive[i] = false;
        costr[messe] = cifre[i];
        print("chiamata %d %d metto %c\n",messe,da_mettere,cifre[i]);
        quanti += perm(messe+1,da_mettere);
        vive[i] = true;
      }
    }
    return quanti;
  }
}

int gruppi(int index, int messi, int da_mettere)
{
  int quanti = 0;
  if (messi==da_mettere)
  {
    for (int i=index; i<n; i++)
      vive[i] = false;
    return perm(0, da_mettere);
  }
  else if (index==n)
    return 0;
  else
  {
    vive[index] = true;
    quanti += gruppi(index+1,messi+1,da_mettere);
    vive[index] = false;
    quanti += gruppi(index+1,messi,da_mettere);
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
      print("%d ",i);
  print("\n");
  scanf("%d\n",&t);
  for (int k=0; k<t; k++){
    scanf("%c",&c);
    n = 0;
    while (c != '\n') {
      cifre[n] = c;
      n++;
      scanf("%c",&c);
    }
    print("caso %d, lette %d cifre\n",k,n);
    for (int i=0; i<n; i++)
      print("%c\n",cifre[i]);
    for (int i=0; i<n; i++)
      vive[i] = true;
    while(!s.empty()) {
      primi[s.top()] = true;
      s.pop();
    }
    quanti = 0;
    for (int i=1; i<=n; i++)
      quanti += gruppi(0,0,i);
    printf("%d\n",quanti);
  }
  return 0;
}
