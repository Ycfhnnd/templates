vector<int>p, minp, isprime;
void sieve(int n){
    isprime.resize(n + 1, 0);
    minp.resize(n + 1);
    minp[1] = 1;
    for (int i = 2;i <= n;i ++){
        if (!isprime[i]){
            p.push_back(i);
        }
        for (int j = 0;j < p.size() and i * p[j] <= n;j ++){
            minp[i * p[j]] = p[j];
            isprime[i * p[j]] = 1;
            if (i % p[j] == 0){
                break;
            }
        }
    }
}