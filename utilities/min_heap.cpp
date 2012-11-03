#include <cstdio>
#include <queue>
#include <cstdlib>
#include <time.h>

using namespace std;

struct point {
  int x, y, price;

  point(int x, int y, int price) {
    this->x = x;
    this->y = y;
    this->price = price;
  }

  point() {}
};

bool by_price(const point& a, const point& b)
{
	return a.price > b.price;
}

priority_queue<point,
               vector<point>,
               bool(*)(const point&,const point&)> q(&by_price);

int main()
{
  int a;
  srand ( time(NULL) );
  for (int i=0; i<15; i++) {
    a = rand() %50 -25;
    printf("pusho: %d\n",a);
    q.push(point(0,0,a));
  }
  printf("\n");
  while(!q.empty())
  {
    printf("poppo: %d\n",q.top().price);
    q.pop();
  }
  return 0;
}
