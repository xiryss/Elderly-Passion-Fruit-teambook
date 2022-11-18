/**
 * Author: Igor Markelov
 * Date: 2022-11-18
 * Description: Polygon functions
 */

ld area(vector<Point>& p) {
  ld ans = 0;
  int n = p.size();
  for (int i = 0; i < n; ++i) {
    ans += p[i] ^ p[i + 1 < n ? i + 1 : 0];
  }
  return abs(ans) / 2;
}

ld perimeter(vector<Point>& p) {
  ld ans = 0;
  int n = p.size();
  for (int i = 0; i < n; ++i) {
    ans += (p[i] - p[i + 1 < n ? i + 1 : 0]).len();
  }
  return ans;
}

bool isCounterclockwise(vector<Point>& p) {
  int n = p.size();
  int pos = min_element(all(p)) - p.begin();
  return sign((p[pos + 1 < n ? pos + 1 : 0] - p[pos]) ^
              (p[pos - 1 >= 0 ? pos - 1 : n - 1] - p[pos])) == 1;
}

bool isConvex(vector<Point>& p) {
  int n = p.size();
  int sgn = 0;
  for (int i = 0; i < n; ++i) {
    int cur_sgn = sign((p[i - 1 >= 0 ? i - 1 : n - 1] - p[i]) ^
                       (p[i + 1 < n ? i + 1 : 0] - p[i]));
    if (sgn && sgn != cur_sgn) {
      return false;
    }
    sgn = cur_sgn;
  }
  return true;
}

vector<Point> convexHull(vector<Point> p) {
  if (p.empty()) {
    return {};
  }
  int n = p.size();
  int pos = min_element(all(p)) - p.begin();
  swap(p[0], p[pos]);
  for (int i = 1; i < n; ++i) p[i] = p[i] - p[0];
  sort(p.begin() + 1, p.end(), [&](Point& lhs, Point& rhs) -> bool {
    int sgn = sign(lhs ^ rhs);
    if (!sgn) {
      return lhs.len2() < rhs.len2();
    }
    return sgn == 1;
  });
  for (int i = 1; i < n; ++i) p[i] = p[i] + p[0];
  int top = 0;
  for (int i = 0; i < n; ++i) {
    while (top >= 2) {
      Vec v1 = p[top - 1] - p[top - 2];
      Vec v2 = p[i] - p[top - 1];
      if (sign(v1 ^ v2) == 1) break;
      --top;
    }
    p[top++] = p[i];
  }
  p.resize(top);
  return p;
}