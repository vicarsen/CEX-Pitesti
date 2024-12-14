#include <stdio.h>
#include <math.h>
 
#define NMAX 100489
 
int n, m;
int a[NMAX], next[NMAX], d[NMAX], last[NMAX];
 
int nb, bs;
 
inline int min(int a, int b)
{
  return (a < b ? a : b);
}
 
inline int max(int a, int b)
{
  return (a > b ? a : b);
}
 
void update_block(int block, int start = -1)
{
  int r = min((block + 1) * bs, n), l = block * bs;
  
  if(start == -1)
    start = r - 1;

  for(int i = start; i >= l; i--)
  {
    if(next[i] >= r)
    {
      d[i] = 1;
      last[i] = i;
    }
    else
    {
      d[i] = 1 + d[next[i]];
      last[i] = last[next[i]];
    }
  }
}
 
int main()
{
  scanf("%d %d", &n, &m);
  for(int i = 0; i < n; i++)
  {
    scanf("%d", &a[i]);
    next[i] = i + a[i];
  }
  
  nb = max(1, sqrt(n) * 0.6f);
  bs = n / nb + 1;

  for(int block = nb - 1; block >= 0; block--)
    update_block(block);
  
  for(int i = 0; i < m; i++)
  {
    int t;
    scanf("%d", &t);
    if(t == 0)
    {
      int x, y;
      scanf("%d %d", &x, &y);
      x--;

      a[x] = y;
      next[x] = x + y;
      update_block(x / bs, x);
    }
    else
    {
      int x;
      scanf("%d", &x);
      x--;

      int s = 0, l = x;
      while(x < n)
      {
        s += d[x];
        l = last[x];
        x = next[l];
      }

      printf("%d %d\n", l + 1, s);
    }
  }
}
