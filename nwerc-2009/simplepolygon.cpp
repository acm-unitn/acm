#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

#define lint long long int

using namespace std;

struct point {
    lint index;
    double x;
    double y;
    double alfa;
};

vector<point> points;

bool cmp(point a, point b) {
    return a.alfa < b.alfa;
}


int main() {
    int N;

    scanf("%d", &N);

    for (int i=0; i<N; i++) {
        point base;
        base.x = 0;
        base.y = 0;

        int p;
        scanf("%d", &p);

        points.clear();
        points.resize(p);

        for (int j=0; j<p; j++) {
            int x, y;

            scanf("%d %d", &x, &y);

            base.x += ((double) x) / p;
            base.y += ((double) y) / p;

            points[j].index = j;
            points[j].x = x;
            points[j].y = y;
        }

        //printf("base.x=%f base.y=%f\n", base.x, base.y);

        for (int j=0; j<p; j++) {
            points[j].alfa = atan2((double) (points[j].x - base.x),
                                   (double) (points[j].y - base.y));
            //printf("point %d alfa=%f\n", j, points[j].alfa);
        }

        sort(points.begin(), points.end(), cmp);

        for (int j=0; j<p; j++) {
            printf("%lld ", points[j].index);
        }
        printf("\n");

    }

    return 0;
}
