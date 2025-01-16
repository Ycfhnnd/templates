constexpr int P = 998244353, N = 2e6 + 10;
i64 fac[N], infac[N];
i64 qmi(i64 a,i64 b){
    i64 ans = 1;
    while (b){
        if (b & 1) ans = ans * a % P;
        a = a * a % P;
        b >>= 1;
    }
    return ans;
}
void init(){
    fac[0] = 1;
    for (int i = 1;i < N;i ++){
        fac[i] = fac[i - 1] * i % P;
    }
    infac[N - 1] = qmi(fac[N - 1], P - 2);
    for (int i = N - 2;i >= 0;i --){
        infac[i] = infac[i + 1] * (i + 1) % P;
    }
}

i64 C(int a, int b){
    if (a < 0 || b < 0 || a < b) return 0; 
    return fac[a] * infac[a - b] % P * infac[b] % P;
}
i64 A(int a,int b){
    if (a < 0 || b < 0 || a < b) return 0; 
    return fac[a] * infac[a - b] % P;
}