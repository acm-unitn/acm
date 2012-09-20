#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int main() {
  int N;
  char str[10001];

  scanf("%d", &N);
  for (int i=0; i < N; i++) {
    int C = 0;
    scanf("%s", str);
    int len = strlen(str);
    //printf("%s\n", str);

    // costo lettere
    for (int j=0; j<len; j++) {
      C += min(str[j] - 'A', 'Z' - str[j] + 1);
    }

    // costo orizzontale
    int costo_base = len - 1;
    int risparmio = 0;
    // cerco tutte le sequenze di A
    for (int j=1; j<len; j++) {
      int inizio = -1;
      int fine = -1;
      if (str[j] == 'A') {
        inizio = j;
        for (int k=j+1; k<len; k++) {
          j++;
          if (str[k] != 'A') {
            fine = k - 1;
            break;
          }
        }
        if (fine == -1) {
          fine = len - 1;
        }
        // guadagno - costo = len(A) - min(lettere a sx - lettere a dx)
        int curr_risparmio = (fine + 1 - inizio) - min(inizio - 1, len - (fine + 1));
        //printf("risparmio %d\n", curr_risparmio);
        //printf("%d %d %d %d %d\n", inizio, fine, (fine + 1 - inizio), inizio - 1, len - (fine + 1));
        if (curr_risparmio > risparmio) {
          risparmio = curr_risparmio;
        }
      }
    }
    printf("%d\n", C + costo_base - risparmio);
  }
}
