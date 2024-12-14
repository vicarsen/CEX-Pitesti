#include <bits/stdc++.h>

#define NMAX 30000
#define QMAX 200000

using namespace std;

int n, a[NMAX];

int q;
struct query_t {
  int l, r, ans;
} query[QMAX];

int order[QMAX];

unordered_map<int, int> mp;

void insert(int i)
{
  mp[a[i]]++;
}

void erase(int i)
{
  mp[a[i]]--;
  if(mp[a[i]] == 0) {
    mp.erase(a[i]);
  }
}

int calculate()
{
  return mp.size();
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  cin >> q;
  for (int i = 0; i < q; i++) {
    cin >> query[i].l >> query[i].r;
    query[i].l--; query[i].r--;
    order[i] = i;
  }

  int bs = max(1, (int) sqrt(n));

  sort(order, order + q, [&](int i, int j) {
    int bi = query[i].l / bs;
    int bj = query[j].l / bs;

    return bi < bj || (bi == bj && query[i].r > query[j].r);
  });

  int l = 0, r = -1;

  for (int k = 0; k < q; k++) {
    int i = order[k];

    while (r < query[i].r) {
      insert(++r);
    }

    while (query[i].l < l) {
      insert(--l);
    }

    while (query[i].r < r) {
      erase(r--);
    }

    while (l < query[i].l) {
      erase(l++);
    }

    query[i].ans = calculate();
  }

  for (int i = 0; i < q; i++) {
    cout << query[i].ans << "\n";
  }
  cout << "\n";
  return 0;
}

