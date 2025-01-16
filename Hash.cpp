struct Hash {
    vector<i64> p, h, uh;
    const i64 P = 131;
    const i64 mod = 1e9 + 9;
    Hash() {}
    void init(string s){
        int n = s.size();
        p.resize(n + 2);
        h.resize(n + 2);
        uh.resize(n + 2);
        p[0] = 1;

        for (int i = 0; i < n; i++) {
            p[i + 1] = p[i] * P % mod;
            h[i + 1] = (h[i] * P % mod + s[i]) % mod;
        }
        
        for (int i = n - 1; i >= 0; i--) {
            uh[i + 1] = (uh[i + 2] * P % mod + s[i]) % mod;
        }
    }
    i64 getL(int l, int r) {
        return (h[r] - h[l - 1] * p[r - l + 1] % mod + mod) % mod;
    }
    i64 getR(int l, int r) {
        return (uh[l] - uh[r + 1] * p[r - l + 1] % mod + mod) % mod;
    }
    bool check(int l, int r, int len) {//反转l到r后字符串是否回文
        i64 dex = (h[len] - getL(l, r) * p[len - r] % mod + getR(l, r) * p[len - r] % mod + mod) % mod;
        i64 dey = (uh[1] - getR(l, r) * p[l - 1] % mod + getL(l, r) * p[l - 1] % mod + mod) % mod;
        return dex == dey;
    }
};

struct DoubleHash {
    vector<i64> p1, h1, uh1, p2, h2, uh2;
    const i64 P1 = 9527;
    const i64 mod1 = 1e9 + 9;
    const i64 P2 = 3960; 
    const i64 mod2 = 998244353; 
    int len;

    DoubleHash() {}
    void init(string s){
        len = s.size();
        p1.resize(len + 2);
        h1.resize(len + 2);
        uh1.resize(len + 2);
        p2.resize(len + 2);
        h2.resize(len + 2);
        uh2.resize(len + 2);
        p1[0] = p2[0] = 1;

        for (int i = 1; i <= len; i++) {
            p1[i] = p1[i - 1] * P1 % mod1;
            h1[i] = (h1[i - 1] * P1 % mod1 + s[i - 1]) % mod1;

            p2[i] = p2[i - 1] * P2 % mod2;
            h2[i] = (h2[i - 1] * P2 % mod2 + s[i - 1]) % mod2;
        }

        for (int i = len; i >= 1; i--) {
            uh1[i] = (uh1[i + 1] * P1 % mod1 + s[i - 1]) % mod1;
            uh2[i] = (uh2[i + 1] * P2 % mod2 + s[i - 1]) % mod2;
        }
    }

    i64 getL(int l, int r) {
        return (h1[r] - h1[l - 1] * p1[r - l + 1] % mod1 + mod1) % mod1;
    }

    i64 getR(int l, int r) {
        return (uh1[l] - uh1[r + 1] * p1[r - l + 1] % mod1 + mod1) % mod1;
    }

    i64 getL2(int l, int r) {
        return (h2[r] - h2[l - 1] * p2[r - l + 1] % mod2 + mod2) % mod2;
    }

    i64 getR2(int l, int r) {
        return (uh2[l] - uh2[r + 1] * p2[r - l + 1] % mod2 + mod2) % mod2;
    }

    bool check(int l, int r, int len) {
        i64 dex = (h1[len] - getL(l, r) * p1[len - r] % mod1 + getR(l, r) * p1[len - r] % mod1 + mod1) % mod1;
        i64 dey = (uh1[1] - getR(l, r) * p1[l - 1] % mod1 + getL(l, r) * p1[l - 1] % mod1 + mod1) % mod1;

        i64 dex2 = (h2[len] - getL2(l, r) * p2[len - r] % mod2 + getR2(l, r) * p2[len - r] % mod2 + mod2) % mod2;
        i64 dey2 = (uh2[1] - getR2(l, r) * p2[l - 1] % mod2 + getL2(l, r) * p2[l - 1] % mod2 + mod2) % mod2;
        
        return dex == dey && dex2 == dey2;
    }
};