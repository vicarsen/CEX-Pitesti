#include <bits/stdc++.h>

#define NMAX 31200
#define MMAX 31200

using namespace std;

int value_of(char c) {
  if (c == 'E') {
    return 0;
  }

  return c - 'A' + 1;
}

struct edge {
  int value;
  short u, v;
  char e;
};

int n, m;
edge e[MMAX];

short parent[NMAX], sz[NMAX];

void dsu_init() {
  for (int i = 0; i < n; i++) {
    parent[i] = i;
    sz[i] = 1;
  }
}

int get_root(int u) {
  if (parent[u] == u) {
    return u;
  }

  return parent[u] = get_root(parent[u]);
}

bool merge(int u, int v) {
  u = get_root(u);
  v = get_root(v);

  if (u == v) {
    return false;
  }

  if (sz[u] < sz[v]) {
    swap(u, v);
  }

  parent[v] = u;
  sz[u] += sz[v];
  return true;
}

int main() {
  ifstream cin("ninjago.in");
  ofstream cout("ninjago.out");

  int v;
  cin >> v;

  cin >> n >> m;

  char s[8];
  for (int i = 0; i < m; i++) {
    cin >> e[i].u >> e[i].v >> s;
    e[i].u--;
    e[i].v--;

    e[i].e = 0;
    for (int j = 0; j < 4; j++) {
      e[i].e += (s[j] == 'E');
    }

    e[i].value = 0;
    for (int j = 0, mul = 1; j < 4; j++, mul *= 5) {
      if (s[j] != 'E') {
        e[i].value += mul * (s[j] - 'A' + 1);
      }
    }
  }

  sort(e, e + m, [](const edge &e1, const edge &e2) {
    return e1.e < e2.e || (e1.e == e2.e && e1.value < e2.value);
  });

  dsu_init();

  int total = 0, i = 0;
  while (i < m && e[i].e == 0) {
    if (merge(e[i].u, e[i].v)) {
      total += e[i].value;
    }

    i++;
  }

  if (v == 1) {
    cout << sz[get_root(0)] << "\n";
    return 0;
  }

  int cnt = 0, cnte = 0;
  while (i < m) {
    if (merge(e[i].u, e[i].v)) {
      total += e[i].value;
      cnt++;
      cnte += e[i].e;
    }

    i++;
  }

  if (v == 2) {
    cout << cnt << "\n" << cnte << "\n";
  } else {
    cout << total << "\n";
  }

  return 0;
}
