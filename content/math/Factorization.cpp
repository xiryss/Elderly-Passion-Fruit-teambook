/**
 * Author: Iurii Pustovalov
 * Date: 2022-11-08
 * Description: Factorizing a number real quick
 * Time: O(n^{\frac{1}{4}})
 */
ll gcd(ll a, ll b) {
  while (b) a %= b, swap(a, b);
  return a;
}

ll f(ll a, ll n) {
  return ((__int128_t)a * a % n + 1) % n;
}

vector<ll> factorize(ll n) {
  if (n <= 1e6) {  // can add primality check for speed?
    vector<ll> res;
    for (ll i = 2; i * i <= n; ++i) {
      while (n % i == 0) {
        res.pbc(i);
        n /= i;
      }
    }
    if (n != 1) res.pbc(n);
    return res;
  }
  ll x = rnd() % (n - 1) + 1;
  ll y = x;
  ll tries = 10 * sqrt(sqrt(n));
  const int C = 60;
  for (ll i = 0; i < tries; i += C) {
    ll xs = x;
    ll ys = y;
    ll m = 1;
    for (int k = 0; k < C; ++k) {
      x = f(x, n);
      y = f(f(y, n), n);
      m = (__int128_t)m * abs(x - y) % n;
    }
    if (gcd(n, m) == 1) continue;
    x = xs, y = ys;
    for (int k = 0; k < C; ++k) {
      x = f(x, n);
      y = f(f(y, n), n);
      ll res = gcd(n, abs(x - y));
      if (res != 1 && res != n) {
        vector<ll> v1 = factorize(res), v2 = factorize(n / res);
        for (auto j : v2) v1.pbc(j);
        return v1;
      }
    }
  }
  return {n};
}
