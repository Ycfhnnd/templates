const int N = 5e6 + 2;
bool np[N];
int prime[N], pi[N];
 
int getprime() {
    int cnt = 0;
    np[0] = np[1] = true;
    pi[0] = pi[1] = 0;
    for(int i = 2; i < N; ++i) {
        if(!np[i]) prime[++cnt] = i;
        pi[i] = cnt;
        for(int j = 1; j <= cnt && i * prime[j] < N; ++j) {
            np[i * prime[j]] = true;
            if(i % prime[j] == 0)   break;
        }
    }
    return cnt;
}
const int M = 7;
const int PM = 2 * 3 * 5 * 7 * 11 * 13 * 17;
int phi[PM + 1][M + 1], sz[M + 1];
void init() {
    getprime();
    sz[0] = 1;
    for(int i = 0; i <= PM; ++i)  phi[i][0] = i;
    for(int i = 1; i <= M; ++i) {
        sz[i] = prime[i] * sz[i - 1];
        for(int j = 1; j <= PM; ++j) {
            phi[j][i] = phi[j][i - 1] - phi[j / prime[i]][i - 1];
        }
    }
}
int sqrt2(i64 x) {
    i64 r = (i64)sqrt(x - 0.1);
    while(r * r <= x)   ++r;
    return int(r - 1);
}
int sqrt3(i64 x) {
    i64 r = (i64)cbrt(x - 0.1);
    while(r * r * r <= x)   ++r;
    return int(r - 1);
}
i64 getphi(i64 x, int s) {
    if(s == 0)  return x;
    if(s <= M)  return phi[x % sz[s]][s] + (x / sz[s]) * phi[sz[s]][s];
    if(x <= prime[s]*prime[s])   return pi[x] - s + 1;
    if(x <= prime[s]*prime[s]*prime[s] && x < N) {
        int s2x = pi[sqrt2(x)];
        i64 ans = pi[x] - (s2x + s - 2) * (s2x - s + 1) / 2;
        for(int i = s + 1; i <= s2x; ++i) {
            ans += pi[x / prime[i]];
        }
        return ans;
    }
    return getphi(x, s - 1) - getphi(x / prime[s], s - 1);
}
i64 getpi(i64 x) {
    if(x < N)   return pi[x];
    i64 ans = getphi(x, pi[sqrt3(x)]) + pi[sqrt3(x)] - 1;
    for(int i = pi[sqrt3(x)] + 1, ed = pi[sqrt2(x)]; i <= ed; ++i) {
        ans -= getpi(x / prime[i]) - i + 1;
    }
    return ans;
}
i64 lehmer_pi(i64 x) {
    if(x < N)   return pi[x];
    int a = (int)lehmer_pi(sqrt2(sqrt2(x)));
    int b = (int)lehmer_pi(sqrt2(x));
    int c = (int)lehmer_pi(sqrt3(x));
    i64 sum = getphi(x, a) + i64(b + a - 2) * (b - a + 1) / 2;
    for (int i = a + 1; i <= b; i++) {
        i64 w = x / prime[i];
        sum -= lehmer_pi(w);
        if (i > c) continue;
        i64 lim = lehmer_pi(sqrt2(w));
        for (int j = i; j <= lim; j++) {
            sum -= lehmer_pi(w / prime[j]) - (j - 1);
        }
    }
    return sum;
}