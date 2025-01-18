#include <stdio.h>

#define LMAX 2'000'005

int n, cnt;
char s[LMAX], t[LMAX];
int pi[LMAX], ans[1000];

int min(int x, int y)
{
  return x <= y ? x : y;
}

int main()
{
  freopen("strmatch.in", "r", stdin);
  freopen("strmatch.out", "w", stdout);

  fgets(s, LMAX, stdin);
  fgets(t, LMAX, stdin);

  pi[0] = 0;
  for (n = 1; s[n] != '\n'; n++) {
    int j = pi[n - 1];
    while (j > 0 && s[j] != s[n]) {
      j = pi[j - 1];
    }

    if (s[j] == s[n]) {
      j++;
    }

    pi[n] = j;
  }

  int j = 0;
  for (int i = 0; t[i] != '\n'; i++) {
    while (j > 0 && s[j] != t[i]) {
      j = pi[j - 1];
    }

    if (s[j] == t[i]) {
      j++;
    }

    if (j == n) {
      if (cnt < 1000) {
        ans[cnt] = i - n + 1;
      }

      cnt++;
    }
  }

  printf("%d\n", cnt);
  for (int i = 0; i < min(cnt, 1000); i++) {
    printf("%d ", ans[i]);
  }
  printf("\n");

  fclose(stdin);
  fclose(stdout);
  return 0;
}

