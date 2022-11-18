/**
 * Author: Igor Markelov
 * Date: 2022-11-18
 * Description: Find both tangets to the convex polygon. \\
 * (Zakaldovany algos mozhet sgonyat za pivom tak zhe).
 * Time: O(\log(n))
 */

pair<int, int> tangents_alex(vector<Point>& p, Point& a) {
  int n = p.size();
  int l = __lg(n);
  auto findWithSign = [&](int val) {
    int i = 0;
    for (int k = l; k >= 0; --k) {
      int i1 = (i - (1 << k) + n) % n;
      int i2 = (i + (1 << k)) % n;
      if (sign((p[i1] - a) ^ (p[i] - a)) == val) i = i1;
      if (sign((p[i2] - a) ^ (p[i] - a)) == val) i = i2;
    }
    return i;
  };
  return {findWithSign(1), findWithSign(-1)};
}