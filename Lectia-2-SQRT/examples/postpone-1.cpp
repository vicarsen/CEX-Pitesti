#include <bits/stdc++.h>

#define NMAX 100000
#define QMAX 100000
#define SQRTQMAX 320

using namespace std;

int n, a[NMAX], q, sum[NMAX + 1];

struct update_t {
  int l, r, x;
} upd[SQRTQMAX];
int m, step;

void build()
{
  sum[0] = a[0];
  for (int i = 1; i < n; i++) {
    sum[i] = sum[i - 1] + a[i];
  }
}

void update(int l, int r, int x)
{
  upd[m++] = { l, r, x };
  if (m >= step) {
    for (int i = 0; i < n; i++) {
      sum[i] = 0;
    }
    
    for (int k = 0; k < m; k++) {
      sum[upd[k].l] += upd[k].x;
      sum[upd[k].r + 1] -= upd[k].x;
    }
    
    m = 0;

    a[0] += sum[0];
    for (int i = 1; i < n; i++) {
      sum[i] += sum[i - 1];
      a[i] += sum[i];
    }

    build();
  }
}

int query(int l, int r)
{
  int ans = sum[r] - (l > 0 ? sum[l - 1] : 0);

  for (int i = 0; i < m; i++) {
    int l2 = max(l, upd[i].l);
    int r2 = min(r, upd[i].r);

    if (l2 <= r2) {
      ans += upd[i].x * (r2 - l2 + 1);
    }
  }

  return ans;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  
  build();

  cin >> q;
  step = max(1, (int) sqrt(q));
  
  for (int i = 0; i < q; i++) {
    int type;
    cin >> type;
    if (type == 1) {
      int l, r;
      cin >> l >> r;
      l--; r--;

      cout << query(l, r) << '\n';
    } else {
      int l, r, x;
      cin >> l >> r >> x;
      l--; r--;

      update(l, r, x);
    }
  }

  return 0;
}

