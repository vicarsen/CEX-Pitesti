#include <bits/stdc++.h>

using namespace std;

struct alphabet_t {
  int remap[256];
  int size;

  void add(char c) {
    remap[c] = size++;
  }
};

vector<int> prefix_function(const string& s)
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

int encode(int q, int c)
{
  return q | (c << 22);
}

unordered_map<int, int> build_automaton(const string& s, const alphabet_t& alphabet)
{
  int n = s.size();
  unordered_map<int, int> aut;

  vector<int> pi = prefix_function(s);
  for (int i = 0; i <= n; i++) {
    for (int c = 0; c < alphabet.size; c++) {
      if (i < n && c == alphabet.remap[s[i]]) {
        aut.emplace(encode(i, c), i + 1);
      } else if (i != 0) {
        auto it = aut.find(encode(pi[i - 1], c));
        if (it != aut.end()) {
          aut.emplace(encode(i, c), it->second);
        }
      }
    }
  }
  return aut;
}

int main()
{
  alphabet_t alphabet;
  alphabet.size = 0;

  for (char c = '0'; c <= '9'; c++) {
    alphabet.add(c);
  }

  for (char c = 'a'; c <= 'z'; c++) {
    alphabet.add(c);
  }

  for (char c = 'A'; c <= 'Z'; c++) {
    alphabet.add(c);
  }

  ifstream cin("strmatch.in");
  ofstream cout("strmatch.out");

  string s, t;
  cin >> s >> t;

  auto aut = build_automaton(s, alphabet);

  int cnt = 0;
  vector<int> ans;
  ans.reserve(1000);

  int q = 0;
  for (int i = 0; i < t.size(); i++) {
    auto it = aut.find(encode(q, alphabet.remap[t[i]]));
    if (it != aut.end()) {
      q = it->second;
    } else {
      q = 0;
    }

    if (q == s.size()) {
      if (cnt < 1000) {
        ans.push_back(i - s.size() + 1);
      }

      cnt++;
    }
  }

  cout << cnt << "\n";
  for (int i = 0; i < ans.size(); i++) {
    cout << ans[i] << " ";
  }
  cout << "\n";

  return 0;
}

