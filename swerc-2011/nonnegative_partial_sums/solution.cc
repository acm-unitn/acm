using namespace std;
#include <iostream>
#include <fstream>

#include <list>

void printl(list<int> l) {
  cout << "list:";
  for (list<int>::iterator i = l.begin(); i != l.end(); i++) {
    cout << " " << (*i);
  }
  cout << endl;
}


int result(list<int> l) { // actual test case solving
  int acc = 0;
  do {
    for (list<int>::reverse_iterator i = l.rbegin();
	 i != l.rend(); /**/) {
      //cout << (i == l.rbegin()) << (i == l.rend()) << endl;
      //cout << "\tacc: " << acc << " + " << (*i);
      acc += (*i);
      //cout << " = " << acc << endl;
      //cout << "\tsize: " << l.size();
      if (acc < 0) {
	// i = l.erase(i); // sarebbe bello fare cosi`, invece...
	l.erase(--(i.base()));   // decremento il valore restituito da i.base()
	                         // ("--" e` definito ma "-" no)
	                         // eliminandolo, sembra che i stesso scorra in avanti
	//i++;                   // quindi questa riga non serve, anzi e` sbagliata
	//l.erase((++i).base()); // questo sarebbe piu` carino ma purtroppo non funziona
	                         // ma non so perche` non funziona. non ci ho capito una mazza
      } 
      else {
	(*i) = acc;
	acc = 0;
	i++;
      }
      //cout << " -> " << l.size() <<endl;;
      //cout << (i == l.rbegin()) << (i == l.rend()) << endl;
    }
    //cout << "---" << endl;
  }
  while ((acc < 0) && (l.size() > 0)); // runs at most twice
  
  return l.size();
}

int main(int argc, char**argv) {
  // IO management, input parsing, iterating over test cases

  int n;
  while(1){
    cin >> n;
    if (n == 0) break;
    list<int> l;
    for (int i = 0; i < n; i++){
      int a;
      cin >> a;
      l.push_back(a);
    }
    //printl(l);
    cout << result(l) << endl;
  }
  return 0;
}
