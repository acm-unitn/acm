#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAX_N 101

int n;
double matrix[MAX_N][MAX_N];
double term_noti[MAX_N];

void print_matrix()
{
  printf("Matrix\n");
  for(int i = 1; i <= n; i++)
  {
    for(int j = 1; j <= n; ++j)
      printf("%6lG ",matrix[i][j]);
    printf("\n");
  }
}

void print_term_noti()
{
  printf("Termini noti\n");
  for(int j = 1; j <= n; ++j)
    printf("%6lg\n",term_noti[j]);
}

void scale_factor(double S[MAX_N])
{
  for(int i = 1; i <= n; ++i)
  {
    S[i] = matrix[i][1];
    for(int j = 2; j <= n; ++j)
    {
      if(S[i] < fabs(matrix[i][j]))
        S[i] = fabs(matrix[i][j]);
    }
  }
}

void swap_rows(int i, int j)
{
  double temp;
  for (int k=0; k<=n; k++)
  {
    temp = matrix[i][k];
    matrix[i][k] = matrix[j][k];
    matrix[j][k] = temp;
  }
}

void pivot_partial(double S[MAX_N])
{
  double temp;
  for(int j = 1; j <= n; ++j)
  {
    for(int i = j + 1; i <= n; ++i)
    {
      if(S[i] == 0)
      {
        if(term_noti[i] == 0)
          printf("\nSystem doesnt have a unique solution");
        else
          printf("\nSystem is inconsistent");
        exit(1);
      }
      if(fabs(matrix[i][j]/S[i]) > fabs(matrix[j][j]/S[j]))
      {
        swap_rows(i,j);
        temp = term_noti[i];
        term_noti[i] = term_noti[j];
        term_noti[j] = temp;
      }
    }
    if(matrix[j][j] == 0)
    {
      printf("\nSingular System Detected\n");
      exit(1);
    }
  }
}

void forward_elimination()
{
  double m;
  for(int k = 1; k <= n-1; ++k)
  {
    for(int i = k + 1; i <= n; ++i)
    {
      m = matrix[i][k] / matrix[k][k];
      for(int j = k + 1; j <= n; ++j)
      {
        matrix[i][j] -= m * matrix[k][j];
        if(i == j && matrix[i][j] == 0)
        {
          printf("\nSingular system detected");
          exit(1);
        }
      }
      term_noti[i] -= m * term_noti[k];
    }
  }
}

void back_substitution(double X[MAX_N])
{
  double sum;
  X[n] = term_noti[n]/matrix[n][n];
  for(int i = n - 1; i >= 1; --i)
  {
    sum = 0;
    for(int j = i + 1; j <= n; ++j)
      sum += matrix[i][j] * X[j];
    X[i] = (term_noti[i] - sum) / matrix[i][i];
  }
}

void gauss(double X[MAX_N])
{
  double S[MAX_N];

  scale_factor(S);
  pivot_partial(S);
  forward_elimination();
  back_substitution(X);
}

int main()
{
  double X[MAX_N];

  scanf("%d",&n);
  printf("Dimension = %i\n",n);
  for(int i = 1; i <= n; ++i)
    for(int j = 1; j <= n; ++j)
      scanf("%lf", &matrix[i][j]);
  for(int j = 1; j <= n; ++j)
    scanf("%lf",&term_noti[j]);
  print_matrix();
  print_term_noti();
  gauss(X);
  for(int i=1; i<=n; ++i)
    printf("%lf ",X[i]);
  return 0;
}
