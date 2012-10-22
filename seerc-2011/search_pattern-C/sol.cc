#include <cstdio>
#include <list>

using namespace std;

#define MAXN 1000000

char buf[MAXN+1];
char pat_str[150];

bool pat[100][70];

int pat_len;

void read_patt(){
  pat_len = 0;
  for(char* c = pat_str; *c != '\0'; c++) {
    //printf("carattere %c (pat len %i): ", *c, pat_len);
    if (*c == '['){
      //printf("[\n");
      for(int i=0; i<70; i++){
        pat[pat_len][i] = false;
      }
      c++;
      for(; *c != ']'; c++){
        pat[pat_len][*c - 'A'] = true;
      }
    }
    else if (*c == '{'){
      //printf("{\n");
      for(int i=0; i<70; i++){
        pat[pat_len][i] = true;
      }
      c++;
      for(; *c != '}'; c++){
        pat[pat_len][*c - 'A'] = false;
      }
    }
    else if (*c == '?'){
      //printf("?\n");
      for(int i=0; i<70; i++){
        pat[pat_len][i] = true;
      }
    }
    else {
      //printf("normale\n");
      for(int i=0; i<70; i++){
        pat[pat_len][i] = false;
      }
      pat[pat_len][*c - 'A'] = true;
    }
    pat_len++;
  }
  //printf("%s\n", pat_str);
  fflush(stdout);
}


void parse(){
  // indici sul pattern del prossimo carattere da leggere
  list<int> ind;
  list<int> res;
  int i;
  for(i=0; buf[i] != '\0'; i++) {
    //printf("read %c\n", buf[i]);
    //fflush(stdout);
    for(list<int>::iterator p = ind.begin(); p!=ind.end();){
      //printf("   *p = %i\n", *p);
      if (*p == pat_len){
        res.push_back(i - pat_len);
        p = ind.erase(p);
        //printf("   finito\n");
      }
      else if (pat[*p][buf[i]-'A']){
        (*p)++;
        //printf("   ok, continuo\n");
        p++;
      }
      else {
        p = ind.erase(p);
        //printf("   sbaracco\n");
      }
    }
    if (pat[0][buf[i]-'A']){
      ind.push_front(1);
      //printf("  nuovo inizio, %i, %c\n", i, buf[i]);
    }
  }

  for(list<int>::iterator p = ind.begin(); p!=ind.end(); p++){
    if (*p == pat_len){
      res.push_back(i - pat_len);
    }
  }

  // print result
  if (res.empty()){
    printf("no match");
  }
  else {
    printf("%i", res.front()+1);
    for(list<int>::iterator it = (++res.begin()); it != res.end(); it++){
      printf(" %i", (*it)+1);
    }
  }
  printf("\n");
}

int main(){
  int tests;
  FILE* in;
  in = stdin;//= fopen("C.IN", "r");
  fscanf(in, "%i", &tests);

  for(int c=0; c<tests; c++){
    fscanf(in, "%s", pat_str);
    fscanf(in, "%s", buf);
    read_patt();
    parse();
  }
}
