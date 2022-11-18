/**
 * Author: Igor Markelov
 * Date: 2022-11-12
 * Description: Build suffix array
 * Time: O(n \log(n))
 */
vector<int> buildSuffixArray(string& s) {
  // Remove, if you want to sort cyclic shifts
  s += "$";
  int n = s.size();
  vector<int> a(n);
  iota(all(a), 0);
  stable_sort(all(a), [&](int i, int j) { return s[i] < s[j]; });
  vector<int> c(n);
  int cc = 0;
  for (int i = 0; i < n; i++) {
    if (i == 0 || s[a[i]] != s[a[i - 1]]) {
      c[a[i]] = cc++;
    } else {
      c[a[i]] = c[a[i - 1]];
    }
  }
  for (int l = 1; l < n; l *= 2) {
    vector<int> cnt(n);
    for (auto i : c) {
      cnt[i]++;
    }
    vector<int> pref(n);
    for (int i = 1; i < n; i++) {
      pref[i] = pref[i - 1] + cnt[i - 1];
    }
    vector<int> na(n);
    for (int i = 0; i < n; i++) {
      int pos = (a[i] - l + n) % n;
      na[pref[c[pos]]++] = pos;
    }
    a = na;
    vector<int> nc(n);
    cc = 0;
    for (int i = 0; i < n; i++) {
      if (i == 0 || c[a[i]] != c[a[i - 1]] ||
          c[(a[i] + l) % n] != c[(a[i - 1] + l) % n]) {
        nc[a[i]] = cc++;
      } else {
        nc[a[i]] = nc[a[i - 1]];
      }
    }
    c = nc;
  }
  return a;
}
