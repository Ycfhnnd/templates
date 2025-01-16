template <class T>
struct ST {
    int n, L;
    vector<vector<T>> f;
    ST() {}
    void init(int n_, vector<T> a) {
        n = n_;
        L = __lg(n) + 1;
        f.resize(__lg(n) + 2);
        for (int j = 0; j < L; j++) f[j].resize(n + 2);
        for (int i = 1; i <= n; i++) f[0][i] = a[i - 1];
        for (int j = 1; j < L; j++)
            for (int i = 1; i + (1 << j) - 1 <= n; i++)
                f[j][i] = max(f[j - 1][i], f[j - 1][i + (1 << (j - 1))]);
    }
    void add(int pos, T v) {
        f[0][pos] = v;
        for (int j = 1; j < L; j++) {
            int i = pos - (1 << j) + 1;
            if (i >= 1) f[j][i] = max(f[j - 1][i], f[j - 1][i + (1 << (j - 1))]);
        }
    }
    T get(int l, int r) {
        if (l > r) swap(l, r);
        int len = __lg(r - l + 1);
        return max(f[len][l], f[len][r - (1 << len) + 1]);
    }
};