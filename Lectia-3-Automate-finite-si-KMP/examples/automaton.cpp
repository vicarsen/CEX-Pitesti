#include <bits/stdc++.h>

using namespace std;

vector<int> prefix_function(string s)
{
  int n = s.size();
  vector<int> pi(n);

  pi[0] = 0;
  for (int i = 1; i < n; i++) {
    int j = pi[i - 1];
    while (j > 0 && s[j] != s[i]) {
      j = pi[j - 1];
    }

    if (s[j] == s[i]) {
      j++;
    }

    pi[i] = j;
  }

  return pi;
}

vector<vector<int>> build_automaton(string s)
{
  int n = s.size();
  vector<vector<int>> aut(n + 1, vector<int>(26));

  vector<int> pi = prefix_function(s);
  for (int i = 0; i <= n; i++) {
    for (int c = 0; c <= 'z' - 'a'; c++) {
      if (i < n && c + 'a' == s[i]) {
        aut[i][c] = i + 1;
      } else if (i != 0) {
        aut[i][c] = aut[pi[i - 1]][c];
      }
    }
  }
  return aut;
}

int main()
{
  string s, t;
  cin >> s >> t;

  cout << (int)'0' << ' ' << (int)'a' << (int)'A' << '\n';

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

