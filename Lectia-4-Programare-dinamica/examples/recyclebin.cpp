#include <bits/stdc++.h>

using namespace std;

int main() {
  ifstream cin("recyclebin.in");
  ofstream cout("recyclebin.out");

  int n;
  cin >> n;

  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }

  int ans = 0;
  vector<vector<array<int, 2>>> dp(n + 1, vector<array<int, 2>>(n + 1));

  dp[0][0] = {0, 0};
  for (int i = 1; i <= n; i++) {
    for (int mask = 0; mask <= i; mask++) {
      if (mask != i) {
        dp[i][mask][0] = max(0, a[i] + dp[i - 1][mask][0]);
        dp[i][mask][1] = max(dp[i - 1][mask][1], dp[i][mask][0]);
      }

      for (int bit = 1; bit <= mask; bit <<= 1) {
        if (mask & bit) {
          int other = mask ^ bit;

          if (dp[i - bit][other][0] > dp[i][mask][0] ||
              (dp[i - bit][other][0] == dp[i][mask][0] &&
               dp[i - bit][other][1] > dp[i][mask][1])) {
            dp[i][mask] = dp[i - bit][other];
          }
        }
      }

      ans = max(ans, dp[i][mask][1]);
    }
  }

  cout << ans << "\n";
  return 0;
}
