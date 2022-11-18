/**
 * Author: Igor Markelov
 * Date: 2022-11-18
 * Description: struct Point
 */

struct Point {
  ld x = 0, y = 0;
  Point() = default;
  Point(ld _x, ld _y) : x(_x), y(_y) {
  }
  Point ort() const {
    return Point(-y, x);
  }
  int half() const {
    return sign(y) == 1 || (sign(y) == 0 && sign(x) >= 0);
  }
  bool operator<(const Point& other) const {
    if (sign(y - other.y) != 0) {
      return y < other.y;
    } else if (sign(x - other.x) != 0) {
      return x < other.x;
    } else {
      return false;
    }
  }
  Point turn(ld sin, ld cos) const {
    return Point(x * cos - y * sin, x * sin + y * cos);
  }
  Point turn(ld phi) const {
    return turn(sin(phi), cos(phi));
  }
};

#define Vec Point

ld getAngle(Vec& lhs, Vec& rhs) {
  return atan2(lhs ^ rhs, lhs * rhs);
}

bool cmpHalf(const Vec& lhs, const Vec& rhs) {
  if (lhs.half() != rhs.half()) {
    return lhs.half();
  } else {
    int sgn = sign(lhs ^ rhs);
    if (!sgn) {
      return lhs.len2() < rhs.len2();
    } else {
      return sgn == 1;
    }
  }
}
