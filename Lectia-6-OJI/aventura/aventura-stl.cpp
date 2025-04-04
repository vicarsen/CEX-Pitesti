#include <bits/stdc++.h>

using namespace std;

ifstream fin("aventura.in");
ofstream fout("aventura.out");

void solve()
{
	int n;
	fin >> n;

	vector<int> deg(n);
	vector<vector<int> > g(n);
	for (int i = 0; i < n; i++) {
		fin >> deg[i];
		for (int j = 0; j < deg[i]; j++) {
			int v;
			fin >> v;

			g[v - 1].push_back(i);
		}
	}

	queue<int> q;

	for (int i = 0; i < n; i++)
		if (deg[i] == 0)
			q.push(i);

	int ans = 0;
	while (!q.empty()) {
		int u = q.front();
		q.pop();

		ans++;

		for (auto v : g[u])
			if (--deg[v] == 0)
				q.push(v);
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
