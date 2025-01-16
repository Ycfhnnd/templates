template<typename T> 
struct Fenwick {
    vector<T> tr;
    int n;
    T sum;
     
    int lowbit(int x) {
        return x & -x;
    }
     
    Fenwick(int n) : n(n), sum(0) {
        tr.resize(n + 1);
    }
     
    void add(int x, T v) {
        sum += v;
        for (; x <= n; x += lowbit(x))
            tr[x] += v;
    }
     
    T ask(int x) {
        T res = 0;
        for (; x; x -= lowbit(x))
            res += tr[x];
        return res;
    }
     
    void clear() {
        sum = 0;
        fill(tr.begin(), tr.end(), 0);
    }
};