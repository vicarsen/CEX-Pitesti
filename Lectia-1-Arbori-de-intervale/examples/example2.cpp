#include <bits/stdc++.h>

#define NMAX 100000
#define INF 0x3f3f3f3f

using namespace std;

struct node_t
{
	int sum, prefix, suffix, seq;
};

node_t combine(const node_t& lhs, const node_t& rhs)
{
	node_t ans;
	ans.sum = lhs.sum + rhs.sum;
	ans.prefix = max(lhs.prefix, lhs.sum + rhs.prefix);
	ans.suffix = max(lhs.suffix + rhs.sum, rhs.suffix);
	ans.seq = max(max(lhs.seq, rhs.seq), lhs.suffix + rhs.prefix);
	return ans;
}

int n, q, a[NMAX + 1], lazy[4 * NMAX + 1];
node_t tree[4 * NMAX + 1];

void build(int node, int l, int r)
{
	if (l == r)
	{
		tree[node] = { a[l], max(0, a[l]), max(0, a[l]), max(0, a[l]) };
		lazy[node] = INF;
		return;
	}

	int m = (l + r) / 2;
	build(2 * node, l, m);
	build(2 * node + 1, m + 1, r);
	tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
	lazy[node] = INF;
}

void apply(int node, int l, int r, int k)
{
	if (l > r)
		return;

	lazy[node] = k;
	tree[node].sum = k * (r - l + 1);
	if (k > 0)
	{
		tree[node].prefix = tree[node].sum;
		tree[node].suffix = tree[node].sum;
		tree[node].seq = tree[node].sum;
	}
	else
	{
		tree[node].prefix = 0;
		tree[node].suffix = 0;
		tree[node].seq = 0;
	}
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

	if (lazy[node] != INF)
		push(node, l, r);

	int m = (l + r) / 2;
	update(2 * node, l, m, x, min(y, m), k);
	update(2 * node + 1, m + 1, r, max(x, m + 1), y, k);
	tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
}

node_t query(int node, int l, int r, int x, int y)
{
	if (x > y)
		return { 0, 0, 0, 0 };

	if (l == x && r == y)
		return tree[node];

	if (lazy[node] != INF)
		push(node, l, r);

	int m = (l + r) / 2;
	return combine(query(2 * node, l, m, x, min(y, m)),
		   		   query(2 * node + 1, m + 1, r, max(x, m + 1), y));
}

int main()
{
	cin >> n >> q;
	for (int i = 1; i <= n; i++)
		cin >> a[i];

	build(1, 1, n);

	for (int i = 0; i < q; i++)
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

			node_t ans = query(1, 1, n, l, r);
			cout << ans.seq << '\n';
		}
	}

	return 0;
}

