
namespace FFT{
    const long double PI = acosl(-1.L);
    struct C{
        double x, y;
        C(double x = 0, double y = 0) : x(x), y(y) {}
        C operator!() const { return C(x, -y); }
    };
    C operator*(C a, C b) { return C(a.x * b.x - a.y * b.y, a.y * b.x + b.y * a.x); }
    C operator+(C a, C b) { return C(a.x + b.x, a.y + b.y); }
    C operator-(C a, C b) { return C(a.x - b.x, a.y - b.y); }
    constexpr int L(1 << 21);

    C w[L];
    void dft(C *a, int n){
        for (static int k = (w[1].x = 1, 2); k < n; k <<= 1){
            for (int i = 0; i < k; i++){
                w[i + k] = i & 1 ? C(cosl(PI * i / k), sinl(PI * i / k)) : w[i + k >> 1];
            }
        }
        for (int k = n >> 1; k; k >>= 1){
            for (int i = 0; i < n; i += k << 1){
                for (int j = 0; j < k; j++){
                    C &x = a[i + j], y = a[i + j + k];
                    a[i + j + k] = (x - y) * w[k + j], x = x + y;
                }
            }
        }
    }
    void idft(C *a, int n){
        for (int k = 1; k < n; k <<= 1){
            for (int i = 0; i < n; i += k << 1){
                for (int j = 0; j < k; j++){
                    C &x = a[i + j], y = a[i + j + k] * w[k + j];
                    a[i + j + k] = x - y, x = x + y;
                }
            }
        }
        for (int i = 0; i < n; i++)
            a[i].x /= n, a[i].y /= n;
        reverse(a + 1, a + n);
    }
}

using Poly = vector<i64>;
vector<i64> conv(const Poly &a, const Poly &b){
    using namespace FFT;
    int len = a.size() + b.size() - 1;
    int n = 1 << __lg(len * 2 - 1);
    vector<C> f(n);
    for (int i = 0; i < n; i++){
        f[i] = C(i < a.size() ? a[i] : 0,
                 i < b.size() ? b[i] : 0);
    }
    dft(f.data(), n);
    for (int i = 0; i < n; i++)
        f[i] = f[i] * f[i];
    idft(f.data(), n);
    vector<i64> r(len);
    for (int i = 0; i < len; i++){
        r[i] = f[i].y / 2 + 0.5;
    }
    return r;
}