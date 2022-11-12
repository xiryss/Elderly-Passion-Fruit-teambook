/**
 * Author: Igor Markelov
 * Date: 2022-11-12
 * Source: https://e-maxx.ru/algo/matching_edmonds
 * Description: Maximum matching in general graph
 * Time: O(n^3)
 */

struct Edge {
  int u, v;
};
const int N = 510;
int n, m;
vector<int> g[N];
vector<Edge> perfectMatching;
int match[N], par[N], base[N];
bool used[N], blossom[N], lcaUsed[N];
int lca(int u, int v) {
  fill(lcaUsed, lcaUsed + n, false);
  while (u != -1) {
    u = base[u];
    lcaUsed[u] = true;
    if (match[u] == -1)
      break;
    u = par[match[u]];
  }
  while (v != -1) {
    v = base[v];
    if (lcaUsed[v])
      return v;
    v = par[match[v]];
  }
  assert(false);
  return -1;
}
void markPath(int v, int myBase, int children) {
  while (base[v] != myBase) {
    blossom[v] = blossom[match[v]] = true;
    par[v] = children;
    children = match[v];
    v = par[match[v]];
  }
}
int findPath(int root) {
  iota(base, base + n, 0);
  fill(par, par + n, -1);
  fill(used, used + n, false);
  queue<int> q;
  q.push(root);
  used[root] = true;
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (auto to : g[v]) {
      if (match[v] == to)
        continue;
      if (base[v] == base[to])
        continue;
      if (to == root || (match[to] != -1 && par[match[to]] != -1)) {
        fill(blossom, blossom + n, false);
        int myBase = lca(to, v);
        markPath(v, myBase, to);
        markPath(to, myBase, v);
        for (int u = 0; u < n; ++u) {
          if (!blossom[base[u]])
            continue;
          base[u] = myBase;
          if (used[u])
            continue;
          used[u] = true;
          q.push(u);
        }
      } else if (par[to] == -1) {
        par[to] = v;
        if (match[to] == -1) {
          return to;
        }
        used[match[to]] = true;
        q.push(match[to]);
      }
    }
  }
  return -1;
}
void blossomShrinking() {
  fill(match, match + n, -1);
  for (int v = 0; v < n; ++v) {
    if (match[v] != -1)
      continue;
    int nxt = findPath(v);
    while (nxt != -1) {
      int parV = par[nxt];
      int parParV = match[parV];
      match[nxt] = parV;
      match[parV] = nxt;
      nxt = parParV;
    }
  }
  for (int v = 0; v < n; ++v) {
    if (match[v] != -1 && v < match[v]) {
      perfectMatching.push_back({v, match[v]});
    }
  }
}
signed main() {
  cin >> n;
  int u, v;
  set<pair<int, int>> edges;
  while (cin >> u >> v) {
    --u;
    --v;
    if (u > v)
      swap(u, v);
    if (edges.count({u, v}))
      continue;
    edges.insert({u, v});
    g[u].push_back(v);
    g[v].push_back(u);
  }
  blossomShrinking();
  cout << perfectMatching.size() * 2 << '\n';
  for (auto i : perfectMatching) {
    cout << i.u + 1 << " " << i.v + 1 << "\n";
  }
  return 0;
}
