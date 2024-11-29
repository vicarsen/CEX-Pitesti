#include <bits/stdc++.h>

#define NMAX 100000

using namespace std;

int n, m, a[NMAX + 1], tree[4 * NMAX + 1];

void build(int node, int l, int r)
{
	if (l == r)
	{
		tree[node] = a[l];
		return;
	}

	int m = (l + r) / 2;
	build(2 * node, l, m);
	build(2 * node + 1, m + 1, r);
	tree[node] = tree[2 * node] + tree[2 * node + 1];
}

void update(int node, int l, int r, int i, int x)
{
	if (l == r)
	{
		tree[node] += x;
		return;
	}

	int m = (l + r) / 2;
	if (i <= m)
		update(2 * node, l, m, i, x);
	else
		update(2 * node + 1, m + 1, r, i, x);

	tree[node] = tree[2 * node] + tree[2 * node + 1];
}

int query(int node, int l, int r, int x, int y)
{
	if (x > y)
		return 0;

	if (l == x && r == y)
		return tree[node];

	int m = (l + r) / 2;
	return query(2 * node, l, m, x, min(y, m)) +
		   query(2 * node + 1, m + 1, r, max(x, m + 1), y);
}

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];

	build(1, 1, n);

	int m;
	cin >> m;
	for (int i = 1; i <= m; i++)
	{
		int type;
		cin >> type;

		if (type == 1)
		{
			int idx, x;
			cin >> idx >> x;

			update(1, 1, n, idx, x);
		}
		else
		{
			int l, r;
			cin >> l >> r;

			cout << query(1, 1, n, l, r) << '\n';
		}
	}

	return 0;
}

