#include <bits/stdc++.h>

using namespace std;

int main() {
  ifstream cin("experimente2.in");
  ofstream cout("experimente2.out");

  int c, q;
  cin >> c >> q;
  for (int i = 0; i < q; i++) {
    int n;
    cin >> n;
    vector<int> a(n);

    int eor = 0;
    for (int &x : a) {
      cin >> x;
      eor ^= x;
    }

    if (eor == 0) {
      cout << "DA\n";
      continue;
    }

    set<int> found[3];
    found[0].emplace(0);

    for (int i = 0, x = 0; i < n; i++) {
      x ^= a[i];

      if (found[1].find(x) != found[1].end())
        found[2].emplace(x);

      if (found[0].find(x ^ eor) != found[0].end())
        found[1].emplace(x ^ eor);

      found[0].emplace(x);
    }

    if (c == 1) {
      cout << (found[2].find(0) != found[2].end() ? "DA\n" : "NU\n");
    } else {
      cout << (!found[2].empty() ? "DA\n" : "NU\n");
    }
  }

  return 0;
}
