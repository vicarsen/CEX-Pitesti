#include <fstream>

#define INF 0x3f3f3f3f

#define NMAX 100000
#define XMAX 500000

using namespace std;

struct edge {
  int v;
  int next;
};

int beg[XMAX], d[XMAX], queue[XMAX];

int top;
edge edges[6 * NMAX + 1];

void add_edge(int u, int v) {
  edges[++top] = {v, beg[u]};
  beg[u] = top;
}

int x[NMAX], y[NMAX], z[NMAX];

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

      add_edge(x[i], y[i]);
      add_edge(x[i], z[i]);

      add_edge(y[i], x[i]);
      add_edge(y[i], z[i]);

      add_edge(z[i], x[i]);
      add_edge(z[i], y[i]);

      d[x[i]] = INF;
      d[y[i]] = INF;
      d[z[i]] = INF;
    }

    int qfront = 0, qtop = 0;
    queue[qtop++] = x[a];
    queue[qtop++] = y[a];
    queue[qtop++] = z[a];

    d[x[a]] = 0;
    d[y[a]] = 0;
    d[z[a]] = 0;

    while (qfront < qtop) {
      int u = queue[qfront++];
      for (int i = beg[u]; i != 0; i = edges[i].next) {
        int v = edges[i].v;
        if (d[v] == INF) {
          queue[qtop++] = v;
          d[v] = d[u] + 1;
        }
      }
    }

    int ans = d[x[b]];
    ans = min(ans, d[y[b]]);
    ans = min(ans, d[z[b]]);

    cout << (ans != INF ? ans + 1 : -1) << "\n";

    for (int i = 0; i < n; i++) {
      beg[x[i]] = 0;
      beg[y[i]] = 0;
      beg[z[i]] = 0;
    }

    top = 0;
  }

  return 0;
}
