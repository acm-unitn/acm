#include<cstdio>

#define MAX_N 200001

long long int towers[MAX_N];
int from_left[MAX_N];
int from_right[MAX_N];
int mem[MAX_N];
int n;

void read_input()
{
  scanf("%d",&n);
  for (int i=0;i<n;i++)
    scanf("%lld",towers+i);
}

//salva in from_left[i] la lunghezza della sequenza cresciente che termina in i
void compute_from_left()
{
  from_left[0] = 1;
  for (int i=1; i<n; i++)
  {
    if (towers[i] > towers[i-1])
      from_left[i] = from_left[i-1] + 1;
    else
      from_left[i] = 1;
  }
}

//salva in from_right[i] la lunghezza della sequenza cresciente che termina in i
void compute_from_right()
{
  from_right[n-1] = 1;
  for (int i=n-2; i>=0; i--)
  {
    if (towers[i] < towers[i+1])
      from_right[i] = from_right[i+1] + 1;
    else
      from_right[i] = 1;
  }
}

//ritorna l'indice del piu grande numero minore di val
int binary_search(int inizio, int fine, int val)
{
  int m;
  if (inizio>fine)
    return fine;
  else
  {
    m = (inizio+fine)/2;
    if (towers[mem[m]] < val)
      return binary_search(m+1,fine,val);
    else
      return binary_search(inizio,m-1,val);
  }
}

//ad ogni passo dell'iterazione in mem[i] viene registrata dove termina la sequenza
//lunga i che tra tutte le sequenze da 0 a i ha l'ultimo elemento piu piccolo
//ad ogni passo aggiorno mem e poi cerco in mem la sequenza piu lunga a cui posso
//collegare l'emento i
int maximum_sequence()
{
  int len, max, mem_index;
  int max_len = 0;
  for (int i=0; i<=n; i++)
    mem[i] = -1;
  for (int i=0; i<n; i++)
  {
    //lunghezza sequenza che termina in i
    len = from_left[i];
    //se non esistono sequenze lunghe len da 0 a i
    //salva i come rappresentate sequenza lunga len
    if (mem[len] == -1)
    {
      mem[len] = i;
      mem_index = len;
    }
    //se esiste una sequenza lunga len prima di i
    //se il rappresentate di quella sequenza è maggiore
    //di towers[i] allora registra i come nuovo rappresentante
    //sequenza lunga len da 0 a i
    if (towers[mem[len]] > towers[i])
      mem[len] = i;
    //cerco lunghezza sequenza piu lunga da 0 a i collegabile a i
    max = binary_search(1,mem_index,towers[i]);
    //se la lunghezza della sequenza max piu la lunghezza della sequenza che prosegue da i
    //e' maggiore di quelle passata salvala come lunghezza massima
    if (max + from_right[i] > max_len)
      max_len = max + from_right[i];

  }
  return max_len;
}

int main()
{
  int z;
  int l;
  scanf("%d",&z);
  for (int k=0; k<z; k++)
  {
    read_input();
    compute_from_left();
    compute_from_right();
    l = maximum_sequence();
    printf("%d\n",l);
  }
  return 0;
}
