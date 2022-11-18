/**
 * Author: Igor Markelov
 * Date: 2022-11-08
 * Description: Calculating product of two polynomials
 * Time: O(n\log(n))
 */
// DONT FORGET TO INITFFT() AND CHECK MAXLOG
const ld PI = acos(-1);
using cd = complex<long double>;
const int MAXLOG = 20, N = (1 << MAXLOG), MAXN = (1 << MAXLOG) + 228;
int rev[MAXN], n, m, fans[MAXN];
cd w[MAXN], a[MAXN], b[MAXN];
void initFFT() {
  for (int i = 0; i < N; i++) {
    w[i] = cd(cos(2 * PI * i / N), sin(2 * PI * i / N));
  }
  rev[0] = 0;
  for (int i = 1; i < N; i++) {
    rev[i] = (rev[i >> 1] >> 1) ^ ((i & 1) << (MAXLOG - 1));
  }
}
void FFT(int n, int LOG, cd* a) {
  for (int i = 0; i < n; i++) {
    if (i < (rev[i] >> (MAXLOG - LOG))) {
      swap(a[i], a[(rev[i] >> (MAXLOG - LOG))]);
    }
  }
  for (int lvl = 0; lvl < LOG; lvl++) {
    int len = 1 << lvl;
    for (int st = 0; st < n; st += len << 1) {
      for (int i = 0; i < len; i++) {
        cd x = a[st + i], y = a[st + len + i] * w[i << (MAXLOG - 1 - lvl)];
        a[st + i] = x + y;
        a[st + i + len] = x - y;
      }
    }
  }
}
void mul() {
  int LOG = __lg(2 * max(n, m) - 1) + 1;
  int sz = 1 << LOG;
  fill(a + n, a + sz, 0);
  fill(b + m, b + sz, 0);
  FFT(sz, LOG, a), FFT(sz, LOG, b);
  for (int i = 0; i < sz; i++) a[i] *= b[i];
  FFT(sz, LOG, a);
  for (int i = 0; i < sz; i++) fans[i] = (int)(a[i].real() / sz + 0.5);
  reverse(fans + 1, fans + sz);
}
// DONT FORGET TO INITFFT() AND CHECK MAXLOG
