#include <cstdio>
#include <queue>
#include <malloc.h>

using namespace std;

struct sell_order {
  int price;
  int num;
};

bool operator==(const sell_order& so1, const sell_order& so2) {
  return so1.price==so2.price;
}
bool operator<(const sell_order& so1, const sell_order& so2) {
  return so1.price>so2.price;
}
bool operator>(const sell_order& so1, const sell_order& so2) {
  return so1.price<so2.price;
}

struct buy_order {
  int price;
  int num;
};

bool operator==(const buy_order& so1, const buy_order& so2) {
  return so1.price==so2.price;
}
bool operator<(const buy_order& so1, const buy_order& so2) {
  return so1.price>so2.price;
}
bool operator>(const buy_order& so1, const buy_order& so2) {
  return so1.price<so2.price;
}

priority_queue<buy_order> buy_heap;
priority_queue<sell_order> sell_heap;

int main()
{
  int t, n,tmp;
  buy_order *b;
  sell_order *s;

  scanf("%d",&t);
  for (int k=0; k<t; k++) {
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
      b = (buy_order*) malloc(sizeof(buy_order));
      s = (sell_order*) malloc(sizeof(sell_order));
      scanf("%d",&tmp);
      b->price = tmp;
      s->price = tmp;
      buy_heap.push(*b);
      sell_heap.push(*s);
    }
  }
}
