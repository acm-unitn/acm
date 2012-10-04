#include <cstdio>
#include <cstdlib>

//#define DEBUG
#ifdef DEBUG
#define print(...) fprintf(stderr, __VA_ARGS__)
#else
#define print(...)
#endif
#define lint long long


#define MAXLEN 50000


//lint arr[MAXLEN+1];
lint sums[MAXLEN+2];
lint n, d;

int cmp(const void *a, const void *b){
  const lint *ia = (const lint *)a;
  const lint *ib = (const lint *)b;
  return *ia  - *ib;
}

lint resolve(){
  for (lint i=0; i<=n; i++){
    print("%lli ", sums[i]);
  }
  print("\n");
  qsort(sums, n+1, sizeof(lint), cmp);
  sums[n+1] = -1;
  for (lint i=0; i<=n+1; i++){
    print("%lli ", sums[i]);
  }
  print("\n");
  lint res = 0;
  lint counter = 1;
  for (lint i=1; i<=n+1; i++){
    if(sums[i] != sums[i-1]){
      res += (counter * (counter-1))/2;
      print ("  %lli occorrenze di %lli: res= %lli\n", counter, sums[i-1], res);
      counter = 1;
    }
    else {
      counter++;
    }
  }

  return res;
}

int main(){
  lint c;
  scanf("%lli", &c);
  print("c = %lli\n\n", c);
  for(lint i=0; i<c; i++){
    scanf("%lli %lli", &d, &n);
    print("n %lli; d %lli;\n", n, d);
    sums[0] = 0;
    for(lint j=1; j<=n; j++){
      lint tmp;
      scanf("%lli", &tmp);
      sums[j] = (sums[j-1] + tmp) % d;
    }
    lint res = resolve();
    printf("%lli\n", res);
  }
}
