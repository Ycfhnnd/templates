struct Manacher{
    string s;
    int len, mr, C;
    vector<int>d;
    void pre(string &_s){
        s = "#";
        for (auto k : _s){
            s += k;
            s += '#';
        }
        len = s.length();
        d.resize(len, 0);
        for (int i = 0, l = 0, r = -1; i < len; i++) {
            int k = (i > r) ? 1 : min(d[l + r - i], r - i + 1);
            while (0 <= i - k && i + k < len && s[i - k] == s[i + k]) {
                k++;
            }
            d[i] = k--;
            if (i + k > r) {
                l = i - k;
                r = i + k;
            }
        }
    }
    i64 palic(){//回文串计数
        i64 res = 0;
        for (int i = 1;i <= len - 2;i ++){
            res += (d[i] + 1 + (i & 1)) / 2;
        }
        return res;
    }
};