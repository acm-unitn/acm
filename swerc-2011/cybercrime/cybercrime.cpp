#include<cstdio>
#include<algorithm>
#include<utility>
#include<vector>

#define MAX_N 100000
#define MAX_Q 50000
#define min(a,b) (((a) < (b)) ? (a) : (b))

using namespace std;

typedef pair<long int, long int> ciambella;
typedef pair<long int, long int> ciamb_rev;

struct tree {
  ciambella val;
  vector<ciamb_rev> subtree;
  tree *dx;
  tree *sx;
};

ciambella dati_db[MAX_N];
ciambella dati[MAX_Q];
long int output[MAX_Q];

bool operator<(const ciamb_rev& c1, const ciamb_rev& c2)
{
  return c1.second < c2.second;
}

bool operator<=(const ciamb_rev& c1, const ciamb_rev& c2)
{
  return (c1 < c2) || (c1 == c2);
}

bool operator>(const ciamb_rev& c1, const ciamb_rev& c2)
{
  return c1.second > c2.second;
}

bool operator>=(const ciamb_rev& c1, const ciamb_rev& c2)
{
  return (c1 > c2) || (c1 == c2);
}

/*
int bin_search(int val, int inizio,int fine)
{
  int m;

  if (inizio==fine)
    return abs(db[inizio]-val);
  else
  {
    m = (inizio+fine)/2;
    if (db[m]==val)
      return 0;
    else
      return min(bin_search(val,inizio,m),bin_search(val,m+1,fine));
  }
  }*/

void merge(vector<ciamb_rev> *dest,
	   vector<ciamb_rev> *a, 
	   vector<ciamb_rev> *b,
	   ciamb_rev val)
{
  bool inserted;
  int i, j, k;
  i = 0; j = 0; k=0; inserted=false;
  dest->resize(a->size()+b->size()+1);
  while (i < (int)a->size() && j < (int)b->size())
  {
    if (val<(*a)[i] && val<(*b)[i] && !inserted)
    {
      (*dest)[k] = val;
      inserted = true;
    } 
    else if ((*a)[i] <= (*b)[j])
    {
      (*dest)[k] = (*a)[i];
      i++;
    }
    else
    {
      (*dest)[k] = (*b)[j];
      j++;
    }
    k++;
  }
  for (int h=i; h<(int)a->size(); h++)
  {
    if (val<(*a)[h] && !inserted)
    {
      (*dest)[k] = val;
      inserted = true;
      k++;
    }
    (*dest)[k] = (*a)[h];
    k++;
  }
  for (int h=j; h<(int)b->size(); h++)
  {
    if (val<(*b)[h] && !inserted)
    {
      (*dest)[k] = val;
      inserted = true;
      k++;
    }
    (*dest)[k] = (*b)[h];
    k++;
  }
  if (!inserted)
  {
    (*dest)[k] = val;
  }
}

tree* build_tree(int inizio, int fine)
{
  int m;
  tree *nodo;
  if (inizio > fine)
    return NULL;
  else 
  {
    m = (inizio+fine) / 2;
    nodo = new tree();
    nodo->val = dati_db[m];
    nodo->sx = build_tree(inizio,m-1);
    nodo->dx = build_tree(m+1,fine);
    if (nodo->sx == NULL && nodo->dx == NULL)
      nodo->subtree.push_back(nodo->val);
    else if (nodo->sx == NULL)
      merge(&nodo->subtree,new vector<ciambella>(),&nodo->dx->subtree,nodo->val);
    else if (nodo->dx == NULL)
      merge(&nodo->subtree,&nodo->sx->subtree,new vector<ciambella>(),nodo->val);
    else
      merge(&nodo->subtree,&nodo->sx->subtree,&nodo->dx->subtree,nodo->val);
    return nodo;
  }
}

void print_tree(tree* a, int lev)
{
  if (a!=NULL)
  {
    print_tree(a->sx,lev+1);
    printf("(%ld %ld) lev. %d----> ",a->val.first,a->val.second,lev);
    for (int i=0; i<(int)a->subtree.size(); i++)
      printf("(%ld %ld) ",a->subtree[i].first,a->subtree[i].second);
    printf("\n");
    print_tree(a->dx,lev+1);
  }
}

int main()
{
  FILE *inp, *out;
  long int n, q;
  tree *db;

  inp = fopen("input.txt","r");
  out = fopen("output.txt","w");
  fscanf(inp,"%li",&n);
  while (n != -1)
  {    
    for (int i=0; i<n; i++)
    {
      fscanf(inp,"%li %li",&dati_db[i].first,&dati_db[i].second);
    }
    sort(dati_db,dati_db+n);
    db = build_tree(0,n-1);
    print_tree(db,0);
    printf("\n");
    fscanf(inp,"%li",&q);
    for (int i=0; i<q; i++)
    {
      fscanf(inp,"%li %li",&dati[i].first,&dati[i].second);
    }
    for (int i=0; i<q; i++)
    {
      output[i] = 1;
    }
    for (int i=0; i<q; i++)
      fprintf(out,"%li\n",output[i]);
    fprintf(out,"\n");
    fscanf(inp,"%li",&n);
  }
  fclose(inp);
  fclose(out);
  return 0;
}
