#include <fstream>

using namespace std;

ifstream fin("experimente.in");
ofstream fout("experimente.out");

struct node_t {
	node_t *l = NULL;
	node_t *r = NULL;
	int cnt = 0;
};

int n, l, r;
node_t root;

void add(node_t *node, int x, int y)
{
	if (l <= x && y <= r)
		node->cnt = y - x;

	if (node->cnt == y - x)
		return;

	int m = (x + y) / 2;

	if (l < m) {
		if (node->l == NULL)
			node->l = new node_t;

		node->cnt -= node->l->cnt;
		add(node->l, x, m);
		node->cnt += node->l->cnt;
	}

	if (m < r) {
		if (node->r == NULL)
			node->r = new node_t;

		node->cnt -= node->r->cnt;
		add(node->r, m, y);
		node->cnt += node->r->cnt;
	}
}

void add(int l, int r)
{
	if (l >= r)
		return;

	::l = l;
	::r = r;
	add(&root, 0, n);
}

int main()
{
	int m, r = 0;
	fin >> n >> m;

	for (int i = 0; i < m; i++) {
		int a, b;
		fin >> a >> b;

		a += r;
		if (a >= n)
			a -= n;

		b += r;
		if (b >= n)
			b -= n;
		b++;

		if (a < b) {
			add(0, a);
			add(b, n);
		} else {
			add(b, a);
		}

		r = n - root.cnt;
		fout << r << "\n";
	}
}
