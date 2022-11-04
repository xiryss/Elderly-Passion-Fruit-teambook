#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct MaxFlow {
    static const ll INF = 1e18 + 228;  // maybe int?
    struct edge {
        int to, rev;
        ll cap;  // maybe int?
    };

    int n;
    vector<vector<edge>> g;
    vector<ll> ex;  // maybe int?
    vector<int> q;

    ll flow(int t) {  // maybe int?
        while (true) {
            vector<int> dist(n, n);
            dist[t] = 0;
            int l = 0;
            int r = 1;
            q[0] = t;
            while (l != r) {
                int v = q[l++];
                for (auto e : g[v]) {
                    if (g[e.to][e.rev].cap > 0 && dist[e.to] > dist[v] + 1) {
                        dist[e.to] = dist[v] + 1;
                        q[r++] = e.to;
                    }
                }
            }
            ll was = ex[t];
            for (int ind = r - 1; ind >= 0; ind--) {
                int v = q[ind];
                if (ex[v] == 0)
                    continue;
                for (auto &e : g[v]) {
                    if (dist[e.to] + 1 == dist[v] && e.cap > 0) {
                        auto f = min(ex[v], e.cap);
                        e.cap -= f;
                        ex[e.to] += f;
                        ex[v] -= f;
                        g[e.to][e.rev].cap += f;
                    }
                }
            }
            if (was == ex[t]) {
                break;
            }
        }
        return ex[t];
    }
    MaxFlow(int n) : n(n) {
        g.resize(n);
        ex.resize(n);
        q.resize(n);
    }
    ll run(int s, int t) {  // maybe int?
        ex[s] = INF;
        return flow(t);
    }
    void add_edge(int a, int b, int c, int cr = 0) {
        int sza = g[a].size();
        int szb = g[b].size();
        g[a].push_back({b, szb, c});
        g[b].push_back({a, sza, cr});
    }
};

int main() {
    int n;
    cin >> n;
    MaxFlow mf(n);
    int s = 0, t = n - 1;
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        mf.add_edge(a, b, c);
    }
    cout << mf.run(s, t) << endl;
}
