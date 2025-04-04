#include <fstream>
#include <algorithm>

#define NMAX 300000
#define MOD 1000000007

using namespace std;

ifstream fin("cromatic.in");
ofstream fout("cromatic.out");

int n, a[NMAX];

int main()
{
	int c, p;
	fin >> c;

	fin >> n;
	if (c == 3)
		fin >> p;

	for (int i = 0; i < n; i++)
		fin >> a[i];

	if (c == 1) {
		sort(a, a + n);

		for (int i = 1; i < n; i++) {
			if (a[i] == a[i - 1]) {
				fout << "0\n";
				return 0;
			}
		}

		int ans = 1;
		while (--n) {
			ans += ans;
			if (ans >= MOD)
				ans -= MOD;
		}

		fout << ans << "\n";
	} else if (c == 2) {
		int ans = 0;

		int k = 0;
		long long comb = 1;
		for (int i = 1; i < n; i++) {
			if (a[i] < a[0]) {
				ans += comb;
				k++;
				comb = comb * (n - k) / k;
			}
		}

		k--;
		comb = comb * (k + 1) / (n - k - 1);
		for (int i = 1; i < n; i++) {
			comb = comb * (n - i - k) / (n - i);
			if (a[i] < a[0]) {
				k--;
				comb = comb * (k + 1) / (n - i - k - 1);
			} else {
				ans += comb;
			}
		}

		fout << ans + 1 << "\n";
	} else {
		sort(a, a + n);
		p--;

		int k = 0;
		long long comb = 1;
		while (p >= comb) {
			p -= comb;
			k++;
			comb = comb * (n - k) / k;
		}

		fout << a[k] << " ";
		int l = k, r = k + 1;

		k--;
		comb = comb * (k + 1) / (n - k - 1);
		for (int i = 1; i < n; i++) {
			comb = comb * (n - i - k) / (n - i);
			if (r < n && p >= comb) {
				p -= comb;

				fout << a[r++] << " ";
			} else {
				fout << a[--l] << " ";

				k--;
				comb = comb * (k + 1) / (n - i - k - 1);
			}
		}

		fout << "\n";
	}

	return 0;
}
