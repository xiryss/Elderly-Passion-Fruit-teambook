/**
 * Author: Igor Markelov
 * Date: 2022-11-08
 * Description: Calculating FFT modulo MOD
 * Time: O(n\log(n))
 */
// DONT FORGET TO CALL initNTT() AND CHECK MAXLOG
namespace NTT {
const int MOD = 998244353;
const int MAXLOG = 20;
const int N = (1 << MAXLOG);
const int MAXN = (1 << MAXLOG) + 228;
int rev[MAXN];
int w[MAXN];
int n, m;
int a[MAXN];
int b[MAXN];
int fans[MAXN];
void initNTT() {
  int g = 2;
  for (;; g++) {
    int y = g;
    for (int i = 0; i < MAXLOG - 1; ++i) {
      y = mul(y, y);
    }
    if (y == MOD - 1) {
      break;
    }
  }
  w[0] = 1;
  for (int i = 1; i < N; ++i) {
    w[i] = mul(w[i - 1], g);
  }
  rev[0] = 0;
  for (int i = 1; i < N; ++i) {
    rev[i] = (rev[i >> 1] >> 1) ^ ((i & 1) << (MAXLOG - 1));
  }
}
void NTT(int n, int LOG, int* a) {
  for (int i = 0; i < n; ++i) {
    if (i < (rev[i] >> (MAXLOG - LOG))) {
      swap(a[i], a[(rev[i] >> (MAXLOG - LOG))]);
    }
  }
  for (int lvl = 0; lvl < LOG; lvl++) {
    int len = 1 << lvl;
    for (int st = 0; st < n; st += len << 1) {
      for (int i = 0; i < len; ++i) {
        int x = a[st + i], y = mul(a[st + len + i], w[i << (MAXLOG - 1 - lvl)]);
        a[st + i] = add(x, y);
        a[st + i + len] = sub(x, y);
      }
    }
  }
}
void mul() {
  int LOG = 0;
  while ((1 << LOG) < 2 * max(n, m))
    LOG++;
  int sz = 1 << LOG;
  for (int i = n; i < sz; ++i) {
    a[i] = 0;
  }
  for (int i = m; i < sz; ++i) {
    b[i] = 0;
  }
  NTT(sz, LOG, a);
  NTT(sz, LOG, b);
  for (int i = 0; i < sz; ++i) {
    a[i] = mul(a[i], b[i]);
  }
  NTT(sz, LOG, a);
  int inv_sz = inv(sz);
  for (int i = 0; i < sz; ++i) {
    fans[i] = mul(a[i], inv_sz);
  }
  reverse(fans + 1, fans + sz);
}
}  // namespace NTT

// DONT FORGET TO CALL initNTT() AND CHECK MAXLOG
