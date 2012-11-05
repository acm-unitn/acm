#include <stdio.h>

#ifdef DEBUG
#define print(...) fprintf(stderr, __VA_ARGS__); fflush(stdout)
#else
#define print(...)
#endif

#define lint long long int

lint arr[1000][2];

lint gcd_inner(lint a, lint r) {
  // assume a>r
  lint new_r = a % r;
  if (new_r == 0)
    return r;
  else
    return gcd_inner(r, new_r);
}

lint gcd(lint a, lint b) {
  if (a>b)
    return gcd_inner(a, b);
  else
    return gcd_inner(b, a);
}

void solve(int c){
  lint curr_gcd = 0;
  lint max_b;
  int i;
  print("solve  \n\n");

  for (i=0; i<c && curr_gcd == 0; i++) {
    if (arr[i][0] < arr[i][1]) {
      printf("impossible\n");
      return;
    }
    else {
      curr_gcd = arr[i][0] - arr[i][1];
    }
  }

  if (i == c) {
      printf("impossible\n");
      return;
  }

  for (; i<c; i++) {
    lint tmp = 0;
    while (tmp == 0 && i<c) {
      if (arr[i][0] < arr[i][1]) {
	printf("impossible\n");
	return;
      }
      else {
	tmp = arr[i][0] - arr[i][1];
      }
    }

    if (i == c) {
      break;
    }

    curr_gcd = gcd(curr_gcd, arr[i][0] - arr[i][1]);
  }
  

  // compute max_b
  max_b = arr[0][1];
  for(i=1; i<c; i++) {
    if (arr[0][1] > max_b) 
      max_b = arr[0][1];
  }

  if (curr_gcd > 1 && curr_gcd > max_b)
    printf("%lli\n", curr_gcd);
  else
    printf("impossible\n");
}

int main() {
  int t, c;
  lint tmp;
  scanf("%i", &t);
  print("t=%i\n\n", t);

  for (int i=0; i<t; i++) {
    scanf("%i", &c);
    for (int j=0; j<c; j++) {
      arr[j][0] = 0;
      for (int z=0; z<9; z++) {
	scanf("%lli", &tmp);
	arr[j][0] += tmp;
      }
      scanf("%lli", &(arr[j][1]));
    }
    solve(c);
  }

}
