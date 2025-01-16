vector<int> kmp(string s, string t) {
    int n = s.size(), m = t.size();

    vector<int> nxt(m + 1);
    s = "-" + s;
    t = "-" + t;

    for (int i = 2, j = 0; i <= m; i++) {
        while (j && t[i] != t[j + 1]) j = nxt[j];
        if (t[i] == t[j + 1]) j++;
        nxt[i] = j;
    }
    vector<int>vis(n + 1);
    for (int i = 1, j = 0; i <= n; i++) {
        while (j && s[i] != t[j + 1]) j = nxt[j];
        if (s[i] == t[j + 1]) j++;
        if (j == m) {
            vis[i - m + 1] ++;
            j = nxt[j];
        }
    }
    return vis;
}