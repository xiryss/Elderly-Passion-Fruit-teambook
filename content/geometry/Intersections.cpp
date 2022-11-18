/**
 * Author: Igor Markelov
 * Date: 2022-11-18
 * Description: Geometry intersections
 */

bool isCrossed(ld lx, ld rx, ld ly, ld ry) {
  if (lx > rx) swap(lx, rx);
  if (ly > ry) swap(ly, ry);
  return sign(min(rx, ry) - max(lx, ly)) >= 0;
}

// if two segments [a, b] and [c, d] has AT LEAST one common point -> true
bool isCrossed(Point& a, Point& b, Point& c, Point& d) {
  if (!isCrossed(a.x, b.x, c.x, d.x)) return false;
  if (!isCrossed(a.y, b.y, c.y, d.y)) return false;
  Vec v1, v2, v3;
  v1 = b - a;
  v2 = c - a;
  v3 = d - a;
  if (sign(v1 ^ v2) * sign(v1 ^ v3) == 1) return false;
  v1 = d - c;
  v2 = a - c;
  v3 = b - c;
  if (sign(v1 ^ v2) * sign(v1 ^ v3) == 1) return false;
  return true;
}

bool cross(Line& l, Line& m, Point& I) {
  ld d = l.b * m.a - m.b * l.a;
  if (sign(d) == 0) {
    return false;
  }
  ld dx = m.b * l.c - m.c * l.b;
  ld dy = m.c * l.a - l.c * m.a;
  I = Point(dx / d, dy / d);
  return true;
}

int cross(Point o1, ld r1, Point o2, ld r2, Point& I1, Point& I2) {
  if (r1 < r2) {
    swap(o1, o2);
    swap(r1, r2);
  }
  if (sign(r1 - r2) == 0 && o1 == o2) {
    return 3;
  }
  ld len = (o1 - o2).len();
  if (sign(len - r1 - r2) == 1 || sign(r1 - len - r2) == 1) {
    return 0;
  }
  ld d = (sq(r1) - sq(r2) + sq(len)) / 2 / len;
  Vec v = (o2 - o1).norm();
  Point a = o1 + v * d;
  if (sign(len - r1 - r2) == 0 || sign(len + r2 - r1) == 0) {
    I1 = a;
    return 1;
  }
  v = v.ort() * sqrt(sq(r1) - sq(d));
  I1 = a + v;
  I2 = a - v;
  return 2;
}

int cross(Point& o, ld r, Line& l, Point& I1, Point& I2) {
  ld len = dist(l, o);
  int sgn = sign(len - r);
  if (sgn == 1) {
    return 0;
  }
  Vec v = Vec(l.a, l.b).norm() * len;
  if (sign(l.eval(o + v)) != 0) {
    v = Point() - v;
  }
  Point a = o + v;
  if (sgn == 0) {
    I1 = a;
    return 1;
  }
  v = Vec(-l.b, l.a).norm() * sqrt(sq(r) - sq(len));
  I1 = a + v;
  I2 = a - v;
  return 2;
}