// Author: fox
// Writing time: ~25min


#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;


bool cmp(pair<int,int> i, pair<int,int> j) {
    if (i.second == j.second) {
        return i.first < j.first;
    }
    else {
        return j.second < i.second;
    }
}


int main() {
    int N;
    int price, people;
    vector<pair<int,int> > max_amount;
    int result[100];

    scanf("%d\n", &N);

    for (int i=0; i<N; i++) {
        scanf("%d %d", &price, &people);
        for (int j=0; j<people; j++) {
            int tmp;
            pair<int,int> p;
            scanf("%d", &tmp);
            p.first = j;
            p.second = tmp;
            max_amount.push_back(p);
        }
        sort(max_amount.begin(), max_amount.end(), cmp);

        //printf("----------------\n");
        //for (int j=0; j<people; j++) {
            //printf("%d %d\n", max_amount[j].first, max_amount[j].second);
        //}
        //printf("----------------\n");

        int people_left = people;

        for (int j=0; j<people; j++) {
            // for every iteration we decide how much a person has to pay
            int current_amount = price / people_left;
            pair<int,int> element = max_amount.back();
            max_amount.pop_back();
            int pays = min(element.second, current_amount);
            price -= pays;
            people_left--;
            result[element.first] = pays;
            //printf("Element number %d has to pay %d out of %d\n",
                   //element.first, pays, element.second);
        }

        if (price != 0) {
            printf("IMPOSSIBLE\n");
        }
        else {
            // print result
            printf("%d", result[0]);
            for (int j=1; j<people; j++) {
                printf(" %d", result[j]);
            }
            printf("\n");
        }
    }
}
