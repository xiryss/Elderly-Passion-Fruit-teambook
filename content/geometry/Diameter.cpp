/**
 * Author: Igor Markelov
 * Date: 2022-11-18
 * Description: Rotating calipers.
 * Time: O(n)
 */

ld diameter(vector<Point> p) {
  p = convexHull(p);
  int n = p.size();
  if (n <= 1) {
    return 0;
  }
  if (n == 2) {
    return (p[0] - p[1]).len();
  }
  ld ans = 0;
  int i = 0, j = 1;
  while (i < n) {
    while (sign((p[(i + 1) % n] - p[i]) ^ (p[(j + 1) % n] - p[j])) >= 0) {
      chkmax(ans, (p[i] - p[j]).len());
      j = (j + 1) % n;
    }
    chkmax(ans, (p[i] - p[j]).len());
    ++i;
  }
  return ans;
}