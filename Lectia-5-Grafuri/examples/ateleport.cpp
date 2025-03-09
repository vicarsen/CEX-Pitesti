#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

#define NMAX 10000
#define KMAX 10

using namespace std;

struct state {
  int u;
  int k;

  inline bool operator<(const state &other) const noexcept {
    return u < other.u;
  }
};

int n, m, p, l, k;
vector<pair<int, int>> g[NMAX];
vector<int> t[NMAX];

int d[NMAX][KMAX + 1];

int main() {
  ifstream cin("ateleport.in");
  ofstream cout("ateleport.out");

  cin >> n >> m >> p >> l >> k;
  for (int i = 0; i < m; i++) {
    int x, y, t;
    cin >> x >> y >> t;
    x--;
    y--;

    g[x].emplace_back(y, t);
    g[y].emplace_back(x, t);
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= k; j++) {
      d[i][j] = INF;
    }
  }

  for (int i = 0; i < n; i++) {
    queue<int> q;
    q.push(i);
    d[i][0] = 0;

    while (!q.empty()) {
      int u = q.front();
      q.pop();

      for (auto [v, _] : g[u]) {
        if (d[v][0] == INF) {
          d[v][0] = d[u][0] + 1;
          t[i].push_back(v);

          if (d[v][0] < l) {
            q.push(v);
          }
        }
      }
    }

    for (auto v : t[i]) {
      d[v][0] = INF;
    }

    d[i][0] = INF;
  }

  set<pair<int, state>> q;
  q.emplace(0, state{0, 0});
  d[0][0] = 0;

  while (!q.empty()) {
    state s = q.begin()->second;
    q.erase(q.begin());

    if (s.k < k) {
      for (auto v : t[s.u]) {
        if (d[v][s.k + 1] > d[s.u][s.k] + p) {
          q.erase({d[v][s.k + 1], state{v, s.k + 1}});
          d[v][s.k + 1] = d[s.u][s.k] + p;
          q.emplace(d[v][s.k + 1], state{v, s.k + 1});
        }
      }
    }

    for (auto [v, w] : g[s.u]) {
      if (d[v][s.k] > d[s.u][s.k] + w) {
        q.erase({d[v][s.k], state{v, s.k}});
        d[v][s.k] = d[s.u][s.k] + w;
        q.emplace(d[v][s.k], state{v, s.k});
      }
    }
  }

  int ans = d[n - 1][0];
  for (int i = 1; i <= k; i++) {
    ans = min(ans, d[n - 1][i]);
  }

  cout << ans << "\n";
  return 0;
}
