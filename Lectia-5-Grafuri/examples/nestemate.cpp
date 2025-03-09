#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

#define NMAX 100000
#define XMAX 500000

using namespace std;

vector<int> g[XMAX];
int d[XMAX], x[NMAX], y[NMAX], z[NMAX];

int main() {
  ifstream cin("nestemate.in");
  ofstream cout("nestemate.out");

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;

    int a, b;
    cin >> a >> b;
    a--;
    b--;

    for (int i = 0; i < n; i++) {
      cin >> x[i] >> y[i] >> z[i];
      x[i]--;
      y[i]--;
      z[i]--;

      g[x[i]].push_back(y[i]);
      g[x[i]].push_back(z[i]);

      g[y[i]].push_back(x[i]);
      g[y[i]].push_back(z[i]);

      g[z[i]].push_back(x[i]);
      g[z[i]].push_back(y[i]);

      d[x[i]] = INF;
      d[y[i]] = INF;
      d[z[i]] = INF;
    }

    queue<int> q;
    q.push(x[a]);
    q.push(y[a]);
    q.push(z[a]);
    d[x[a]] = 0;
    d[y[a]] = 0;
    d[z[a]] = 0;

    while (!q.empty()) {
      int u = q.front();
      q.pop();

      for (auto v : g[u]) {
        if (d[v] == INF) {
          q.push(v);
          d[v] = d[u] + 1;
        }
      }
    }

    int ans = d[x[b]];
    ans = min(ans, d[y[b]]);
    ans = min(ans, d[z[b]]);

    cout << (ans != INF ? ans + 1 : -1) << "\n";

    for (int i = 0; i < n; i++) {
      g[x[i]].clear();
      g[y[i]].clear();
      g[z[i]].clear();
    }
  }

  return 0;
}
