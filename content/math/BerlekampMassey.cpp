/**
 * Author: Igor Markelov (stole from Red Panda teambook)
 * Date: 2022-11-18
 * Description: Find the shortest linear-feedback shift register
 * Time: O(n^2)
 */
vector<int> berlekamp_massey(vector<int> x) {
  vector<int> ls, cur;
  int lf = 0, d = 0;
  for (int i = 0; i < x.size(); ++i) {
    ll t = 0;
    for (int j = 0; j < cur.size(); ++j) {
      t = (t + 1ll * x[i - j - 1] * cur[j]) % MOD;
    }
    if ((t - x[i]) % MOD == 0) continue;
    if (cur.empty()) {
      cur.resize(i + 1);
      lf = i;
      d = (t - x[i]) % MOD;
      continue;
    }
    ll k = -(x[i] - t) * pw(d, MOD - 2) % MOD;
    vector<int> c(i - lf - 1);
    c.push_back(k);
    for (auto &j : ls) c.push_back(-j * k % MOD);
    if (c.size() < cur.size()) c.resize(cur.size());
    for (int j = 0; j < cur.size(); ++j) {
      c[j] = (c[j] + cur[j]) % MOD;
    }
    if (i - lf + (int)ls.size() >= (int)cur.size()) {
      tie(ls, lf, d) = make_tuple(cur, i, (t - x[i]) % MOD);
    }
    cur = c;
  }
  for (auto &i : cur) i = (i % MOD + MOD) % MOD;
  return cur;
}
// for a_i = 2 * a_i-1 + a_i-1 returns {2, 1}