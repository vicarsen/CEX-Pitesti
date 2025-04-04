#include <fstream>

#define NMAX 500000
#define MMAX 2000000

using namespace std;

ifstream fin("aventura.in");
ofstream fout("aventura.out");

struct edge_t {
	int v;
	int next;
};

int n, deg[NMAX], queue[NMAX];
int beg[NMAX], top;
edge_t edges[MMAX];

void add_edge(int u, int v)
{
	edges[++top] = { v, beg[u] };
	beg[u] = top;
}

void solve()
{
	fin >> n;

	top = 0;
	for (int i = 0; i < n; i++)
		beg[i] = 0;

	for (int i = 0; i < n; i++) {
		fin >> deg[i];
		for (int j = 0; j < deg[i]; j++) {
			int v;
			fin >> v;

			add_edge(v - 1, i);
		}
	}

	int qfront = 0, qtop = 0;
	for (int i = 0; i < n; i++)
		if (deg[i] == 0)
			queue[qtop++] = i;

	int ans = 0;
	while (qfront < qtop) {
		int u = queue[qfront++];

		ans++;

		for (int i = beg[u]; i != 0; i = edges[i].next) {
			int v = edges[i].v;
			if (--deg[v] == 0)
				queue[qtop++] = v;
		}
	}

	fout << ans << "\n";
}

int main()
{
	int t;
	fin >> t;
	while (t--)
		solve();

	return 0;
}
