#include <fstream>
#include <algorithm>

#define NMAX 300000
#define MOD 1000000007
#define MODLL ((1ll << 61) - 1)

using namespace std;

ifstream fin("cromatic.in");
ofstream fout("cromatic.out");

int n, a[NMAX];

long long mul(long long x, long long y, long long mod)
{
	return (__int128_t)x * y % mod;
}

long long binpow(long long b, long long p, long long mod)
{
	long long r = 1;
	while (p) {
		if (p & 1)
			r = mul(r, b, mod);
		b = mul(b, b, mod);
		p >>= 1;
	}
	return r;
}

long long inv(long long x, long long mod)
{
	return binpow(x, mod - 2, mod);
}

long long fact[NMAX], ifact[NMAX];

void precalc(long long mod)
{
	fact[0] = 1;
	for (int i = 1; i < n; i++)
		fact[i] = mul(fact[i - 1], i, mod);

	ifact[n - 1] = 1;
	for (int i = n - 2; i >= 0; i--)
		ifact[i] = mul(ifact[i + 1], i + 1, mod);

	long long ifn = inv(fact[n - 1], mod);
	for (int i = 0; i < n; i++)
		ifact[i] = mul(ifact[i], ifn, mod);
}

long long comb(int n, int k, long long mod)
{
	return mul(fact[n], mul(ifact[k], ifact[n - k], mod), mod);
}

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

		fout << binpow(2, n - 1, MOD) << "\n";
	} else if (c == 2) {
		precalc(MOD);

		int order = 0;
		long long ans = 0;
		for (int i = 1; i < n; i++) {
			if (a[i] < a[0]) {
				ans += comb(n - 1, order, MOD);
				order++;
			}
		}

		for (int i = 1; i < n; i++) {
			if (a[i] < a[0])
				order--;
			else if (order > 0)
				ans += comb(n - i - 1, order - 1, MOD);
		}

		fout << ans + 1 << "\n";
	} else {
		precalc(MODLL);

		sort(a, a + n);

		p--;
		int l = 0;
		long long cnt = 1;
		while (p >= cnt) {
			p -= cnt;
			cnt = comb(n - 1, ++l, MODLL);
		}

		int r = l + 1;
		fout << a[l] << " ";

		while (p > 0) {
			int cnt = comb(n - (r - l) - 1, l - 1, MODLL);
			if (p >= cnt) {
				p -= cnt;
				fout << a[r++] << " ";
			} else {
				fout << a[--l] << " ";
			}
		}

		while (l > 0)
			fout << a[--l] << " ";

		while (r < n)
			fout << a[r++] << " ";

		fout << "\n";
	}
	return 0;
}
