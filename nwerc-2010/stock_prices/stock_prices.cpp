#include <cstdio>
#include <queue>
#include <malloc.h>
#include <string.h>

using namespace std;

struct sell_order {
  int price;
  int *num;

  sell_order(int price, int num) {
    this->num = new int;
    *this->num = num;
    this->price = price;
  }

  //~sell_order() {
  //  delete this->num;
  //}
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
  int *num;

  buy_order(int price, int num) {
    this->num = new int;
    *this->num = num;
    this->price = price;
  }

  //~buy_order() {
  //  delete this->num;
  //}
};

bool operator==(const buy_order& so1, const buy_order& so2) {
  return so1.price==so2.price;
}
bool operator<(const buy_order& so1, const buy_order& so2) {
  return so1.price<so2.price;
}
bool operator>(const buy_order& so1, const buy_order& so2) {
  return so1.price>so2.price;
}

priority_queue<buy_order> buy_heap;
priority_queue<sell_order> sell_heap;

int main()
{
  char otype[5];
  int t, n,tmp,num;
  int stock_price=-1;
  buy_order *b;
  sell_order *s;

  scanf("%d",&t);
  for (int k=0; k<t; k++) {
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
      scanf("%s %d shares at %d",otype,&num,&tmp);
      //printf("%s %d shares at %d\n",otype,num,tmp);
      if (strlen(otype)==3) {
	b = new buy_order(tmp, num);
        buy_heap.push(*b);
      }
      else {
        s = new sell_order(tmp, num);
        sell_heap.push(*s);
      }
      while (!buy_heap.empty() &&
	     !sell_heap.empty() &&
	     buy_heap.top().price >= sell_heap.top().price)
      {
	stock_price = sell_heap.top().price;
	if (*buy_heap.top().num == *sell_heap.top().num)
	{
	  buy_heap.pop();
	  sell_heap.pop();
	}
	else if (*buy_heap.top().num > *sell_heap.top().num)
	{
	  *buy_heap.top().num -= *sell_heap.top().num;
	  sell_heap.pop();
	}
	else
	{
	  *sell_heap.top().num -= *buy_heap.top().num;
	  buy_heap.pop();
	}
      }
      if (buy_heap.empty() && sell_heap.empty())
	  printf("- - %d\n",stock_price);
      else if (buy_heap.empty())
      {
        if(stock_price == -1)
          printf("%d - -\n",sell_heap.top().price);
        else
          printf("%d - %d\n",sell_heap.top().price,stock_price);
      }
      else if (sell_heap.empty())
      {
        if(stock_price == -1)
          printf("- %d -\n",buy_heap.top().price);
        else
          printf("- %d %d\n",buy_heap.top().price,stock_price);
      }
      else
      {
	if(stock_price == -1)
	  printf("%d %d -\n",sell_heap.top().price,
	                    buy_heap.top().price);
	else
	  printf("%d %d %d\n",sell_heap.top().price,
			    buy_heap.top().price,stock_price);
      }
    }
    stock_price = -1;
    while (!sell_heap.empty())
      sell_heap.pop();
    while (!buy_heap.empty())
      buy_heap.pop();
  }
}
