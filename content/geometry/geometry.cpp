#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;

#define pbc push_back
#define mp make_pair
#define all(a) (a).begin(), (a).end()
#define vin(a)      \
  for (auto& i : a) \
  cin >> i

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

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

const ld EPS = 1e-9;
const ld PI = acos(-1);

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
  bool operator==(const Point& other) const {
    return sign(x - other.x) == 0 && sign(y - other.y) == 0;
  }
  Point norm() const {
    ld d = len();
    // maybe change to if (d == 0) return Point();
    assert(sign(d) == 1);
    return Point(x / d, y / d);
  }
};

#define Vec Point

ld getAngle(const Vec& lhs, const Vec& rhs) {
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
  if (lx > rx)
    swap(lx, rx);
  if (ly > ry)
    swap(ly, ry);
  return sign(min(rx, ry) - max(lx, ly)) >= 0;
}

// if two segments [a, b] and [c, d] has AT LEAST one common point -> true
bool isCrossed(const Point& a, const Point& b, const Point& c, const Point& d) {
  if (!isCrossed(a.x, b.x, c.x, d.x))
    return false;
  if (!isCrossed(a.y, b.y, c.y, d.y))
    return false;
  Vec v1, v2, v3;
  v1 = b - a;
  v2 = c - a;
  v3 = d - a;
  if (sign(v1 ^ v2) * sign(v1 ^ v3) == 1)
    return false;
  v1 = d - c;
  v2 = a - c;
  v3 = b - c;
  if (sign(v1 ^ v2) * sign(v1 ^ v3) == 1)
    return false;
  return true;
}

struct Line {
  ld a = 0, b = 0, c = 0;
  Line() = default;
  Line(ld _a, ld _b, ld _c) : a(_a), b(_b), c(_c) {
  }
  Line(const Point& x, const Point& y) : a(y.y - x.y), b(x.x - y.x), c(x.y * y.x - x.x * y.y) {
    // for half planes
    ld d = Vec(a, b).len();
    assert(sign(d) > 0);
    a /= d;
    b /= d;
    c /= d;
  }
  ld eval(const Point& p) const {
    return a * p.x + b * p.y + c;
  }
  bool operator==(const Line& other) const {
    return sign(a * other.b - b * other.a) == 0 && sign(a * other.c - c * other.a) == 0;
  }
};

ld dist(const Line& l, const Point& p) {
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

bool cross(const Line& l, const Line& m, Point& I) {
  ld d = l.b * m.a - m.b * l.a;
  if (sign(d) == 0) {
    return false;
  }
  ld dx = m.b * l.c - m.c * l.b;
  ld dy = m.c * l.a - l.c * m.a;
  I = Point(dx / d, dy / d);
  return true;
}

int touch(const Point& o, const ld r, const Point& p, Point& I1, Point& I2) {
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

int cross(const Point& o, ld r, const Line& l, Point& I1, Point& I2) {
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

ld area(const vector<Point>& p) {
  ld ans = 0;
  int n = p.size();
  for (int i = 0; i < n; ++i) {
    ans += p[i] ^ p[i + 1 < n ? i + 1 : 0];
  }
  return abs(ans) / 2;
}

ld perimeter(const vector<Point>& p) {
  ld ans = 0;
  int n = p.size();
  for (int i = 0; i < n; ++i) {
    ans += (p[i] - p[i + 1 < n ? i + 1 : 0]).len();
  }
  return ans;
}

bool isOnSegment(const Point& a, const Point& b, const Point& x) {
  if (a == b) {
    return a == x;
  }
  return sign((b - a) ^ (x - a)) == 0 && sign((b - a) * (x - a)) >= 0 &&
         sign((a - b) * (x - b)) >= 0;
  // optional (slower, but works better if there are some precision problems)
  // return sign((b - a).len() - (x - a).len() - (x - b).len()) == 0;
}

bool isIn(const vector<Point>& p, const Point& a) {
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

bool isCounterclockwise(const vector<Point>& p) {
  int n = p.size();
  int pos = min_element(all(p)) - p.begin();
  return sign((p[pos + 1 < n ? pos + 1 : 0] - p[pos]) ^
              (p[pos - 1 >= 0 ? pos - 1 : n - 1] - p[pos])) == 1;
}

bool isConvex(const vector<Point>& p) {
  int n = p.size();
  int sgn = 0;
  for (int i = 0; i < n; ++i) {
    int cur_sgn = sign((p[i - 1 >= 0 ? i - 1 : n - 1] - p[i]) ^ (p[i + 1 < n ? i + 1 : 0] - p[i]));
    if (sgn && sgn != cur_sgn) {
      return false;
    }
    sgn = cur_sgn;
  }
  return true;
}

bool isInTriangle(const Point& a, const Point& b, const Point& c, const Point& x) {
  return sign((b - a) ^ (x - a)) >= 0 && sign((c - b) ^ (x - b)) >= 0 &&
         sign((a - c) ^ (x - c)) >= 0;
}

// points should be in the counterclockwise order
bool isInConvex(const vector<Point>& p, const Point& a) {
  int n = p.size();
  assert(n >= 3);
  // assert(isConvex(p));
  // assert(isCounterclockwise(p));
  if (sign((p[1] - p[0]) ^ (a - p[0])) < 0)
    return false;
  if (sign((p[n - 1] - p[0]) ^ (a - p[0])) > 0)
    return false;
  int pos = lower_bound(p.begin() + 2, p.end(), a,
                        [&](const Point& lhs, const Point& rhs) -> bool {
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
  for (int i = 1; i < n; ++i)
    p[i] = p[i] - p[0];
  sort(p.begin() + 1, p.end(), [&](const Point& lhs, const Point& rhs) -> bool {
    int sgn = sign(lhs ^ rhs);
    if (!sgn) {
      return lhs.len2() < rhs.len2();
    }
    return sgn == 1;
  });
  for (int i = 1; i < n; ++i)
    p[i] = p[i] + p[0];
  int top = 0;
  for (int i = 0; i < n; ++i) {
    while (top >= 2) {
      Vec v1 = p[top - 1] - p[top - 2];
      Vec v2 = p[i] - p[top - 1];
      if (sign(v1 ^ v2) == 1)
        break;
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
    if (a.y >= 0 && b.y < 0)
      return 1;
    if (a.y < 0 && b.y >= 0)
      return 0;
    if (a.y == 0 && b.y == 0)
      return a.x > 0 && b.x < 0;
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
        } else if ((getPoint(st.back().first) ^ getPoint(lines[i])) < EPS / 2) {
          return {};
        } else if (st.size() >= 2 &&
                   bad(st[st.size() - 2].first, st[st.size() - 1].first, lines[i])) {
          st.pop_back();
        } else {
          break;
        }
      }
      if (!flag)
        st.push_back({lines[i], i});
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
    while (sign((p[i + 1 < n ? i + 1 : 0] - p[i]) ^ (p[j + 1 < n ? j + 1 : 0] - p[j])) >= 0) {
      chkmax(ans, (p[i] - p[j]).len());
      j = j + 1 < n ? j + 1 : 0;
    }
    chkmax(ans, (p[i] - p[j]).len());
    ++i;
  }
  return ans;
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

  // Tinkoff Generation 2021-2022. C. Геометрия 1 E - Расстояние от точки до прямой
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

  // Tinkoff Generation 2021-2022. C. Геометрия 1 G - Пусти козла в огород~- 1
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
    cout << max({calc(b - a, c - a), calc(c - b, a - b), calc(a - c, b - c)}) << endl;
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

  // Tinkoff Generation 2021-2022. C. Геометрия 1 I - Пусти козла в огород - 4
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

  // Tinkoff Generation 2021-2022. C. Геометрия 2 A - Касательные к окружности
  /*{
    Point o, p;
    ld r;
    cin >> o.x >> o.y >> r >> p.x >> p.y;
    Point I1, I2;
    int ans = touch(o, r, p, I1, I2);
    if (!ans) {
      cout << ans << endl;
    } else if (ans == 1) {
      cout << ans << "\n" << I1.x << " " << I1.y << endl;
    } else if (ans == 2) {
      cout << ans << "\n" << I1.x << " " << I1.y << "\n" << I2.x << " " << I2.y << endl;
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
      cout << ans << "\n" << I1.x << " " << I1.y << "\n" << I2.x << " " << I2.y << endl;
    }
  }*/

  // Tinkoff Generation 2021-2022. C. Геометрия 2 D - Площадь многоугольника
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

  // Tinkoff Generation 2021-2022. C. Геометрия 2 E - Точка в многоугольнике
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

  // Tinkoff Generation 2021-2022. C. Геометрия 2 F - Выпукл ли многоугольник
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
    sort(all(order), [&](int lhs, int rhs) -> bool { return areas[lhs] < areas[rhs]; });
    vector<bool> used(n);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
      Point a;
      cin >> a.x >> a.y;
      int L = -1, R = n;
      while (L < R - 1) {
        int M = (L + R) / 2;
        if (isInConvex(p[order[M]], a)) {
          R = M;
        } else {
          L = M;
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
    for (const auto& [x, y] : p) {
      cout << (ll)(round(x)) << " " << (ll)(round(y)) << '\n';
    }
    ld ans = area(p);
    cout << (ll)(ans) << (sign(ans - (ll)ans) == 1 ? ".5" : "") << endl;
  }*/

  // Tinkoff Generation 2021-2022. B'. Геометрия 2 E - Разрезание торта
  /*{
#ifndef LOCAL
    freopen("cut.in", "r", stdin);
    freopen("cut.out", "w", stdout);
#endif
    const ld C = 1e3 + 228;
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

  // Tinkoff Generation 2021-2022. B'. Геометрия 2 H - Две самые далёкие точки
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

  return 0;
}
