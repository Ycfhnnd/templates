i64 mul(i64 a, i64 b, i64 p) {
    i64 ans = 0;
    while (b) {
        if (b & 1) ans = (ans + a) % p;
        a = (a + a) % p;
        b >>= 1;
    }
    return ans;
}

i64 exgcd(i64 a, i64 b, i64& x, i64& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    i64 d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}

i64 excrt(vector<int>ai, vector<int>bi) {
    i64 M = bi[0], ans = ai[0];
    int n = ai.size();
    for (int i = 1; i < n; i++) {
        i64 a = M, b = bi[i], c = (ai[i] - ans % b + b) % b;
        i64 x, y;
        i64 g = exgcd(a, b, x, y);
        if (c % g != 0) return -1; 
        i64 bg = b / g;
        x = mul(x, c / g, bg);
        ans += x * M;
        M *= bg;
        ans = (ans % M + M) % M;
    }
    return (ans % M + M) % M;
}