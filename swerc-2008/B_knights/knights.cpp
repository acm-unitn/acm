#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAX_N 1600

int n, r, c;
double matrix[MAX_N][MAX_N+1];
double term_noti[MAX_N];

void print_matrix()
{
  printf("Matrix\n");
  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j <= n; ++j)
      printf("%6lG ",matrix[i][j]);
    printf("\n");
  }
}

void annulla(int riga, int part)
{
  double rapp;
  //printf("azzero riga %d con %d\n",riga,part);
  rapp = matrix[riga][part] / matrix[part][part] * -1;
  for (int j=part; j<=n; j++)
    matrix[riga][j] += matrix[part][j] * rapp;
}

void triangola()
{
  for (int i=0; i<n-1; i++)
  {
    for (int j=i+1; j<n; j++)
      if (matrix[j][i]<-0.0000000000001 || matrix[j][i]>0.0000000000001)
        annulla(j,i);
  }
}

void risolvi()
{
  double val;
  for (int i=n-1; i>=0; i--)
  {
    //printf("risolvo %d\n",i);
    val = matrix[i][n] / matrix[i][i];
    matrix[i][n] /= matrix[i][i];
    matrix[i][i] = 1;
    for (int j=0; j<i; j++)
    {
      matrix[j][n] -= matrix[j][i] * val;
      matrix[j][i] = 0;
    }
    //print_matrix();
  }
}

int main()
{
  double tmp;

  while (true)
  {
    scanf("%d %d",&r,&c);
    if (r==0 && c==0)
      break;
    n = r * c;
    for (int i=0; i<n; i++)
      for (int j=0; j<=n; j++)
        if (i==j)
          matrix[i][j]=1;
        else
          matrix[i][j]=0;
    //block 1
    for (int i=0; i<r; i++)
      for (int j=0; j<c; j++)
      {
        scanf("%lf", &tmp);
        if (tmp > 0)
          matrix[(i*c)+j][(i+1)*c+j] = tmp * -1;
      }
    //block 2
    for (int i=0; i<r; i++)
      for (int j=0; j<c; j++)
      {
        scanf("%lf", &tmp);
        if (tmp > 0)
          matrix[(i*c)+j][(i)*c+j+1] = tmp * -1;
      }
    //block 3
    for (int i=0; i<r; i++)
      for (int j=0; j<c; j++)
      {
        scanf("%lf", &tmp);
        if (tmp > 0)
          matrix[(i*c)+j][(i-1)*c+j] = tmp * -1;
      }
    //block 4
    for (int i=0; i<r; i++)
      for (int j=0; j<c; j++)
      {
        scanf("%lf", &tmp);
        if (tmp > 0)
          matrix[(i*c)+j][(i)*c+j-1] = tmp * -1;
      }
    for(int i = 0; i < n-1; ++i)
      matrix[i][n] = 1;
    matrix[n-1][n] = 0;
    //print_matrix();
    triangola();
    //print_matrix();
    risolvi();
    //print_matrix();
    printf("%lf\n",matrix[0][n]);
  }
  return 0;
}
