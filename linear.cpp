struct Base{
    i64 a[61] = {}, tmp[61] = {};
    bool flag;
    Base(){}
    void insert(i64 x){
        for (int i = 60;i >= 0;i --){
            if (x >> i & 1){
                if (!a[i]){
                    a[i] = x;
                    return;
                }else{
                    x ^= a[i];
                }
            }
        }
        flag = true;
    }
    bool check(i64 x){
        for (int i = 60;i >= 0;i --){
            if (x >> i & 1){
                if (!a[i]){
                    return false;
                }else{
                    x ^= a[i];
                }
            }
        }
        return true;
    }

    i64 qmax(){
        i64 ans = 0;
        for (int i = 60;i >= 0;i --){
            ans = max(ans, ans ^ a[i]);
        }
        return ans;
    }
    i64 qmin(){
        if (flag) return 0;
        for (int i = 0;i <= 60;i ++){
            if (a[i]){
                return a[i];
            }
        }
    }
    i64 query(i64 k){//查询k小值
        i64 ans = 0;
        int cnt = 0;
        k -= flag;
        if (!k) return 0;
        for (int i = 0;i <= 60;i ++){
            for (int j = i - 1;j >= 0;j --){
                if (a[i] >> j & 1){
                    a[i] ^= a[j];
                }
            }
            if (a[i]){
                tmp[cnt ++] = a[i];
            }
        }
        if (k >= (1LL << cnt)) return -1;
        for (int i = 0;i < cnt;i ++){
            if (k >> i & 1){
                ans ^= tmp[i];
            }
        }
        return ans;
    }
};