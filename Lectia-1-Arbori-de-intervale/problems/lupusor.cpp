#include <bits/stdc++.h>

#define NMAX 100000
#define MMAX 100000
#define AMAX (2 * NMAX + 2 * MMAX)

#define MOD 1000000007

using namespace std;

int c, n, a[NMAX + 1], b[NMAX + 1], m, amax, pow2[NMAX + 1], inv2;

int add(int x, int y)
{
	x += y;
	if (x >= MOD)
		x -= MOD;
	return x;
}

int mul(int x, int y)
{
	return (long long) x * y % MOD;
}

int binpow(int b, int p)
{
	int r = 1;
	while (p)
	{
		if (p % 2 == 1) r = mul(r, b);
		b = mul(b, b);
		p /= 2;
	}
	return r;
}

struct SegmentTreeIntersect
{
	int tree[4 * AMAX + 1];
	int lazy[4 * AMAX + 1];

	void build(int node, int l, int r)
	{
		if (l == r)
		{
			tree[node] = 0;
			return;
		}

		int m = (l + r) / 2;
		build(2 * node, l, m);
		build(2 * node + 1, m + 1, r);
		tree[node] = max(tree[2 * node], tree[2 * node + 1]);
		lazy[node] = 0;
	}

	void apply(int node, int l, int r, int k)
	{
		if (l > r)
			return;

		tree[node] += k;
		lazy[node] += k;
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
		tree[node] = max(tree[2 * node], tree[2 * node + 1]);
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
		return max(query(2 * node, l, m, x, min(y, m)),
			   	   query(2 * node + 1, m + 1, r, max(x, m + 1), y));
	}
} no_of_intersections;

struct Operation
{
	int a, b;
};

struct SegmentTreeCount 
{
	int tree[4 * AMAX + 1];
	Operation lazy[4 * AMAX + 1];

	void build(int node, int l, int r)
	{
		if (l == r)
		{
			tree[node] = 0;
			return;
		}

		int m = (l + r) / 2;
		build(2 * node, l, m);
		build(2 * node + 1, m + 1, r);
		tree[node] = add(tree[2 * node], tree[2 * node + 1]);
		lazy[node] = { 1, 0 };
	}

	void apply(int node, int l, int r, Operation op)
	{
		if (l > r)
			return;

		tree[node] = add(mul(op.a, tree[node]), mul(op.b, r - l + 1));
		lazy[node] = { mul(op.a, lazy[node].a), add(mul(op.a, lazy[node].b), op.b) };
	}

	void push(int node, int l, int r)
	{
		int m = (l + r) / 2;
		apply(2 * node, l, m, lazy[node]);
		apply(2 * node + 1, m + 1, r, lazy[node]);
		lazy[node] = { 1, 0 };
	}

	void update(int node, int l, int r, int x, int y, Operation op)
	{
		if (x > y)
			return;

		if (l == x && r == y)
		{
			apply(node, l, r, op);
			return;
		}

		if (lazy[node].a != 1 || lazy[node].b != 0)
			push(node, l, r);

		int m = (l + r) / 2;
		update(2 * node, l, m, x, min(y, m), op);
		update(2 * node + 1, m + 1, r, max(x, m + 1), y, op);
		tree[node] = add(tree[2 * node], tree[2 * node + 1]);
	}

	int query(int node, int l, int r, int x, int y)
	{
		if (x > y)
			return 0;

		if (l == x && r == y)
			return tree[node];

		if (lazy[node].a != 1 || lazy[node].b != 0)
			push(node, l, r);

		int m = (l + r) / 2;
		return add(query(2 * node, l, m, x, min(y, m)),
			   	   query(2 * node + 1, m + 1, r, max(x, m + 1), y));
	}
} no_of_ways;

void insert(int x, int y)
{
	if (c == 2)
	{
		int k = no_of_intersections.query(1, 1, amax, x, x);
		no_of_ways.update(1, 1, amax, x, y, { 2, 0 });
		no_of_ways.update(1, 1, amax, x, x, { 1, pow2[k] });
	}

	no_of_intersections.update(1, 1, amax, x, y, 1);
}

void erase(int x, int y)
{
	no_of_intersections.update(1, 1, amax, x, y, -1);

	if (c == 2)
	{
		int k = no_of_intersections.query(1, 1, amax, x, x);
		no_of_ways.update(1, 1, amax, x, x, { 1, MOD - pow2[k] });
		no_of_ways.update(1, 1, amax, x, y, { inv2, 0 });
	}
}

int query()
{
	if (c == 1)
		return n - no_of_intersections.query(1, 1, amax, 1, amax);
	else
		return no_of_ways.query(1, 1, amax, 1, amax);
}

int main()
{
	ifstream cin("lupusor.in");
	ofstream cout("lupusor.out");

	cin >> c;

	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
		cin >> b[i];

	pow2[0] = 1;
	for (int i = 1; i <= n; i++)
		pow2[i] = add(pow2[i - 1], pow2[i - 1]);

	inv2 = binpow(2, MOD - 2);

	cin >> m;
	amax = 2 * n + 2 * m;

	no_of_intersections.build(1, 1, amax);
	if (c == 2)
		no_of_ways.build(1, 1, amax);

	for (int i = 1; i <= n; i++)
		if (a[i] <= b[i])
			insert(a[i], b[i]);

	cout << query() << '\n';

	for (int i = 1; i <= m; i++)
	{
		int id, c, d;
		cin >> id >> c >> d;

		if (a[id] <= b[id])
			erase(a[id], b[id]);

		a[id] = c;
		b[id] = d;

		if (a[id] <= b[id])
			insert(a[id], b[id]);

		cout << query() << '\n';
	}
	
	return 0;
}

