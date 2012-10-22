#include <cstdio>
#include <cmath>

#define pi 3.141592653589793

using namespace std;

long double f(long double x) {
  return tanl(sinl(x))-sinl(tanl(x))+powl(cosl(x), 5)-0.5;
  //return 1 - x * x;
}

int main() {
  FILE* in;
  in = stdin; //fopen("D.IN", "r");

  while (!feof(in)) {
    long double inizio, fine, a, b;
    long long int nstep;
    long long int result = 0;

    if (scanf("%Lf %Lf %lld", &inizio, &fine, &nstep) == -1) {
      break;
    }

    //printf("%Lf %Lf %d\n", inizio, fine, nstep);

    long double step = (fine - inizio) / ((long double) nstep);
    for (int i=0; i<nstep; i++) {
      a = inizio + step * i;
      b = inizio + step * (i+1);
      long double na = (a - pi / 2) / pi;
      long double nb = (b - pi / 2) / pi;
      if (fabs(floor(na) - floor(nb)) < 10e-10) {
        long double fa = f(a);
        long double fb = f(b);
        //printf("fa=%Lf fb=%Lf %Lf %Lf\n", fa, fb, na, nb);
        if (fa * fb < 0 || fabs(fa) < 10e-10 || fabs(fb) < 10e-10) {
          result += 1;
        }
      }
    }
    printf("%lld\n", result);
  }
}
