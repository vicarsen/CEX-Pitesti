#include <bits/stdc++.h>

#define INF INT32_MAX

using namespace std;

int main() {
  ifstream cin("antivirus.in");
  ofstream cout("antivirus.out");

  int t;
  cin >> t;
  while (t--) {
    int n, k;
    cin >> n >> k;

    vector<int> a(n + 1);

    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }

    vector<vector<int>> d(n + 1, vector<int>(k + 1, INF));

    d[0][0] = 0;

    int last = 0, sum_to_last = 0;
    for (int i = 1; i <= n; i++) {
      if (a[i] == 0) {
        int sum = 0;
        for (int l = i; l > last; l--) {
          sum += a[l];

          int cnt = i - l + 1;
          for (int j = cnt; j <= k; j++) {
            d[i][j] = (int)min((long long)d[i][j],
                               (long long)d[l - 1][j - cnt] + sum);
          }
        }

        last = i;
        sum_to_last = 0;
      } else if (last != 0) {
        sum_to_last += a[i];

        for (int j = 0; j <= k; j++) {
          d[i][j] = d[i - 1][j];
        }

        int cnt = i - last;
        for (int j = cnt; j <= k; j++) {
          d[i][j] = (int)min((long long)d[i][j],
                             (long long)d[last][j - cnt] + sum_to_last);
        }
      } else {
        d[i][0] = 0;
      }
    }

    cout << d[n][k] << "\n";
  }

  return 0;
}
