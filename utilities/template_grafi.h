#ifndef TEMPLATE_GRAFI_H
#define TEMPLATE_GRAFI_H

#define MAX_N 10000

#include <vector>

using namespace std;

struct node;

vector<node> graph;

void dfs(int node);

void bfs(int start_node);

void full_dfs();

void full_bfs();

#endif
