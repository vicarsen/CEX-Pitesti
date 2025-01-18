#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> build_automaton(string s)
{
  int n = s.size();

  vector<vector<int>> aut(n + 1, vector<int>(26));
  for (int i = 0; i <= n; i++) {
    for (int c = 0; c <= 'z' - 'a'; c++) {
      if (i < n && c + 'a' == s[i]) {
        aut[i][c] = i + 1;
      } else {
        aut[i][c] = 0;
        
        for (int j = i; j >= 0; j--) {
          int len = i - j + 1;
          bool ok = (s[len - 1] == c + 'a');
          for (int k = 0; k < len - 1; k++) {
            if (s[k] != s[j + k]) {
              ok = false;
            }
          }

          if (ok) {
            aut[i][c] = len;
          }
        }
      }
    }
  }

  return aut;
}

int main()
{
  string s, t;
  cin >> s >> t;

  vector<vector<int>> aut = build_automaton(s);

  int q = 0;
  for (int i = 0; i < t.size(); i++) {
    q = aut[q][t[i] - 'a'];
    if (q == s.size()) {
      cout << i << " ";
    }
  }
  cout << "\n";

  return 0;
}

