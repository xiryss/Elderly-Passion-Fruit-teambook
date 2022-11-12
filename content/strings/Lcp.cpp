/**
 * Author: Igor Markelov
 * Date: 2022-11-12
 * Description: lcp array
 * Time: O(n)
 */

vector<int> buildLCP(string& s, vector<int>& a) {
  int n = s.size();
  vector<int> ra(n);
  for (int i = 0; i < n; i++) {
    ra[a[i]] = i;
  }
  vector<int> lcp(n - 1);
  int cur = 0;
  for (int i = 0; i < n; i++) {
    cur--;
    chkmax(cur, 0);
    if (ra[i] == n - 1) {
      cur = 0;
      continue;
    }
    int j = a[ra[i] + 1];
    while (s[i + cur] == s[j + cur])
      cur++;
    lcp[ra[i]] = cur;
  }
  // for suffixes!!!
  s.pop_back();
  a.erase(a.begin());
  lcp.erase(lcp.begin());
  return lcp;
}
