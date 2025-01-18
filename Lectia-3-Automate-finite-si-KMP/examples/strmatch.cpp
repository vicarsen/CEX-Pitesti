#include <bits/stdc++.h>

using namespace std;

int main()
{
  ifstream cin("strmatch.in");
  ofstream cout("strmatch.out");

  string s, t;
  cin >> s >> t;

  int n = s.size();
  s = s + "#" + t;

  int m = s.size();
  vector<int> pi(m);
  
  pi[0] = 0;
  for (int i = 1; i < m; i++) {
    int j = pi[i - 1];
    while (j > 0 && s[j] != s[i]) {
      j = pi[j - 1];
    }

    if (s[j] == s[i]) {
      j++;
    }

    pi[i] = j;
  }

  int cnt = 0;
  vector<int> ans(1000);

  for (int i = n + 1; i < m; i++) {
    if (pi[i] == n) {
      if (cnt < 1000) {
        ans[cnt] = i - 2 * n;
      }

      cnt++;
    }
  }

  cout << cnt << "\n";
  for (int i = 0; i < min(cnt, 1000); i++) {
    cout << ans[i] << " ";
  }
  cout << "\n";

  return 0;
}

