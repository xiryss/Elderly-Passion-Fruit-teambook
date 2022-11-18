/**
 * Author: Igor Markelov
 * Date: 2022-11-18
 * Description: Is in polygon functions
 */

bool isOnSegment(Point& a, Point& b, Point& x) {
  if (a == b) {
    return a == x;
  }
  return sign((b - a) ^ (x - a)) == 0 && sign((b - a) * (x - a)) >= 0 &&
         sign((a - b) * (x - b)) >= 0;
  // optional (slower, but works better if there are some precision
  // problems) return sign((b - a).len() - (x - a).len() - (x - b).len())
  // == 0;
}

bool isIn(vector<Point>& p, Point& a) {
  int n = p.size();
  // depents on limitations
  Point b = a + Point(1e9, 1);
  int cnt = 0;
  for (int i = 0; i < n; ++i) {
    Point x = p[i];
    Point y = p[i + 1 < n ? i + 1 : 0];
    if (isOnSegment(x, y, a)) {
      // depends on the problem statement
      return true;
    }
    cnt += isCrossed(x, y, a, b);
  }
  return cnt % 2 == 1;
  /*optional (atan2 is VERY SLOW)!
  ld ans = 0;
  int n = p.size();
  for (int i = 0; i < n; ++i) {
    Point x = p[i];
    Point y = p[i + 1 < n ? i + 1 : 0];
    if (isOnSegment(x, y, a)) {
      // depends on the problem statement
      return true;
    }
    x = x - a;
    y = y - a;
    ans += atan2(x ^ y, x * y);
  }
  return abs(ans) > 1;*/
}

bool isInTriangle(Point& a, Point& b, Point& c, Point& x) {
  return sign((b - a) ^ (x - a)) >= 0 && sign((c - b) ^ (x - b)) >= 0 &&
         sign((a - c) ^ (x - c)) >= 0;
}

// points should be in the counterclockwise order
bool isInConvex(vector<Point>& p, Point& a) {
  int n = p.size();
  assert(n >= 3);
  // assert(isConvex(p));
  // assert(isCounterclockwise(p));
  if (sign((p[1] - p[0]) ^ (a - p[0])) < 0) return false;
  if (sign((p[n - 1] - p[0]) ^ (a - p[0])) > 0) return false;
  int pos = lower_bound(p.begin() + 2, p.end(), a,
                        [&](Point lhs, Point rhs) -> bool {
                          return sign((lhs - p[0]) ^ (rhs - p[0])) > 0;
                        }) -
            p.begin();
  assert(pos > 1 && pos < n);
  return isInTriangle(p[0], p[pos - 1], p[pos], a);
}