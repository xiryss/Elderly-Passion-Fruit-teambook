const ld EPS = 1e-9;
ld sq(ld a) {
    return a * a;
}
struct Point {
    ld x, y;
    Point() {
    }
    Point(ld _x, ld _y) {
        x = _x;
        y = _y;
    }
    Point operator-(const Point &other) const {
        return Point(x - other.x, y - other.y);
    }
    ld operator^(const Point &other) const {
        return x * other.y - y * other.x;
    }
    ld len2() const {
        return sq(x) + sq(y);
    }
    ld len() const {
        return sqrt(len2());
    }
};
#define Vec Point
struct line {
    ld a, b, c;
    line() {
    }
    // То, что слева от вектора xy лежит в полуплоскости
    line(Point x, Point y) : a(y.y - x.y), b(x.x - y.x), c(x.y * y.x - x.x * y.y) {
        ld d = Vec(a, b).len();
        a /= d;
        b /= d;
        c /= d;
    }
};
Point cross(line l, line m) {
    ld d = l.b * m.a - l.a * m.b;
    ld dx = l.c * m.b - l.b * m.c;
    ld dy = l.a * m.c - l.c * m.a;
    return Point(dx / d, dy / d);
}
Vec getPoint(line l) {
    return Vec(-l.b, l.a);
}
ld eval(line l, Point a) {
    return l.a * a.x + l.b * a.y + l.c;
}
bool bad(line a, line b, line c) {
    Point x = cross(b, c);
    return eval(a, x) > 0;
}
// Не забываем про bounding box
vector<Point> hpi(vector<line> lines) {
    sort(all(lines), [](line al, line bl) -> bool {
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

    vector<pair<line, int> > st;
    for (int it = 0; it < 2; it++) {
        for (int i = 0; i < lines.size(); i++) {
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
    for (int i = 0; i < st.size(); i++) {
        if (en[st[i].second] == -1) {
            en[st[i].second] = i;
            continue;
        }
        for (int j = en[st[i].second]; j < i; j++) {
            ans.push_back(cross(st[j].first, st[j + 1].first));
        }
        break;
    }
    return ans;
}
