#include <cstdio>
#include <stack>

#ifdef DEBUG
#define print(...) fprintf(stdout, __VA_ARGS__)
#else
#define print(...)
#endif


#define MAX_N 1001

using namespace std;

int n, m;
bool land[MAX_N][MAX_N];
int max_height[MAX_N][MAX_N];
int output[MAX_N*2+MAX_N*2];
//int max_sin[MAX_N][MAX_N];

void fill_max_height()
{
  int max;
  for (int j=0; j<m; j++)
  {
    max=0;
    for (int i=0; i<n; i++)
    {
      if (land[i][j])
        max_height[i][j] = max;
      else
      {
        max_height[i][j] = -1;
        max = i+1;
      }
    }
  }
}

/*
void fill_max_sin()
{
  int max;
  for (int i=0; i<n; i++)
  {
    max=0;
    for (int j=0; i<m; j++)
    {
      if (land[i][j])
        max_sin[i][j] = max;
      else
      {
        max_sin[i][j] = -1;
        max = i+1;
      }
    }
  }
  }*/


void solve_row(int row)
{
  int max, endi, endj;
  pair<int,int> tmp;
  int base, altezza;
  stack<pair<int,int> > s;
  s.push(pair<int,int>(row,0));
  for (int j=0; j<m; j++)
  {
    if (max_height[row][j] == -1)
    {
      while (!s.empty())
        s.pop();
      for (int k=row; k>max_height[row][j+1]; k--)
        s.push(pair<int,int>(k,j+1));
    }
    else
    {
      print("%d\n",j);
      max = 0;
      while (!s.empty() && (s.top().first < max_height[row][j]))
      {
        base = j-s.top().second+1;
        altezza = row-max_height[row][j]+1;
        if (base+altezza>max)
        {
          endi = max_height[row][j];
          endj = s.top().second;
          max = base+altezza;
        }
        s.pop();
      }
      if (s.empty())
      {
        base = 0;
        altezza = 0;
      }
      else
      {
        print("end point %d %d\n",s.top().first,s.top().second);
        base = j-s.top().second+1;
        altezza = row-s.top().first+1;
      }
      if (max > base+altezza)
      {
        s.push(pair<int,int>(endi,endj));
        base = j-endj+1;
        altezza = row-endi+1;
      }
      if (base+altezza > 1+(row-max_height[row][j]+1))
      {
        print("si aggiunge all'end point %d\n",(base+altezza)*2);
        if ((base+altezza)*2 == 6)
        {
          print("%d %d\n",row,j);
          print("**********************************************************\n");
        }
        output[(base+altezza)*2]++;
      }
      else
      {
        print("colonna alta %d\n",(1+row-max_height[row][j]+1)*2);
        if ((1+row-max_height[row][j]+1)*2 == 6)
        {
          print("%d %d\n",row,j);
          print("**********************************************************\n");
        }
        s.push(pair<int,int>(max_height[row][j],j));
        output[(1+row-max_height[row][j]+1)*2]++;
      }
    }
  }
}

void solve()
{
  for (int i=0; i<n; i++)
  {
    print("row %d\n",i);
    solve_row(i);
  }
}

int main()
{
  int t;
  char c;
  scanf("%d",&t);
  for (int k=0; k<t; k++)
  {
    scanf("%d %d",&n,&m);
    //printf("caso %d %d %d\n",k,n,m);
    scanf("\n");
    for (int i=0; i<n; i++)
    {
      for (int j=0; j<m; j++)
      {
        scanf("%c",&c);
        land[i][j] = (c=='.');
      }
      scanf("\n");
    }
    fill_max_height();
    //fill_max_sin();
    for (int i=0; i<=2*n+2*m; i++)
    {
      output[i] = 0;
    }
    print("land\n");
    for (int i=0; i<n; i++)
    {
      for (int j=0; j<m; j++)
        if (land[i][j])
          print(".");
        else
          print("#");
      print("\n");
    }
    print("height\n");
    for (int i=0; i<n; i++)
    {
      for (int j=0; j<m; j++)
        print("%d ",max_height[i][j]);
      print("\n");
    }
    solve();
    for (int i=0; i<=2*n+2*m; i++)
    {
      if (output[i] != 0)
        printf("%d x %d\n",output[i],i);
    }
  }
}
