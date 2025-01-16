struct BSGS{
    i64 a, b, p;
    map<i64, i64>f;

    BSGS(){
    }

    i64 qmi(i64 a,i64 b, i64 p){
        i64 res = 1;
        while (b){
            if (b & 1) res = res * a % p;
            b >>= 1;
            a = a * a % p;
        }
        return res;
    }

    void exgcd(i64 a,i64 b, i64 &x, i64 &y){
        if (!b){
            x = 1, y = 0;
        }else{
            exgcd(b, a % b, x, y);
            i64 t = x;
            x = y;
            y = t - a / b * y;
        }
    }

    i64 inv(i64 a, i64 b){
        i64 x, y;
        exgcd(a, b, x, y);
        return (x % b + b) % b;
    }

    i64 bsgs(i64 a, i64 b, i64 p){
        f.clear();
        i64 m = ceil(sqrt(p));
        b %= p;
        for (int i = 1;i <= m;i ++){
            b = b * a % p;
            f[b] = i;
        }

        i64 tmp = qmi(a, m, p);
        b = 1;

        for (int i = 1;i <= m;i ++){
            b = b * tmp % p;
            if (f.count(b) > 0){
                return (i * m - f[b] + p) % p;
            }
        }
        return -1;
    }

    i64 exbsgs(i64 a, i64 b, i64 p){
        if (b == 1 || p == 1) return 0;
        i64 g = gcd(a, p), k = 0, na = 1;
        while (g > 1){
            if (b % g != 0) return -1;
            k ++;
            b /= g;
            p /= g;
            na = na * (a / g) % p;
            if (na == b) return k;
            g = gcd(a, p);
        }
        i64 f = bsgs(a, b * inv(na, p) % p, p);
        if (f == -1) return -1;
        return f + k;
    }
};