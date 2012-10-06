#include<cstdio>
#include<map>
#include<string>
#include<cstring>
#include<assert.h>
#include<vector>

//#define DEBUG
#ifdef DEBUG
#define print(...) fprintf(stdout, __VA_ARGS__)
#else
#define print(...)
#endif

#define MAX_L 300000

using namespace std;

struct nodo {
  int val;
  int tipo;
  int pos;
  char str[5];
  nodo* sx;
  nodo* dx;
};

typedef nodo* tree;
typedef pair<int,pair<int,int> > key;
typedef map<key,int> registro;
int n, out_id;
map<string,int> diz;
registro reg;
vector<tree> indici;
char s[MAX_L];
char out[MAX_L];
int idx;
int word_number;
int type_number;
tree nullo;
int number;

int insert_word(char* s)
{
  string str = string(s);
  map<string,int>::iterator i = diz.find(str);
  if (i == diz.end())
  {
    word_number++;
    diz[str] = word_number;
    return word_number;
  }
  else
    return i->second;
}

int registra(tree t)
{
  int ret;
  key k = key(t->val,pair<int,int>(t->sx->tipo,t->dx->tipo));
  registro::iterator i = reg.find(k);
  if (i==reg.end())
  {
    reg[k] = type_number;
    indici.push_back(t);
    ret = type_number;
    assert(indici[type_number] == t);
    type_number++;
  }
  else
    ret = i->second;
  return ret;
}

tree parse()
{
  char temp[5];
  int id=0;
  tree ret = new(nodo);
  bool done = false;
  //print("chiamato a %d\n",idx);
  while(!done)
  {
    //print("leggo %c\n",s[idx]);
    if (s[idx]=='(')
    {
      idx++; //salto la parentesi
      temp[id]='\0';
      strcpy(ret->str,temp);
      ret->val = insert_word(temp);
      ret->sx = parse();
      assert(s[idx]==',');
      idx++; //salto la virgola
      ret->dx = parse();
      assert(s[idx]==')');
      idx++; //salto la parentesi
      done = true;
      ret->tipo = registra(ret);
    }
    else if (s[idx]==',' || s[idx]==')' || s[idx]=='\0')
    {
      temp[id]='\0';
      strcpy(ret->str,temp);
      ret->val = insert_word(temp);
      ret->sx = nullo;
      ret->dx = nullo;
      done = true;
      ret->tipo = registra(ret);
    }
    else
    {
      temp[id] = s[idx];
      id++;
      idx++;
    }
  }
  return ret;
}

void print_tree(tree t)
{
  if (t->sx->tipo != -1)
  {
    print("%d(",t->tipo);
    print_tree(t->sx);
    print(",");
    print_tree(t->dx);
    print(")");
  }
  else
    print("%d",t->tipo);
}

void trasforma_grafo(tree t)
{
  print("analizzo nodo %d\n",t->tipo);
  if (t->sx->tipo!=-1)
  {
    if (indici[t->sx->tipo]!=t->sx)
    {
      print("figlio sinistro %d diventa un altro\n",t->tipo);
      t->sx = indici[t->sx->tipo];
    }
    else
      trasforma_grafo(t->sx);
  }
  if (t->dx->tipo!=-1)
  {
    if (indici[t->dx->tipo]!=t->dx)
    {
      print("figlio destro %d diventa un altro\n",t->tipo);
      t->dx = indici[t->dx->tipo];
    }
    else
      trasforma_grafo(t->dx);
  }
}

void print_graph(tree t)
{
  print("analizzo nodo %d\n",t->tipo);
  if (t->sx->tipo!=-1)
  {
    assert(t->dx->tipo!=-1);
    t->pos = number;
    number++;
    sprintf(&(out[out_id]),"%s",t->str);
    while (out[out_id] != '\0')
      out_id++;
    out[out_id] = '(';
    out_id++;
    if (indici[t->sx->tipo]!=t->sx)
    {
      print("figlio sinistro %d diventa un altro\n",t->tipo);
      sprintf(&(out[out_id]),"%d",indici[t->sx->tipo]->pos);
      while (out[out_id] != '\0')
        out_id++;
    }
    else
      print_graph(t->sx);
    out[out_id] = ',';
    out_id++;
    if (indici[t->dx->tipo]!=t->dx)
    {
      print("figlio destro %d diventa un altro\n",t->tipo);
      sprintf(&(out[out_id]),"%d",indici[t->dx->tipo]->pos);
      while (out[out_id] != '\0')
        out_id++;
    }
    else
      print_graph(t->dx);
    out[out_id] = ')';
    out_id++;
  }
  else
  {
    t->pos = number;
    number++;
    sprintf(&(out[out_id]),"%s",t->str);
    while (out[out_id] != '\0')
      out_id++;
  }
}

int main()
{
  int c;
  tree t;
  nullo = new nodo();
  nullo->tipo = -1;
  scanf("%d\n",&c);
  for (int k=0; k<c; k++)
  {
    scanf("%s\n",s);
    print("letto %s\n",s);
    n = strlen(s);
    idx = 0;
    word_number = 0;
    type_number = 0;
    reg.erase(reg.begin(),reg.end());
    diz.erase(diz.begin(),diz.end());
    indici.erase(indici.begin(),indici.end());
    t = parse();
    out_id = 0;
    print("\n");
    print_tree(t);
    print("\n");
    number = 1;
    print_graph(t);
    out[out_id] = '\0';
    printf("%s\n",out);
    //trasforma_grafo(t);
    //print("\n");
    //print_tree(t);
    //print("\n");

  }
  return 0;
}
