#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = double;
using ull = unsigned long long;

#define pbc push_back
#define mp make_pair
#define all(a) (a).begin(), (a).end()
#define vin(a) \
  for (auto& i : a) cin >> i

// mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
mt19937 rnd(228);

template <typename T1, typename T2>
inline void chkmin(T1& x, const T2& y) {
  if (y < x) {
    x = y;
  }
}

template <typename T1, typename T2>
inline void chkmax(T1& x, const T2& y) {
  if (x < y) {
    x = y;
  }
}

ld EPS = 1e-9;
ld PI = acos(-1);

int sign(ld x) {
  if (x > EPS) {
    return 1;
  } else if (x < -EPS) {
    return -1;
  } else {
    return 0;
  }
}

ld sq(ld x) {
  return x * x;
}

struct Point {
  ld x = 0, y = 0;
  Point() = default;
  Point(ld _x, ld _y) : x(_x), y(_y) {
  }
  Point operator-(const Point& other) const {
    return Point(x - other.x, y - other.y);
  }
  Point operator+(const Point& other) const {
    return Point(x + other.x, y + other.y);
  }
  Point operator*(const ld& a) const {
    return Point(x * a, y * a);
  }
  Point operator/(const ld& a) const {
    assert(sign(a) != 0);
    return Point(x / a, y / a);
  }
  ld operator^(const Point& other) const {
    return x * other.y - y * other.x;
  }
  ld operator*(const Point& other) const {
    return x * other.x + y * other.y;
  }
  Point ort() const {
    return Point(-y, x);
  }
  ld len2() const {
    return sq(x) + sq(y);
  }
  ld len() const {
    return sqrt(len2());
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
  bool operator==(Point& other) const {
    return sign(x - other.x) == 0 && sign(y - other.y) == 0;
  }
  Point norm() const {
    ld d = len();
    // maybe change to if (d == 0) return Point();
    assert(sign(d) == 1);
    return Point(x / d, y / d);
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

ld dist(Line& l, Point& p) {
  return abs(l.eval(p) / Vec(l.a, l.b).len());
}

/*

x * l.a + y * l.b + l.c = 0
x * m.a + y * m.b + m.c = 0

y * (l.b * m.a - m.b * l.a) + (l.c * m.a - m.c * l.a) = 0
x * m.a + y * m.b + m.c = 0


y = (m.c * l.a - l.c * m.a) / (l.b * m.a - m.b * l.a)
x * l.a + (m.c * l.a - l.c * m.a) / (l.b * m.a - m.b * l.a) * l.b + l.c = 0

x + (m.c * l.b - m.b * l.c) / (l.b * m.a - m.b * l.a) = 0

x = (m.b * l.c - m.c * l.b) / (l.b * m.a - m.b * l.a)

*/

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

Vec getPoint(Line l) {
  return Vec(-l.b, l.a);
}

bool bad(Line a, Line b, Line c) {
  Point x;
  assert(cross(b, c, x) == 1);
  return a.eval(x) > 0;
}

// Do not forget about the bounding box
vector<Point> hpi(vector<Line> lines) {
  sort(all(lines), [](Line al, Line bl) -> bool {
    Point a = getPoint(al);
    Point b = getPoint(bl);
    if (a.y >= 0 && b.y < 0) return 1;
    if (a.y < 0 && b.y >= 0) return 0;
    if (a.y == 0 && b.y == 0) return a.x > 0 && b.x < 0;
    return (a ^ b) > 0;
  });

  vector<pair<Line, int> > st;
  for (int it = 0; it < 2; it++) {
    for (int i = 0; i < (int)lines.size(); i++) {
      bool flag = false;
      while (!st.empty()) {
        if ((getPoint(st.back().first) - getPoint(lines[i])).len() < EPS) {
          if (lines[i].c <= st.back().first.c) {
            flag = true;
            break;
          } else {
            st.pop_back();
          }
        } else if ((getPoint(st.back().first) ^ getPoint(lines[i])) <
                   EPS / 2) {
          return {};
        } else if (st.size() >= 2 &&
                   bad(st[st.size() - 2].first, st[st.size() - 1].first,
                       lines[i])) {
          st.pop_back();
        } else {
          break;
        }
      }
      if (!flag) st.push_back({lines[i], i});
    }
  }

  vector<int> en(lines.size(), -1);
  vector<Point> ans;
  for (int i = 0; i < (int)st.size(); i++) {
    if (en[st[i].second] == -1) {
      en[st[i].second] = i;
      continue;
    }
    for (int j = en[st[i].second]; j < i; j++) {
      Point I;
      assert(cross(st[j].first, st[j + 1].first, I) == 1);
      ans.push_back(I);
    }
    break;
  }
  return ans;
}

bool isHpiEmpty(vector<Line> lines) {
  // return hpi(lines).empty();
  // overflow/precision problems?
  shuffle(all(lines), rnd);
  const ld C = 1e9;
  Point ans(C, C);
  vector<Point> box = {{-C, -C}, {C, -C}, {C, C}, {-C, C}};
  for (int i = 0; i < 4; ++i) lines.push_back({box[i], box[(i + 1) % 4]});
  int n = lines.size();
  for (int i = n - 4; i >= 0; --i) {
    if (lines[i].isIn(ans)) continue;
    Point up(0, C + 1), down(0, -C - 1), pi = getPoint(lines[i]);
    for (int j = i + 1; j < n; ++j) {
      if (lines[i] == lines[j]) continue;
      Point p, pj = getPoint(lines[j]);
      if (!cross(lines[i], lines[j], p)) {
        if (sign(pi * pj) != -1) continue;
        if (sign(lines[i].c + lines[j].c) * (!sign(pi.y) ? sign(pi.x) : -1) == -1)
          return true;
      } else {
        if ((!sign(pi.y) ? sign(pi.x) : sign(pi.y)) * (sign(pi ^ pj)) == 1)
          chkmin(up, p);
        else
          chkmax(down, p);
      }
    }
    if ((ans = up) < down) return true;
  }
  // for (int i = 0; i < n; ++i) {
  //   assert(lines[i].eval(ans) < EPS);
  // }
  return false;
}

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

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cout.precision(20), cout.setf(ios::fixed);

  // Tinkoff Generation 2021-2022. C. Геометрия 1 A - Площадь треугольника
  /*{
    Point a, b, c;
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
    cout << abs((b - a) ^ (c - a)) / 2 << endl;
  }*/

  // Tinkoff Generation 2021-2022. C. Геометрия 1 B - Угол между векторами
  /*{
    Vec a, b;
    cin >> a.x >> a.y >> b.x >> b.y;
    cout << abs(getAngle(a, b)) << endl;
  }*/

  // Tinkoff Generation 2021-2022. C. Геометрия 1 C - Точка в углу
  /*{
    Point a, o, b, p;
    cin >> a.x >> a.y >> o.x >> o.y >> b.x >> b.y >> p.x >> p.y;
    a = a - o;
    b = b - o;
    if (sign(a ^ b) <= 0) {
      swap(a, b);
    }
    p = p - o;
    bool ok = true;
    if (sign(a ^ b) == 1) {
      ok = sign(a ^ p) >= 0 && sign(p ^ b) >= 0;
    } else {
      ok = !(sign(a ^ p) < 0 && sign(p ^ b) < 0);
    }
    if (ok) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }*/

  // Tinkoff Generation 2021-2022. C. Геометрия 1 D - Пересечение отрезков
  /*{
    Point a, b, c, d;
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;
    if (isCrossed(a, b, c, d)) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }*/

  // Tinkoff Generation 2021-2022. C. Геометрия 1 E - Расстояние от точки
  // до прямой
  /*{
    Point p;
    cin >> p.x >> p.y;
    Line l;
    cin >> l.a >> l.b >> l.c;
    cout << dist(l, p) << endl;
  }*/

  // Tinkoff Generation 2021-2022. C. Геометрия 1 F - Пересечение прямых
  /*{
    Point a, b, c, d;
    Line l, m;
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;
    l = Line(a, b);
    m = Line(c, d);
    Point ans;
    if (cross(l, m, ans)) {
      cout << 1 << " " << ans.x << " " << ans.y << endl;
    } else if (l == m) {
      cout << 2 << endl;
    } else {
      cout << 0 << endl;
    }
  }*/

  // Tinkoff Generation 2021-2022. C. Геометрия 1 G - Пусти козла в
  // огород~- 1
  /*{
    Point a, b, c;
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
    auto calc = [](Vec lhs, Vec rhs) -> ld {
      ld sgn = sign(lhs ^ rhs);
      if (!sgn) {
        return 180;
      }
      if (sgn < 0) {
        swap(lhs, rhs);
      }
      return atan2(lhs ^ rhs, lhs * rhs) / (2 * PI) * 360;
    };
    cout << max({calc(b - a, c - a), calc(c - b, a - b), calc(a - c, b -
  c)}) << endl;
  }*/

  // Tinkoff Generation 2021-2022. C. Геометрия 1 H - Биссектриса
  /*{
    Point x, y, z;
    cin >> x.x >> x.y >> y.x >> y.y >> z.x >> z.y;
    y = (y - x).norm();
    z = (z - x).norm();
    Line l(x, x + y + z);
    cout << l.a << " " << l.b << " " << l.c << endl;
  }*/

  // Tinkoff Generation 2021-2022. C. Геометрия 1 I - Пусти козла в огород
  // - 4
  /*{
    Point a, b, c;
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
    Vec v1, v2;
    v1 = (b - a).norm();
    v2 = (c - a).norm();
    Line l(a, a + v1 + v2);
    v1 = (a - b).norm();
    v2 = (c - b).norm();
    Line m(b, b + v1 + v2);
    Point ans;
    if (cross(l, m, ans)) {
      cout << ans.x << " " << ans.y << endl;
    } else {
      assert(false);
    }
  }*/

  // Tinkoff Generation 2021-2022. C. Геометрия 2 A - Касательные к
  // окружности
  /*{
    Point o, p;
    ld r;
    cin >> o.x >> o.y >> r >> p.x >> p.y;
    Point I1, I2;
    int ans = tangents(o, r, p, I1, I2);
    if (!ans) {
      cout << ans << endl;
    } else if (ans == 1) {
      cout << ans << "\n" << I1.x << " " << I1.y << endl;
    } else if (ans == 2) {
      cout << ans << "\n" << I1.x << " " << I1.y << "\n" << I2.x << " " <<
  I2.y << endl;
    }
  }*/

  // Tinkoff Generation 2021-2022. C. Геометрия 2 B - Пересекаем окружности
  /*{
    int t;
    cin >> t;
    while (t--) {
      Point o1, o2;
      ld r1, r2;
      cin >> o1.x >> o1.y >> r1 >> o2.x >> o2.y >> r2;
      Point I1, I2;
      int ans = cross(o1, r1, o2, r2, I1, I2);
      if (!ans || ans == 3) {
        cout << ans << endl;
      } else if (ans == 1) {
        cout << ans << "\n" << I1.x << " " << I1.y << endl;
      } else if (ans == 2) {
        Point fans = (I1 + I2) / 2;
        cout << ans << "\n"
             << fans.x << " " << fans.y << "\n"
             << (o1 - fans).len() << " " << (I1 - fans).len() << "\n"
             << I1.x << " " << I1.y << "\n"
             << I2.x << " " << I2.y << endl;
      }
    }
  }*/

  // Tinkoff Generation 2021-2022. C. Геометрия 2 C - Прямая и окружность
  /*{
    Point o;
    ld r;
    Line l;
    cin >> o.x >> o.y >> r >> l.a >> l.b >> l.c;
    Point I1, I2;
    int ans = cross(o, r, l, I1, I2);
    if (!ans) {
      cout << ans << endl;
    } else if (ans == 1) {
      cout << ans << "\n" << I1.x << " " << I1.y << endl;
    } else if (ans == 2) {
      cout << ans << "\n" << I1.x << " " << I1.y << "\n" << I2.x << " " <<
  I2.y << endl;
    }
  }*/

  // Tinkoff Generation 2021-2022. C. Геометрия 2 D - Площадь
  // многоугольника
  /*{
    int n;
    cin >> n;
    vector<Point> p(n);
    for (auto& [x, y] : p) {
      cin >> x >> y;
    }
    ld ans = area(p);
    cout << (ll)(ans) << (sign(ans - (ll)ans) == 1 ? ".5" : "") << endl;
  }*/

  // Tinkoff Generation 2021-2022. C. Геометрия 2 E - Точка в
  // многоугольнике
  /*{
#ifndef LOCAL
    freopen("point.in", "r", stdin);
    freopen("point.out", "w", stdout);
#endif
    int n;
    cin >> n;
    Point a;
    cin >> a.x >> a.y;
    vector<Point> p(n);
    for (auto& [x, y] : p) {
      cin >> x >> y;
    }
    if (isIn(p, a)) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }*/

  // Tinkoff Generation 2021-2022. C. Геометрия 2 F - Выпукл ли
  // многоугольник
  /*{
    int n;
    cin >> n;
    vector<Point> p(n);
    for (auto& [x, y] : p) {
      cin >> x >> y;
    }
    if (isConvex(p)) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }*/

  // Tinkoff Generation 2021-2022. C. Геометрия 2 G - Теодор Рузвельт
  /*{
    int n, m, k;
    cin >> n >> m >> k;
    vector<Point> p(n);
    for (auto& [x, y] : p) {
      cin >> x >> y;
    }
    assert(isConvex(p));
    assert(isCounterclockwise(p));
    int cnt = 0;
    for (int i = 0; i < m; ++i) {
      Point a;
      cin >> a.x >> a.y;
      if (isInConvex(p, a)) {
        ++cnt;
      }
    }
    if (cnt >= k) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }*/

  // Tinkoff Generation 2021-2022. B'. Геометрия 2 B - Замок
  /*{
    int n;
    cin >> n;
    vector<vector<Point>> p(n);
    vector<ld> areas(n);
    for (int i = 0; i < n; ++i) {
      int k;
      cin >> k;
      p[i].resize(k);
      for (auto& [x, y] : p[i]) {
        cin >> x >> y;
      }
      areas[i] = area(p[i]);
    }
    vector<int> order(n);
    iota(all(order), 0);
    sort(all(order), [&](int lhs, int rhs) -> bool { return areas[lhs] <
  areas[rhs]; }); vector<bool> used(n); int q; cin >> q; for (int i = 0; i
  < q; ++i) { Point a; cin >> a.x >> a.y; int L = -1, R = n; while (L < R -
  1) { int M = (L + R) / 2; if (isInConvex(p[order[M]], a)) { R = M; } else
  { L = M;
        }
      }
      if (R < n)
        used[R] = true;
    }
    ld ans = 0;
    for (int i = 0; i < n; ++i) {
      if (used[i]) {
        ans += areas[order[i]] - (i > 0 ? areas[order[i - 1]] : 0);
      }
    }
    cout << ans << endl;
  }*/

  // Tinkoff Generation 2021-2022. B'. Геометрия 2 D - Выпуклая оболочка
  /*{
#ifndef LOCAL
    freopen("hull.in", "r", stdin);
    freopen("hull.out", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<Point> p(n);
    for (auto& [x, y] : p) {
      cin >> x >> y;
    }
    p = convexHull(p);
    cout << p.size() << '\n';
    for (auto& [x, y] : p) {
      cout << (ll)(round(x)) << " " << (ll)(round(y)) << '\n';
    }
    ld ans = area(p);
    cout << (ll)(ans) << (sign(ans - (ll)ans) == 1 ? ".5" : "") << endl;
  }*/

  // Stress tangents, fast point location
  /* {
    int N = 100000;
    int C = 1e9;
    int Q = 100;
    auto get = [&] (int l, int r) -> int {
      return (ull)rnd() % (r - l + 1) + l;
    };
    auto stupidTangents = [&] (vector<Point>& p, Point& a) {
      auto cmp = [&](Point& lhs, Point& rhs) -> bool {
        return sign((lhs - a) ^ (rhs - a)) > 0;
      };
      int posL = min_element(all(p), cmp) - p.begin();
      int posR = max_element(all(p), cmp) - p.begin();
      return mp(posL, posR);
    };
    for (int test_id = 0; test_id < 1'000'000; ++test_id) {
      int n = get(1, N);
      vector<Point> p(n);
      for (int i = 0; i < n; ++i) {
        p[i] = Point(get(-C, C), get(-C, C));
      }
      p = convexHull(p);
      n = p.size();
      for (int i = 0; i < Q; ++i) {
        Point a(-C, C);
        if (p.size() >= 3) {
          if(isInConvex(p, a) != isIn(p, a)) {
            cerr << "WA convex " << test_id << " " << i << endl;
            cerr << "n = " << n << endl;
            cerr << "p = " << endl;
            for (auto [x, y] : p) {
              cerr << "(" << x << ", " << y << ")" << endl;
            }
            cerr << "a = " << endl;
            cerr << "(" << a.x << " " << a.y << ")" << endl;
            cerr << "ans = " << isIn(p, a) << endl;
            cerr << "out = " << isInConvex(p, a) << endl;
            exit(1);
          }
        }
        if (isIn(p, a)) continue;
        auto ans = stupidTangents(p, a);
        auto out = tangents_alex(p, a);
        bool ok = true;
        if (sign((p[ans.first] - a) ^ (p[out.first] - a)) != 0) {
          ok = false;
        } else if (sign((p[ans.second] - a) ^ (p[out.second] - a)) != 0) {
          ok = false;
        }
        if (!ok) {
          cerr << "WA tangents " << test_id << " " << i << endl;
          cerr << "n = " << n << endl;
          cerr << "p = " << endl;
          for (auto [x, y] : p) {
            cerr << "(" << x << ", " << y << ")" << endl;
          }
          cerr << "a = " << endl;
          cerr << "(" << a.x << " " << a.y << ")" << endl;
          cerr << "ans = " << ans.first << " " << ans.second << endl;
          cerr << "out = " << out.first << " " << out.second << endl;
          exit(1);
        }
      }
      cerr << "OK " << test_id << endl;
    }
  } */

  // Tinkoff Generation 2021-2022. B'. Геометрия C - Сыр (Offlin + check
  // Online tangents)
  /*{
    int n;
    cin >> n;
    vector<Point> p(n);
    for (auto& [x, y] : p) {
      cin >> x >> y;
    }
    p = convexHull(p);
    n = p.size();
    int m;
    cin >> m;
    vector<Point> pIn(m);
    for (auto& [x, y] : pIn) {
      cin >> x >> y;
    }
    pIn = convexHull(pIn);
    m = pIn.size();
    Point base = p[0];
    auto cmp = [&](Point& lhs, Point& rhs) -> bool {
      return sign((lhs - base) ^ (rhs - base)) > 0;
    };
    int posL = min_element(all(pIn), cmp) - pIn.begin();
    int nxtL = 1;
    auto nxtV = [](int v, int n) -> int { return v + 1 < n ? v + 1 : 0; };
    auto moveL = [&]() {
      while (cmp(pIn[nxtV(posL, m)], pIn[posL])) posL = nxtV(posL, m);
      assert(sign((pIn[posL] - base) ^ (pIn[tangents_alex(pIn, base).first]
  - base)) == 0); while (cmp(p[nxtV(nxtL, n)], pIn[posL])) nxtL =
  nxtV(nxtL, n);
    };
    int posR = max_element(all(pIn), cmp) - pIn.begin();
    int nxtR = 0;
    auto moveR = [&]() {
      while (cmp(pIn[posR], pIn[nxtV(posR, m)])) posR = nxtV(posR, m);
      assert(sign((pIn[posR] - base) ^ (pIn[tangents_alex(pIn,
  base).second] - base)) == 0); while (!cmp(pIn[posR], p[nxtR])) nxtR =
  nxtV(nxtR, n);
    };
    vector<ll> prefArea(n);
    for (int i = 2; i < n; ++i) {
      prefArea[i] = abs(round((p[i - 1] - p[0]) ^ (p[i] - p[0])));
      prefArea[i] += prefArea[i - 1];
    }
    auto calcArea = [&](int l, int r) -> ll {
      ll fans;
      if (l <= r) {
        if (r - l < 2) return 0;
        fans = prefArea[r] - prefArea[l] - abs(round((p[l] - p[0]) ^ (p[r]
  - p[0]))); } else { fans = prefArea[n - 1] - prefArea[l] + prefArea[r] +
  abs(round((p[l] - p[0]) ^ (p[r] - p[0])));
      }
      return fans;
    };
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
      base = p[i];
      moveL();
      moveR();
      chkmax(ans, calcArea(i, nxtL));
      chkmax(ans, calcArea(nxtR, i));
    }
    cout << ans << endl;
  }*/

  // Tinkoff Generation 2021-2022. B'. Геометрия 2 E - Разрезание торта
  /*{
#ifndef LOCAL
    freopen("cut.in", "r", stdin);
    freopen("cut.out", "w", stdout);
#endif
    ld C = 1e3 + 228;
    int n;
    cin >> n;
    vector<Point> p(n);
    for (auto& [x, y] : p) {
      cin >> x >> y;
    }
    if (!isCounterclockwise(p)) {
      reverse(all(p));
    }
    ld need = area(p) / 2;

    auto calc1 = [&](ld x) -> ld {
      vector<Point> has;
      Point D(x, -C);
      Point U(x, C);
      Line l(D, U);
      for (int i = 0; i < n; ++i) {
        if (p[i].x < x) {
          has.push_back(p[i]);
        }
        Point cur = p[i];
        Point nxt = p[i + 1 < n ? i + 1 : 0];
        if (sign(cur.x - nxt.x) != 0) {
          if (!isCrossed(D, U, cur, nxt))
            continue;
          Point I;
          assert(cross(l, Line(cur, nxt), I) == 1);
          has.push_back(I);
        }
      }
      return area(convexHull(has));
    };

    auto calc2 = [&](ld x) -> ld {
      Point D(x, -C);
      Point U(x, C);
      Line l(D, U);
      vector<Line> lines;
      for (int i = 0; i < n; ++i) {
        lines.emplace_back(p[i], p[i + 1 < n ? i + 1 : 0]);
      }
      lines.push_back(l);
      return area(hpi(lines));
    };

    ld L = -C, R = C;
    for (int it = 0; it < 60; ++it) {
      ld M = (L + R) / 2;
      assert(sign(calc1(M) - calc2(M)) == 0);
      if (calc1(M) < need) {
        L = M;
      } else {
        R = M;
      }
    }
    cout << R << endl;
  }*/

  // Tinkoff Generation 2021-2022. B'. Геометрия 2 H - Две самые далёкие
  // точки
  /*{
    int n;
    cin >> n;
    vector<Point> p(n);
    for (auto& [x, y] : p) {
      cin >> x >> y;
    }
    cout << diameter(p) << endl;
  }*/

  // Tinkoff Generation 2021-2022. B'. Геометрия 2 K - Стена
  /*{
#ifndef LOCAL
    freopen("wall.in", "r", stdin);
    freopen("wall.out", "w", stdout);
#endif
    int n, l;
    cin >> n >> l;
    vector<Point> p(n);
    for (auto& [x, y] : p) {
      cin >> x >> y;
    }
    ld ans = perimeter(convexHull(p)) + 2 * PI * l;
    cout << ans << endl;
  }*/

  // Stress isHpiEmpty, hpi
  {
    int N = 10;
    int C = 10;
    auto get = [&](int l, int r) -> int {
      return (ull)rnd() % (r - l + 1) + l;
    };
    auto getPoint = [&]() -> Point {
      return Point(get(-C, C), get(-C, C));
    };
    for (int test_id = 0;; ++test_id) {
      int n = get(1, N);
      vector<Line> lines(n);
      for (int i = 0; i < n; ++i) {
        Point a = getPoint();
        Point b = getPoint();
        while (a == b) {
          b = getPoint();
        }
        lines[i] = {a, b};
      }
      // cerr << "n = " << n << endl;
      // cerr << "lines = " << endl;
      // for (auto [a, b, c] : lines) {
      //   cerr << "x * " << a << " + y * " << b << " + " << c << " = 0" <<
      //   endl;
      // }
      const ld C = 1e9;
      vector<Point> box = {{-C, -C}, {C, -C}, {C, C}, {-C, C}};
      for (int i = 0; i < 4; ++i) {
        lines.push_back({box[i], box[(i + 1) % 4]});
      }
      bool ans = hpi(lines).empty();
      lines.resize(n);
      bool out = isHpiEmpty(lines);
      if (ans == 0 && out == 1) {
        cerr << "WA isHpiEmpty " << test_id << endl;
        cerr << "n = " << n << endl;
        cerr << "lines = " << endl;
        for (auto [a, b, c] : lines) {
          cerr << "x * " << a << " + y * " << b << " + " << c << " = 0"
               << endl;
        }
        cerr << "ans = " << ans << endl;
        cerr << "out = " << out << endl;
        exit(1);
      }
      cerr << "OK " << test_id << " ans = " << ans << endl;
    }
  }

  // 2021-2022 ICPC NERC (NEERC), North-Western Russia Regional Contest
  // (Northern Subregionals) G https://codeforces.com/gym/104011/problem/G
  /* {
    int n;
    cin >> n;
    vector<Point> p(n);
    for (auto& [x, y] : p) {
      cin >> x >> y;
    }
    int pos = min_element(all(p)) - p.begin();
    rotate(p.begin(), p.begin() + pos, p.end());
    vector<Point> v;
    for (int i = 0; i < n; ++i) {
      v.push_back(p[i + 1 < n ? i + 1 : 0] - p[i]);
    }
    vector<int> fpos(n);
    for (int i = 0; i < n; ++i) {
      int pos = lower_bound(all(v), Point() - v[i], cmpHalf) - v.begin();
      pos = pos % n;
      fpos[i] = pos;
    }
    auto check = [&](ld x) -> bool {
      vector<Line> lines;
      lines.reserve(2 * n);
      auto addLine = [&](int i, int j) {
        Vec v1 = (p[j] - p[i]) * (x / (x + 1));
        Vec v2 = (p[j + 1 < n ? j + 1 : 0] - p[i]) * (x / (x + 1));
        lines.push_back({p[i] + v1, p[i] + v2});
      };
      for (int i = 0; i < n; ++i) {
        int pos = fpos[i];
        addLine(i, pos);
        addLine(pos, i);
      }
      return !isHpiEmpty(lines);
    };
    ld L = 1, R = 2;
    for (int it = 0; it < 19; ++it) {
      ld M = sqrt(L * R);
      if (check(M)) {
        R = M;
      } else {
        L = M;
      }
    }
    cout << sqrt(L * R) << endl;
  } */
  return 0;
}