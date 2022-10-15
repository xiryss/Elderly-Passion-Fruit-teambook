vector<int> pf(string s)
{
    int k = 0;
    vector<int> p(s.size());
    for (int i = 1; i < s.size(); ++i) {
        while (k && s[i] != s[k]) k = p[k - 1];
        k += (s[i] == s[k]);
        p[i] = k;
    }
    return p;
}
vector<int> zf(string s)
{
    int n = s.size();
    vector<int> z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    z[0] = n;
    return z;
}
