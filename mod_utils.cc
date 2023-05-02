#include <bits/stdc++.h>
using namespace std;


// Computes x^pow (mod m).
int64_t ModPow(const int64_t x, int64_t pow, const int64_t m) {
  int64_t base = x, ans = 1;
  while (pow) {
    if (pow & 0x1LL) ans = (ans * base) % m;
    base = (base * base) % m;
    pow >>= 1;
  }
  return ans;
}
