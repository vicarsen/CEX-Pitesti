#include <bits/stdc++.h>

#define NMAX 50000
#define SQRTNMAX 250

#define INF 0x3f3f3f3f

using namespace std;

int n, a[NMAX], m, block[SQRTNMAX];

int nb, bs;

void update_block(int b)
{
  int l = b * bs, r = min(n, (b + 1) * bs);

  block[b] = -INF;
  for (int i = l; i < r; i++) {
    block[b] = max(block[b], a[i]);
  }
}

void update(int i, int x)
{
  a[i] = x;
  update_block(i / bs);
}

int query(int l, int r)
{
  cout << "Query: " << l << " " << r << "\n";

  int bl = l / bs;
  int br = r / bs;

  int ans = -INF;
  for (int i = bl + 1; i < br; i++) {
    ans = max(ans, block[i]);
  }

  for (int i = l; i < (bl + 1) * bs; i++) {
    ans = max(ans, a[i]);
  }

  for (int i = br * bs; i < r; i++) {
    ans = max(ans, a[i]);
  }

  return ans;
}

int main()
{
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  nb = max(1, (int) sqrt(n));
  bs = n / nb + 1;

  cin >> m;
  for (int i = 0; i < m; i++) {
    int type, x, y;
    cin >> type >> x >> y;

    if (type == 0) {
      update(x - 1, y);
    } else {
      cout << query(x - 1, y) << '\n';
    }
  }

  return 0;
}

