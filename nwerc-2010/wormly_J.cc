// nwerc 2010
// problem J - Wormly
// solution by Davide Kirchner

using namespace std;
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>

#include <list>
#include <stack>
#include <queue>

#define MAXN 1000000
#ifdef DEBUG
#define PRINT                                                  \
  for(long int k=0; k<n; k++){                                 \
    if (k>=worm_start && k<=worm_end) printf("o");             \
    else printf(" ");                                          \
  }                                                            \
  printf("\n");                                                \
  for(long int k=0; k<n; k++){                                 \
    if (k>=placche[legs_start] && k<=placche[legs_end]         \
        && bridge[k])                                          \
      printf("L");                                             \
    else                                                       \
      printf(" ");                                             \
  }                                                            \
  printf("\n");                                                \
  for(long int k=0; k<n; k++){                                 \
    if (bridge[k]) printf("-");                                \
    else printf(".");                                          \
  }                                                            \
  printf("\n");                                                \
  printf("GAMBE:  ");                                          \
  printf("%li  ", legs_start);                                 \
  printf("%li\n", legs_end);                                   \
  printf("PLACCHE:  ");                                        \
  for(long int i=0; i<pl_len; i++)                             \
    printf("%li ", placche[i]);                                \
  printf("\n\n");
#else
#define PRINT
#endif
bool bridge[MAXN];
long int placche[MAXN]; // indexes in bridge, where one can walk
char res[100];
char imp[] = "IMPOSSIBLE";

void resolve(long int l, long int b, long int n, long int pl_len) {
  // bridge should be filled from 0 to n-1
  // placche shluld be filled from 0 to pl_len-1
  long int worm_start = 0;
  long int worm_end = b-1;
  long int legs_start = 0; // index of first leg in array placche
  long int legs_end = l-1; //          last leg
  //long int legs_ind[l];
  //for (long int i=0; i<l; i++)
  //  legs_ind[i] = i;
  //// legs are all on the left, from 0 to l-1
  long int turns = 0;
  PRINT
  while(1) {
    //printf("TURN %li is starting\n", turns + 1);
    if (placche[legs_start] == (n-l)) { // first leg in position n-l
      //printf("END!\n");
      sprintf(res, "%li", turns);
      return;
    }
    if ((worm_start < placche[legs_start])
        && (worm_end < (n-1))){  // if worm can move
      // MOVE WORM
      long int moves = placche[legs_start] - worm_start;
      if (worm_end + moves >= n)
        moves = n - 1 - worm_end; // reaching the end
      turns += moves;
      worm_start += moves;
      worm_end += moves;
      //printf("WORM MOVED\n");
    }
    else {
      // MOVE LEGS (if possible)
      long int i;
      for(i=legs_end; placche[i]<=worm_end && i<pl_len; i++);
      i--; // last i where conditions were met!
      long int shift = i - legs_end;
      if(shift == 0) {
        strcpy(res, "IMPOSSIBLE");
        return;
      }
      else {
        turns += l;
        legs_start += shift;
        legs_end += shift;
      }
      /*
      queue<int> q = queue<int>();
      // scan bridge backwords
      //for (long int i=legs_ind[l-1]+1; i<=worm_end; i++){
      for (long int i=worm_end; i>legs_ind[l-1]; i--) {
        if (bridge[i]){
          q.push(i);
        }
      }
      if (q.empty()){
        // "IMPOSSIBLE"
        strcpy(res, imp);
        return;
      }
      else {
        turns += l; // conto una mossa per ogni gamba!
        for (long int leg=l-1; leg>=0 ; leg--){
          // move leg to latest available position
          q.push(legs_ind[leg]);
          legs_ind[leg] = q.front();
          q.pop();
        }
      }*/
      //printf("Moved legs\n");
    }
    //printf("TURN %li is done\n", turns);
    PRINT
  }
}

int main(int argc, char**argv) {
  // IO management, input parsing, iterating over test cases

  long int c; // number of cases
  scanf("%li\n", &c);
  //printf("casi: %li\n", c);
  fflush(stdout);
  for(long int i=0; i<c; i++){
    //printf("Caso %li\n", i);
    long int l, b, n;
    scanf("%li %li %li\n", &l, &b, &n);
    //printf("l %li; b %li; n %li\n", l, b, n);
    long int pl_j = 0; //intex in placche
    for (long int j=0; j<n; j++){
      char ch;
      scanf("%c", &ch);
      if (ch=='1') {
        bridge[j] = true;
        placche[pl_j] = j;
        pl_j++;
      }
      else if (ch=='0') bridge[j] = false;
      else printf("WAT - %c \n", ch);
    }
    resolve(l, b, n, pl_j);
    printf("%s\n", res);
  }
  return 0;
}
