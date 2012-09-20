// http://livearchive.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2982
// solution by Davide Kirchner

using namespace std;
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>

#include <list>
#include <stack>

#define MAXSTR 1000000

char str[MAXSTR + 1];
char res[MAXSTR + 1];

void printl(list<int> l) {
  cout << "list:";
  for (list<int>::iterator i = l.begin(); i != l.end(); i++) {
    cout << " " << (*i);
  }
  cout << endl;
}

char next(char c){
  switch(c){
  case 'a':
    return 'e'; break;
  case 'e':
    return 'i'; break;
  case 'i':
    return 'o'; break;
  case 'o':
    return '\0'; break;
  default:
    cout << "WAT\n";
    return 'H';
  }
}
char opening_letter(char c){
  switch(c){
  case 'a':
  case 'e':
    return 'a'; break;
  case 'i':
  case 'o':
    return 'i'; break;
  default:
    cout << "WAT\n";
    return 'H';
  }
}
int opens(char c){
  switch(c){
  case 'a':
  case 'i':
    return 1; break;
  case 'e':
  case 'o':
    return 0; break;
  default:
    cout << "WAT\n";
    return 'H';
  }
}

void result() { // actual test case solving
  strcpy(res, str);
  stack<char> st;
  int len = strlen(str)
  // loop from strlen backwords, didn't find
  // a way to make scanf() tell me the read length
  for(int i=len-1; i>=0; i--) {
    char c = str[i];
    int free
  }
}

int main(int argc, char**argv) {
  // IO management, input parsing, iterating over test cases

  int n;
  scanf("%i\n", &n);
  printf("%i\n", n);
  fflush(stdout);
  for(int i=0; i<n; i++){
    scanf("%s", str);
    result();
    printf("%s\n", res);
  }
  return 0;
}
