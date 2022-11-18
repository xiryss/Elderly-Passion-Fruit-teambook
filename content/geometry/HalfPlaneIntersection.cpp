/**
 * Author: Igor Markelov (stole from Red Panda teambook)
 * Date: 2022-11-05
 * Description: Find the intersection of the half planes.
 * Time: O(n \log(n))
 */
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