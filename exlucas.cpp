constexpr i64 power(i64 a, i64 b, i64 p) {
    i64 res = 1;
    for (; b; b /= 2, a = 1LL * a * a % p) {
        if (b % 2) {
            res = 1LL * res * a % p;
        }
    }
    return res;
}

constexpr i64 fac(const i64 n, const i64 p, const i64 pk){
    if (!n){
        return 1;
    }
    i64 ans = 1;
    for (int i = 1; i < pk; i ++){
        if (i % p){
            ans = ans * i % pk;
        }
    }
    ans = power(ans, n / pk, pk);
    for (int i = 1; i <= n % pk; i ++){
        if (i % p){
            ans = ans * i % pk;
        }
    }
    return ans * fac(n / p, p, pk) % pk;
}

constexpr i64 exgcd(i64 a, i64 b, i64 &x, i64 &y){
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    i64 g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}
constexpr i64 inv(const i64 a, const i64 p){
    i64 x, y;
    exgcd(a, p, x, y);
    return (x % p + p) % p;
}

constexpr i64 Comb(const i64 n, const i64 m, const i64 p, const i64 pk){
    if (n < m){
        return 0;
    }

    i64 f1 = fac(n, p, pk), f2 = fac(m, p, pk), f3 = fac(n - m, p, pk), cnt = 0;

    for (i64 i = n; i; i /= p){   
        cnt += i / p;
    }

    for (i64 i = m; i; i /= p){
        cnt -= i / p;
    }   

    for (i64 i = n - m; i; i /= p){
        cnt -= i / p;
    }

    return f1 * inv(f2, pk) % pk * inv(f3, pk) % pk * power(p, cnt, pk) % pk;
}

constexpr int N = 1E6 + 10;
i64 a[N], c[N];
int cnt;
constexpr i64 CRT(){
    i64 M = 1, ans = 0;
    for (int i = 0; i < cnt; i ++){
        M *= c[i];
    }

    for (int i = 0; i < cnt; i ++){
        ans = (ans + a[i] * (M / c[i]) % M * inv(M / c[i], c[i]) % M) % M;
    }
    return ans;
}

i64 exLucas(const i64 n, const i64 m, i64 p){
    i64 tmp = sqrt(p);
    for (int i = 2; p > 1 and i <= tmp; i ++){
        i64 tmp = 1;
        while (p % i == 0){
            p /= i, tmp *= i;
        }
        if (tmp > 1){
            a[cnt] = Comb(n, m, i, tmp), c[cnt++] = tmp;
        }
    }
    if (p > 1){
        a[cnt] = Comb(n, m, p, p), c[cnt ++] = p;
    }

    return CRT();
}