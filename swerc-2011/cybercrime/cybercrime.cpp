#include<cstdio>
#include<algorithm>
#include<utility>
#include<vector>
#include<cmath>

#define MAX_N 100000
#define MAX_Q 50000
#define min(a,b) (((a) < (b)) ? (a) : (b))

using namespace std;

//ciambella ordinata secondo x
typedef pair<double, double> ciambella;
//ciambella ordinata secondo y
typedef pair<double, double> ciamb_rev;

struct tree {
  ciambella val;
  vector<ciamb_rev> subtree;
  tree *dx;
  tree *sx;
};

tree *db;
ciambella dati_db[MAX_N];
ciambella dati[MAX_Q];
double output[MAX_Q];

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

void rotate(long int x, long int y, double *xp, double *yp)
{
  //ruota 45 gradi
  (*xp) = x * pow(2,0.5)/2.0 - y * pow(2,0.5)/2.0;
  (*yp) = x * pow(2,0.5)/2.0 + y * pow(2,0.5)/2.0;
}

void merge(vector<ciamb_rev> *dest,
	   vector<ciamb_rev> *a,
	   vector<ciamb_rev> *b,
	   ciamb_rev val)
{
  bool inserted;
  int i, j, k;
  i = 0; j = 0; k=0; inserted=false;
  dest->resize(a->size()+b->size()+1);
  //merge delle due liste, inserisce val al punto giusto
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
    //costruisci nodo
    nodo = new tree();
    nodo->val = dati_db[m];
    nodo->sx = build_tree(inizio,m-1);
    nodo->dx = build_tree(m+1,fine);
    //merge i valori dei figli
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

/*
void print_tree(tree* a, int lev)
{
  if (a!=NULL)
  {
    print_tree(a->sx,lev+1);
    printf("(%f %f) lev. %d----> ",a->val.first,a->val.second,lev);
    for (int i=0; i<(int)a->subtree.size(); i++)
      printf("(%f %f) ",a->subtree[i].first,a->subtree[i].second);
    printf("\n");
    print_tree(a->dx,lev+1);
  }
}*/



int bin_search(vector<ciamb_rev> lista, int inizio, int fine,double val)
{
  int m;
  if (inizio==fine)
    return inizio;
  else
  {
    m = (inizio+fine)/2;
    if (lista[m].second==val)
      return m;
    else
    {
      if (lista[m].second>val)
	return bin_search(lista,inizio,m-1,val);
      else
	return bin_search(lista,m+1,fine,val);
    }
  }
}

int search_su_y(vector<ciamb_rev> *lista, double y1, double y2, vector<ciamb_rev> *elementi=NULL)
{
  int inizio, fine;
  //printf("cerco sulla y, intervallo %lf %lf\n",y1,y2);
  //printf("lista valori\n");
  //for (int i=0; i<(int)(*lista).size();  i++)
    //printf("(%lf %lf) ",(*lista)[i].first,(*lista)[i].second);
  //printf("\n");
  inizio = bin_search((*lista),0,(int)(*lista).size()-1,y1);
  if ((*lista)[inizio].second <= y1)
    inizio++;
  fine = bin_search((*lista),0,(int)(*lista).size()-1,y2);
  if ((*lista)[fine].second >= y2)
    fine--;
  //printf("inizio %d fine %d\n",inizio,fine);
  if (elementi != NULL)
    for (int i=inizio; i<=fine; i++)
      (*elementi).push_back((*lista)[i]);
  return fine-inizio+1;
}

int my_search(double x1, double x2, double y1, double y2, bool solo_quanti, vector<ciamb_rev> *elementi=NULL)
{
  int quanti;
  tree *nodo;
  tree *radice = db;
  //printf("cerco in intervallo x (%lf,%lf) y (%lf,%lf)\n",x1,x2,y1,y2);
  //trovo radice che ha nel sottoalbero sinistro x1 e nel destro x2
  while (radice!=NULL && !(radice->val.first > x1 && radice->val.first < x2))
  {
    if (radice->val.first < x1)
      radice = radice->dx;
    else
      radice = radice->sx;
  }
  if (radice == NULL)
  {
    //printf("nell'intervallo delle x cercato non casca neanche un nodo\n");
    return 0; //nell'intervallo delle x cercato non casca neanche un nodo
  }
  //printf("la radice è: %lf %lf\n",radice->val.first,radice->val.second);
  quanti = 0;
  if ((radice->val.second > y1)&& (radice->val.second < y2))
  {
    //printf("la radice è nell'intervallo\n");
    if (!solo_quanti)
      (*elementi).push_back(radice->val);
    quanti++;
  }
  //visito a sinistra
  nodo = radice->sx;
  //printf("visito a sinistra\n");
  while (nodo != NULL)
  {
    //printf("visito ciambella %lf %lf\n",nodo->val.first,nodo->val.second);
    if (nodo->val.first > x1) //vado a sinistra
    {
      //printf("vado a sinistra\n");
      if ((nodo->val.second > y1)&& (nodo->val.second < y2))
      {
	//printf("la ciambella visitata è nell'intervallo\n");
	if (!solo_quanti)
	  (*elementi).push_back(nodo->val);
	quanti++;
      }
      if (nodo->dx != NULL)
      {
	//aggiungo tutti i nodi nel sottoalbero destro nell'intervallo y
	if (!solo_quanti)
	  quanti += search_su_y(&nodo->dx->subtree,y1,y2,elementi);
	else
	  quanti += search_su_y(&nodo->dx->subtree,y1,y2);
      }
      nodo = nodo->sx;
    }
    else //vado a destra
    {
      //printf("vado a destra");
      nodo = nodo->dx;
    }
  }
  //printf("quanti %d\n",quanti);
  //visito a destra;
  nodo = radice->dx;
  //printf("visito a destra\n");
  while (nodo != NULL)
  {
    //printf("visito ciambella %lf %lf\n",nodo->val.first,nodo->val.second);
     if (nodo->val.first < x2) //vado a destra
    {
      if ((nodo->val.second > y1)&& (nodo->val.second < y2))
      {
	if (!solo_quanti)
	  (*elementi).push_back(nodo->val);
	//printf("la ciambella visitata è nell'intervallo\n");
	quanti++;
      }
      //printf("vado a destra\n");
      if (nodo->sx != NULL)
      {
	//aggiungo tutti i nodi nel sottoalbero sinistro nell'intervallo y
	if (!solo_quanti)
	  quanti += search_su_y(&nodo->sx->subtree,y1,y2,elementi);
	else
	  quanti += search_su_y(&nodo->sx->subtree,y1,y2);
      }
      nodo = nodo->dx;
    }
    else //vado a sinistra
    {
      //printf("vado a sinistra\n");
      nodo = nodo->dx;
    }
  }
  //printf("quanti %d\n",quanti);
  return quanti;
}


ciambella cerca_ciambella(ciambella val,double quadrato)
{
  double x1, x2, y1, y2, min;
  vector<ciamb_rev> elementi;
  ciambella out;
  x1 = val.first - quadrato/2.0;
  x2 = val.first + quadrato/2.0;
  y1 = val.second - quadrato/2.0;
  y2 = val.second + quadrato/2.0;
  //printf("TROVATO!!! è nell'intevallo x (%lf %lf) y (%lf %lf)\n",x1,x2,y1,y2);
  my_search(x1,x2,y1,y2,false,&elementi);
  min = abs(val.first-elementi[0].first) + abs(val.second-elementi[0].second);
  out = elementi[0];
  for (int i=1; i<(int) elementi.size(); i++)
    if (min > abs(val.first-elementi[i].first) + abs(val.second-elementi[i].second))
    {
      min = abs(val.first-elementi[i].first) + abs(val.second-elementi[i].second);
      out = elementi[i];
    }
  //printf(">>>>>>> la più simile per %lf %lf è %lf %lf\n",val.first,val.second,out.first,out.second);
  return out;
}

ciambella trova_simile(ciambella val)
{
  int quanti;
  double x1, x2, y1, y2;
  //inizio con un quadrato grande due, centrato in val
  double quadrato_esterno, quadrato_interno, quadrato;
  quadrato_esterno = 2.0;
  quadrato_interno = 2.0;
  //modifico dimensioni del quadrato interno
  //finche non contiene meno di 5 ciambelle
  quanti = 1;
  while(quanti != 0)
  {
    quadrato_interno /=2;
    x1 = val.first - quadrato_interno/2.0;
    x2 = val.first + quadrato_interno/2.0;
    y1 = val.second - quadrato_interno/2.0;
    y2 = val.second + quadrato_interno/2.0;
    quanti = my_search(x1,x2,y1,y2,true);
    if (quanti > 0 && quanti <= 4)
      return cerca_ciambella(val,quadrato_interno);
  }
  //modifico dimensioni del quadrato esterno
  //finche non contiene almeno 5 ciambelle
  quanti = 0;
  while(quanti <= 4)
  {
    quadrato_esterno *=2;
    x1 = val.first - quadrato_esterno/2.0;
    x2 = val.first + quadrato_esterno/2.0;
    y1 = val.second - quadrato_esterno/2.0;
    y2 = val.second + quadrato_esterno/2.0;
    quanti = my_search(x1,x2,y1,y2,true);
    if (quanti > 0 && quanti <= 4)
      return cerca_ciambella(val,quadrato_esterno);
  }
  //printf("quadrato esterno: %lf\n",quadrato_esterno);
  //printf("quadrato interno: %lf\n",quadrato_interno);
  //modifico dimensione del quadrato finche
  //non contiene quattro o meno ciambella
  quadrato = (quadrato_esterno + quadrato_interno) / 2.0;
  quanti = my_search(x1,x2,y1,y2,true);
  while (!(quanti >= 1 && quanti <= 4))
  {
    //printf("quadrato esterno: %lf\n",quadrato_esterno);
    //printf("quadrato interno: %lf\n",quadrato_interno);
    if (quanti > 1)
      quadrato_esterno = quadrato;
    else if (quanti == 0)
      quadrato_interno = quadrato;
    quadrato = (quadrato_esterno + quadrato_interno) / 2.0;
    x1 = val.first - quadrato/2.0;
    x2 = val.first + quadrato/2.0;
    y1 = val.second - quadrato/2.0;
    y2 = val.second + quadrato/2.0;
    quanti = my_search(x1,x2,y1,y2,true);
  }
  return cerca_ciambella(val,quadrato);
}

int main()
{
  long int n, q;
  long int a, b;
  ciambella c;
  double cf, cs, df, ds;

  scanf("%li",&n);
  while (n != -1)
  {
    for (int i=0; i<n; i++)
    {
      scanf("%li %li",&a,&b);
      rotate(a,b,&dati_db[i].first,&dati_db[i].second);
    }
    sort(dati_db,dati_db+n);
    db = build_tree(0,n-1);
    //print_tree(db,0);
    //printf("\n");
    scanf("%li",&q);
    for (int i=0; i<q; i++)
    {
      scanf("%li %li",&a,&b);
      rotate(a,b,&dati[i].first,&dati[i].second);
    }
    for (int i=0; i<q; i++)
    {
      //printf("Trova simile per ciambella %lf %lf\n",dati[i].first,dati[i].second);
      c = trova_simile(dati[i]);
      cf = c.first * pow(2,0.5)/2.0 + c.second * pow(2,0.5)/2.0;
      cs = c.first * pow(2,0.5)/2.0 * -1.0 + c.second * pow(2,0.5)/2.0;
      df = dati[i].first * pow(2,0.5)/2.0 + dati[i].second * pow(2,0.5)/2.0;
      ds = dati[i].first * pow(2,0.5)/2.0 * -1.0 + dati[i].second * pow(2,0.5)/2.0;
      //printf(">>>>>>> la più simile per %lf %lf è %lf %lf\n",dati[i].first,dati[i].second,c.first,c.second);
      output[i] = abs(cf-df) + abs(cs-ds);
    }
    for (int i=0; i<q; i++)
      printf("%lf\n",output[i]);
    printf("\n");
    scanf("%li",&n);
  }
  exit(0);
}
