struct eertree {
    int len[MAXN], suffLink[MAXN];
    int to[MAXN][26];
    int numV, v;
    void addLetter(int n, string& str) {
        while (str[n - len[v] - 1] != str[n])
            v = suffLink[v];
        int u = suffLink[v];
        while (str[n - len[u] - 1] != str[n])
            u = suffLink[u];
        int u_ = to[u][str[n] - 'a'];
        int v_ = to[v][str[n] - 'a'];
        if (v_ == -1) {
            v_ = to[v][str[n] - 'a'] = numV;
            len[numV++] = len[v] + 2;
            suffLink[v_] = u_;
        }
        v = v_;
    }
    void init() {
        len[0] = -1;
        len[1] = 0;
        suffLink[1] = 0;
        suffLink[0] = 0;
        numV = 2;
        for (int i = 0; i < 26; ++i) {
            to[0][i] = numV++;
            suffLink[numV - 1] = 1;
            len[numV - 1] = 1;
        }
        v = 0;
    }
    void init(int sz) {
        for (int i = 0; i < sz; ++i) {
            len[i] = suffLink[i] = 0;
            for (int j = 0; j < 26; ++j) to[i][j] = -1;
        }
    }
};
