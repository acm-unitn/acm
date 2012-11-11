#include <cstdio>
#include <utility>
#include <cmath>

#define D 10
#define MAX_N 100801

using namespace std;

pair<double,double> mean_points[10][10];
int count[D][D];
pair<double,double> points[MAX_N];

int main()
{
  double sum;
  int n;
  long long int quanti;
  double x, y;
  while (scanf("%d",&n)==1)
  {
    for (int i=0; i<D; i++)
      for (int j=0; j<D; j++)
      {
        count[i][j] = 0;
        mean_points[i][j].first = 0;
        mean_points[i][j].second = 0;
      }
    for (int z=0; z<n; z++)
    {
      scanf("%lf %lf",&x,&y);
      points[z].first = x;
      points[z].second = y;
      for (int i=(int)floor(x); i<D; i++)
        for (int j=(int)floor(y); j<D; j++)
        {
          count[i][j] ++;
          mean_points[i][j].first += x;
          mean_points[i][j].second += y;
        }
    }
    for (int i=0; i<D; i++)
      for (int j=0; j<D; j++)
      {
        if (count[i][j]>0)
        {
          mean_points[i][j].first /= count[i][j];
          mean_points[i][j].second /= count[i][j];
        }
      }
    /*
    for (int i=0; i<D; i++)
      for (int j=0; j<D; j++)
      {
        printf("%d %d mean point (%.9lf,%.9lf) %d\n",
               i,j,
               mean_points[i][j].first,
               mean_points[i][j].second,
               count[i][j]);
      }
    */
    sum = 0;
    quanti = 0;
    for (int i=0; i<n; i++)
    {
      x = points[i].first;
      y = points[i].second;
      if (((int)floor(x)-1)>=0 && ((int)floor(y)-1)>=0)
      {
        sum += (x - mean_points[(int)floor(x)-1][(int)floor(y)-1].first) *
          count[(int)floor(x)-1][(int)floor(y)-1];
        sum += (y - mean_points[(int)floor(x)-1][(int)floor(y)-1].second) *
          count[(int)floor(x)-1][(int)floor(y)-1];
        quanti += count[(int)floor(x)-1][(int)floor(y)-1];
      }
    }
    if (quanti>0)
      sum /= quanti;
    printf("%.8lf\n",sum);
  }
  return 0;
}
