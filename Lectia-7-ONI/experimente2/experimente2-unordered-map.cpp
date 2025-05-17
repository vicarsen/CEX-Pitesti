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

    unordered_map<int, bool> stage;
    stage.reserve(n);

    bool found0 = false, found_any = false;

    stage[0] = 0;
    for (int i = 0, x = 0; i < n; i++) {
      x ^= a[i];

      if (stage[x] != 0) {
        found_any = true;
        found0 = (found0 || x == 0);
      }

      auto it = stage.find(x ^ eor);
      if (it != stage.end())
        it->second = 1;

      it = stage.find(x);
      if (it == stage.end())
        stage[x] = 0;
    }

    if (c == 1) {
      cout << (found0 ? "DA\n" : "NU\n");
    } else {
      cout << (found_any ? "DA\n" : "NU\n");
    }
  }

  return 0;
}
