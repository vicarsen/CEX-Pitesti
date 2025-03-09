#include <bits/stdc++.h>

#define NMAX 100

using namespace std;

int n, m, extra[NMAX], c[NMAX], sz[NMAX], nc;
vector<int> g[NMAX];

vector<pair<int, int>> edges;

int find_best(int i) {
  int u = -1;
  for (int v = 0; v < n; v++) {
    if (c[v] == i) {
      if (u == -1 || extra[u] > extra[v]) {
        u = v;
      }
    }
  }

  return u;
}

void merge(int i, int j) {
  int u = find_best(i);
  int v = find_best(j);

  extra[u]++;
  extra[v]++;
  edges.emplace_back(u, v);

  for (int w = 0; w < n; w++) {
    if (c[w] == j) {
      c[w] = i;
    }
  }

  sz[i] += sz[j];
  sz[j] = 0;
}

int main() {
  ifstream cin("conexidad.in");
  ofstream cout("conexidad.out");

  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;

    g[u].push_back(v);
    g[v].push_back(u);
  }

  for (int s = 0; s < n; s++) {
    if (c[s] == 0) {
      queue<int> q;
      q.push(s);
      c[s] = ++nc;
      sz[nc] = 1;

      while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto v : g[u]) {
          if (c[v] == 0) {
            q.push(v);
            c[v] = nc;
            sz[nc]++;
          }
        }
      }
    }
  }

  int i = 1;
  while (i <= nc && sz[i] < 2) {
    i++;
  }

  if (i > nc) {
    i = 1;
  }

  for (int j = i + 1; j <= nc; j++) {
    if (sz[j] >= 2) {
      merge(i, j);
    }
  }

  for (int j = 1; j <= nc; j++) {
    if (i != j && sz[j] == 1) {
      merge(i, j);
    }
  }

  int maxextra = extra[0];
  for (int i = 1; i < n; i++) {
    maxextra = max(maxextra, extra[i]);
  }

  cout << maxextra << "\n";
  cout << edges.size() << "\n";
  for (auto [u, v] : edges) {
    cout << u + 1 << " " << v + 1 << "\n";
  }

  return 0;
}
