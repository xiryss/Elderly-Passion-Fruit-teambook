/**
 * Author: Igor Markelov
 * Date: 2022-11-18
 * Description: Tangents to circles.
 */

int tangents(Point& o, ld r, Point& p, Point& I1, Point& I2) {
  ld len = (o - p).len();
  int sgn = sign(len - r);
  if (sgn == -1) {
    return 0;
  } else if (sgn == 0) {
    I1 = p;
    return 1;
  } else {
    ld x = sq(r) / len;
    Vec v = (p - o).norm() * x;
    Point a = o + v;
    v = (p - o).norm().ort() * sqrt(sq(r) - sq(x));
    I1 = a + v;
    I2 = a - v;
    return 2;
  }
}

void tangents(Point c, ld r1, ld r2, vector<Line>& ans) {
  ld r = r2 - r1;
  ld z = sq(c.x) + sq(c.y);
  ld d = z - sq(r);
  if (sign(d) == -1) return;
  d = sqrt(abs(d));
  Line l;
  l.a = (c.x * r + c.y * d) / z;
  l.b = (c.y * r - c.x * d) / z;
  l.c = r1;
  ans.push_back(l);
}

vector<Line> tangents(Point o1, ld r1, Point o2, ld r2) {
  vector<Line> ans;
  for (int i = -1; i <= 1; i += 2)
    for (int j = -1; j <= 1; j += 2)
      tangents(o2 - o1, r1 * i, r2 * j, ans);
  for (int i = 0; i < (int)ans.size(); ++i)
    ans[i].c -= ans[i].a * o1.x + ans[i].b * o1.y;
  return ans;
}