/**
 * Author: Igor Markelov
 * Date: 2022-11-18
 * Description: Determines is half plane intersectinos.
 * Time: O(n) (expected)
 */

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
