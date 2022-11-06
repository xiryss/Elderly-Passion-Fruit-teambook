// НЕ ЗАБЫТЬ ВЫЗВАТЬ initFFT и проверить MAXLOG
namespace FFT {
const int MAXLOG = 20;
const ld PI = acos(-1);
using cd = complex<long double>;
const int N = (1 << MAXLOG);
const int MAXN = (1 << MAXLOG) + 228;
int rev[MAXN];
cd w[MAXN];
int n, m;
cd a[MAXN], b[MAXN];
int fans[MAXN];
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
    int LOG = 0;
    while ((1 << LOG) < 2 * max(n, m))
        LOG++;
    int sz = 1 << LOG;
    for (int i = n; i < sz; i++)
        a[i] = 0;
    for (int i = m; i < sz; ++i)
        b[i] = 0;
    FFT(sz, LOG, a);
    FFT(sz, LOG, b);
    for (int i = 0; i < sz; i++) {
        a[i] *= b[i];
    }
    FFT(sz, LOG, a);
    for (int i = 0; i < sz; i++) {
        fans[i] = (int)(a[i].real() / sz + 0.5);
    }
    reverse(fans + 1, fans + sz);
}
}  // namespace FFT
// НЕ ЗАБЫТЬ ВЫЗВАТЬ initFFT и проверить MAXLOG
