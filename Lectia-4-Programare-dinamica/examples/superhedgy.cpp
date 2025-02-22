#include <bits/stdc++.h>

using namespace std;

#define INFLL 0x3f3f3f3f3f3f3f3fll

struct event_t {
  int l, h, e;
};

int main() {
  ifstream cin("superhedgy.in");
  ofstream cout("superhedgy.out");

  int n;
  cin >> n;

  vector<event_t> top(n + 1);

  for (int i = 0; i < n; i++) {
    int l, h, e;
    cin >> top[i].l >> top[i].h >> top[i].e;
  }

  int m;
  cin >> m;

  vector<event_t> bottom(m + 1);

  for (int i = 0; i < m; i++) {
    int l, h, e;
    cin >> bottom[i].l >> bottom[i].h >> bottom[i].e;
  }

  int htop = 0, hbottom = 0;
  long long etop = INFLL, ebottom = INFLL;
  long long xtop = 0, xbottom = 0, ctop = 0, cbottom = 0;

  int i = 0, j = 0;
  while (i < n) {
    long long cmp = (xtop + top[i].l) - (xbottom + bottom[j].l);

    if (cmp <= 0) {
      ctop += abs(htop - top[i].h);
      xtop += top[i].l;
      htop = top[i].h;
      etop = top[i].e;
      i++;
    }

    if (cmp >= 0) {
      cbottom += abs(hbottom - bottom[j].h);
      xbottom += bottom[j].l;
      hbottom = bottom[j].h;
      ebottom = bottom[j].e;
      j++;
    }

    int e = etop + ebottom;
    ctop = min(ctop, cbottom + e);
    cbottom = min(cbottom, ctop + e);
  }

  cout << min(ctop + htop, cbottom + hbottom) + xtop << "\n";
  return 0;
}
