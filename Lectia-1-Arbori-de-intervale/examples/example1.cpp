#include <bits/stdc++.h>

#define NMAX 100000

using namespace std;

int n, q, a[NMAX + 1], tree[4 * NMAX + 1], lazy[4 * NMAX + 1];

void build(int node, int l, int r)
{
	if (l == r)
	{
		tree[node] = a[l];
		lazy[node] = 0;
		return;
	}

	int m = (l + r) / 2;
	build(2 * node, l, m);
	build(2 * node + 1, m + 1, r);
	tree[node] = tree[2 * node] + tree[2 * node + 1];
	lazy[node] = 0;
}

void apply(int node, int l, int r, int k)
{
	if (l > r)
		return;

	lazy[node] += k;
	tree[node] += k * (r - l + 1);
}

void push(int node, int l, int r)
{
	int m = (l + r) / 2;
	apply(2 * node, l, m, lazy[node]);
	apply(2 * node + 1, m + 1, r, lazy[node]);
	lazy[node] = 0;
}

void update(int node, int l, int r, int x, int y, int k)
{
	if (x > y)
		return;

	if (l == x && r == y)
	{
		apply(node, l, r, k);
		return;
	}

	if (lazy[node] != 0)
		push(node, l, r);

	int m = (l + r) / 2;
	update(2 * node, l, m, x, min(y, m), k);
	update(2 * node + 1, m + 1, r, max(x, m + 1), y, k);
	tree[node] = tree[2 * node] + tree[2 * node + 1];
}

int query(int node, int l, int r, int x, int y)
{
	if (x > y)
		return 0;

	if (l == x && r == y)
		return tree[node];

	if (lazy[node] != 0)
		push(node, l, r);

	int m = (l + r) / 2;
	return query(2 * node, l, m, x, min(y, m)) +
		   query(2 * node + 1, m + 1, r, max(x, m + 1), y);
}

int main()
{
	cin >> n >> q;
	for (int i = 1; i <= n; i++)
		cin >> a[i];

	build(1, 1, n);

	for (int i = 1; i <= q; i++)
	{
		int type;
		cin >> type;

		if (type == 1)
		{
			int l, r, k;
			cin >> l >> r >> k;

			update(1, 1, n, l, r, k);
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

