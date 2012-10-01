#include <cstdio>
#include <cstdlib>

//#define DEBUG
#ifdef DEBUG
#define print(...) fprintf(stderr, __VA_ARGS__)
#else
#define print(...)
#endif

#define MAXLEN 50000

int arr[MAXLEN+1];
int sums[MAXLEN+2];
int n, d;

int cmp(const void *a, const void *b){
  const int *ia = (const int *)a;
  const int *ib = (const int *)b;
  return *ia  - *ib;
}

int resolve(){
  for (int i=0; i<=n; i++){
    print("%i ", sums[i]);
  }
  print("\n");
  qsort(sums, n+1, sizeof(int), cmp);
  sums[n+1] = -1;
  for (int i=0; i<=n+1; i++){
    print("%i ", sums[i]);
  }
  print("\n");
  int res = 0;
  int counter = 0;
  int last = -1;
  for (int i=0; i<=n+1; i++){
    if(sums[i] != last){
      res += (counter * (counter-1))/2;
      print ("  %i occorrenze di %i: res= %i\n", counter, last, res);
      last = sums[i];
      counter = 1;
    }
    else {
      counter++;
    }
  }

  return res;
}

int main(){
  int c;
  scanf("%i", &c);
  print("c = %i\n\n", c);
  for(int i=0; i<c; i++){
    scanf("%i %i", &d, &n);
    print("n %i; d %i;\n", n, d);
    sums[0] = 0;
    for(int j=1; j<=n; j++){
      int tmp;
      scanf("%i", &tmp);
      sums[j] = (sums[j-1] + tmp) % d;
    }
    int res = resolve();
    printf("%i\n", res);
  }
}
