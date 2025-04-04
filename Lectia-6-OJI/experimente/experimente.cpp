#include <fstream>
#include <set>

using namespace std;

ifstream fin("experimente.in");
ofstream fout("experimente.out");

int total;
set<pair<int, int> > s;

void add(int l, int r)
{
	if (l >= r)
		return;

	auto it = s.lower_bound(make_pair(l, 0));
	if (it != s.begin()) {
		auto pr = prev(it);
		if (l <= pr->second) {
			l = pr->first;
			r = max(r, pr->second);
			total -= pr->second - pr->first;
			it = s.erase(pr);
		}
	}

	while (it != s.end() && it->first <= r) {
		r = max(r, it->second);
		total -= it->second - it->first;
		it = s.erase(it);
	}

	total += r - l;
	s.emplace(l, r);
}

int main()
{
	int n, m, r = 0;
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

		r = n - total;
		fout << r << "\n";
	}
}
