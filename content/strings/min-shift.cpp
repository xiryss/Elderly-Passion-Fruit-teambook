string minshift(string s) {
    int i = 0, ans = 0;
    s += s;
    int n = s.size();
    while (i < n / 2) {
        ans = i;
        int j = i + 1, k = i;
        while (j < n && s[k] <= s[j]) {
            if (s[k] < s[j]) k = i;
            else ++k;
            ++j;
        }
        while (i <= k) {
            i += j - k;
        }
    }
    return s.substr(ans, n / 2);
}
