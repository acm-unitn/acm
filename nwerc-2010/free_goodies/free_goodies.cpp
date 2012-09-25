#include<cstdio>
#include<string.h>
#include<utility>
#include<algorithm>
#include<vector>

#define MAX_N 1000

using namespace std;

struct goody {
  int petra;
  int jan;
};

bool operator==(const goody& go1, const goody& go2) {
  return go1.petra==go2.petra && go1.jan==go2.jan;
}
bool operator<(const goody& go1, const goody& go2) {
  if (go1.petra==go2.petra)
    return go1.jan<go2.jan;
  else
    return go1.petra>go2.petra;
}
bool operator>(const goody& go1, const goody& go2) {
  if (go1.petra==go2.petra)
    return go1.jan>go2.jan;
  else
    return go1.petra<go2.petra;
}

int n;
vector<goody> goodies;
int mem[MAX_N][MAX_N];
int mem_pet[MAX_N+1][MAX_N+1];

int val(int i, int turn)
{
  int prendo, non_prendo;
  //printf("entro posizione %d al turno %d\n",i,turn);
  if (i==n)
  {
    mem_pet[i][turn] = 0;
    //printf("Jan 0\n");
    return 0;
  }
  else
  {
    if (mem[i][turn] == -1)
    {
      if (i<(turn-1)*2)
      {
        mem[i][turn] = val(i+1,turn);
        mem_pet[i][turn] = mem_pet[i+1][turn] + goodies[i].petra;
      }
      else
      {
        prendo = val(i+1,turn+1) + goodies[i].jan;
        non_prendo = val(i+1,turn);
        if (prendo>non_prendo)
        {
          mem[i][turn] = prendo;
          mem_pet[i][turn] = mem_pet[i+1][turn+1];
        }
        else if (non_prendo>prendo)
        {
          mem[i][turn] = non_prendo;
          mem_pet[i][turn] = mem_pet[i+1][turn] + goodies[i].petra;
        }
        else
        {
          mem[i][turn] = prendo;
          mem_pet[i][turn] = max(mem_pet[i+1][turn+1],
                                 mem_pet[i+1][turn]+goodies[i].petra);
        }
      }
    }
    //printf("RITORNATO posizione %d al turno %d\n",i,turn);
    //printf("jan = %d\n",mem[i][turn]);
    //printf("petra = %d\n",mem_pet[i][turn]);
    return mem[i][turn];
  }
}

int main()
{
  int petra,jan;
  int t;
  char s[10];
  scanf("%d",&t);
  for (int k=0; k<t; k++)
  {
    scanf("%d",&n);
    goodies.resize(n);
    scanf("%s",s);
    for (int i=0; i<n; i++)
    {
      scanf("%d %d",&goodies[i].petra,&goodies[i].jan);
    }
    sort(goodies.begin(),goodies.end());
    //printf("parsato input %d caso\n",k);
    petra = 0;
    if (strlen(s) > 3)
    {
      petra = goodies[0].petra;
      n--;
      goodies.erase(goodies.begin());
    }
    //for (int i=0; i<n; i++)
    //printf("%d %d\n",goodies[i].petra,goodies[i].jan);
    for (int i=0; i<=n; i++)
      for (int j=0; j<=n; j++)
      {
        mem[i][j] = -1;
      }
    jan = val(0,1);
    //printf("petra ++++ %d\n",petra);
    petra += mem_pet[0][1];
    printf("%d %d\n",petra,jan);
  }
  return 0;
}
