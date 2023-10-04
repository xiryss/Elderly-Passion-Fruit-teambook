#ifdef LOCAL
    #define _GLIBCXX_DEBUG
#endif
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;
using ull = unsigned long long;

#define pbc push_back
#define mp make_pair
#define all(a) (a).begin(), (a).end()
#define vin(a) for (auto& i : a) cin >> i

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

template <typename T1, typename T2>
inline void chkmin(T1& x, const T2& y) {
    if (y < x)
        x = y;
}

template <typename T1, typename T2>
inline void chkmax(T1& x, const T2& y) {
    if (x < y)
        x = y;
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cout.precision(20), cout.setf(ios::fixed);

    return 0;
}
