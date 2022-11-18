/**
 * Author: Igor Markelov
 * Date: 2022-11-18
 * Description: struct Line
 */

struct Line {
  ld a = 0, b = 0, c = 0;
  Line() = default;
  void norm() {
    // for half planes
    ld d = Vec(a, b).len();
    assert(sign(d) > 0);
    a /= d;
    b /= d;
    c /= d;
  }
  Line(ld _a, ld _b, ld _c) : a(_a), b(_b), c(_c) {
    norm();
  }
  Line(Point x, Point y)
      : a(y.y - x.y), b(x.x - y.x), c(x.y * y.x - x.x * y.y) {
    norm();
  }
  ld eval(Point p) const {
    return a * p.x + b * p.y + c;
  }
  bool isIn(Point p) const {
    return sign(eval(p)) <= 0;
  }
  bool operator==(const Line& other) const {
    return sign(a * other.b - b * other.a) == 0 &&
           sign(a * other.c - c * other.a) == 0 &&
           sign(b * other.c - c * other.b) == 0;
  }
};