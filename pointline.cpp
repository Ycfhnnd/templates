using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128;
using f128 = __float128;template<class T>

struct Point {
    T x;
    T y;
    Point(const T &x_ = 0, const T &y_ = 0) : x(x_), y(y_) {}

    template<class U>
    operator Point<U>() {
        return Point<U>(U(x), U(y));
    }
    Point &operator+=(const Point &p) & {
        x += p.x;
        y += p.y;
        return *this;
    }
    Point &operator-=(const Point &p) & {
        x -= p.x;
        y -= p.y;
        return *this;
    }
    Point &operator*=(const T &v) & {
        x *= v;
        y *= v;
        return *this;
    }
    Point &operator/=(const T &v) & {
        x /= v;
        y /= v;
        return *this;
    }
    Point operator-() const {
        return Point(-x, -y);
    }
    constexpr friend Point operator+(Point a, const Point &b) {
        return a += b;
    }
    constexpr friend Point operator-(Point a, const Point &b) {
        return a -= b;
    }
    constexpr friend Point operator*(Point a, const T &b) {
        return a *= b;
    }
    constexpr friend Point operator/(Point a, const T &b) {
        return a /= b;
    }
    constexpr friend Point operator*(const T &a, Point b) {
        return b *= a;
    }
    constexpr friend bool operator==(const Point &a, const Point &b) {
        return a.x == b.x && a.y == b.y;
    }
    friend std::istream &operator>>(std::istream &is, Point &p) {
        return is >> p.x >> p.y;
    }
    friend std::ostream &operator<<(std::ostream &os, const Point &p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};

template<class T>
struct Line {
    Point<T> a;
    Point<T> b;
    Line(const Point<T> &a_ = Point<T>(), const Point<T> &b_ = Point<T>()) : a(a_), b(b_) {}
};

template<class T>
T dot(const Point<T> &a, const Point<T> &b) {
    return a.x * b.x + a.y * b.y;
}

template<class T>
T cross(const Point<T> &a, const Point<T> &b) {
    return a.x * b.y - a.y * b.x;
}

template<class T>
T square(const Point<T> &p) {
    return dot(p, p);
}

template<class T>
f64 length(const Point<T> &p) {
    return sqrtl(square(p));
}

template<class T>
f64 length(const Line<T> &l) {
    return length(l.a - l.b);
}

template<class T>
Point<T> normalize(const Point<T> &p) {
    return p / length(p);
}

template<class T>
bool parallel(const Line<T> &l1, const Line<T> &l2) {
    return cross(l1.b - l1.a, l2.b - l2.a) == 0;
}

template<class T>
f64 distance(const Point<T> &a, const Point<T> &b) {
    return length(a - b);
}

template<class T>
f64 distancePL(const Point<T> &p, const Line<T> &l) {
    return std::abs(cross(l.a - l.b, l.a - p)) / length(l);
}

template<class T>
f64 distancePS(const Point<T> &p, const Line<T> &l) {
    if (dot(p - l.a, l.b - l.a) < 0) {
        return distance(p, l.a);
    }
    if (dot(p - l.b, l.a - l.b) < 0) {
        return distance(p, l.b);
    }
    return distancePL(p, l);
}

template<class T>
Point<T> rotate(const Point<T> &a) {
    return Point(-a.y, a.x);
}

template<class T>
int sgn(const Point<T> &a) {
    return a.y > 0 or (a.y == 0 and a.x > 0) ? 1 : -1;
}

template<class T>
f64 angle(const Point<T>& p) {
    return std::atan2(p.y, p.x);
}

template<class T>
f64 angle(const Line<T>& l) {
    return angle(l.b - l.a);
}

template<class T>
bool pointOnLineLeft(const Point<T> &p, const Line<T> &l) {
    return cross(l.b - l.a, p - l.a) > 0;
}

template<class T>
Point<T> lineIntersection(const Line<T> &l1, const Line<T> &l2) {
    return l1.a + (l1.b - l1.a) * (cross(l2.b - l2.a, l1.a - l2.a) / cross(l2.b - l2.a, l1.a - l1.b));
}

template<class T>
bool pointOnSegment(const Point<T> &p, const Line<T> &l) {
    return cross(p - l.a, l.b - l.a) == 0 and std::min(l.a.x, l.b.x) <= p.x and p.x <= std::max(l.a.x, l.b.x) and std::min(l.a.y, l.b.y) <= p.y and p.y <= std::max(l.a.y, l.b.y);
}

template<class T>
bool pointOnLine(const Point<T> &p, const Line<T> &l) {
    return pointOnSegment(p, l) or pointOnSegment(l.a, Line(p, l.b)) or pointOnSegment(l.b, Line(p, l.a));
}

template<class T>
bool pointInPolygon(const Point<T> &a, const std::vector<Point<T>> &p) {
    int n = p.size();
    for (int i = 0; i < n; i++) {
        if (pointOnSegment(a, Line(p[i], p[(i + 1) % n]))) {
            return true;
        }
    }
    int t = 0;
    for (int i = 0; i < n; i++) {
        const auto &u = p[i];
        const auto &v = p[(i + 1) % n];
        if (u.x < a.x and v.x >= a.x and pointOnLineLeft(a, Line(v, u))) {
            t ^= 1;
        }
        if (u.x >= a.x and v.x < a.x and pointOnLineLeft(a, Line(u, v))) {
            t ^= 1;
        }
    }
    return t == 1;
}

//0: 两条线段不相交。
//1: 两条线段严格相交（交于一点，但不在端点）。
//2: 两条线段重叠;
//3: 两条线段在一个端点相交。
template<class T>
std::tuple<int, Point<T>, Point<T>> segmentIntersection(const Line<T> &l1, const Line<T> &l2) {
    if (std::max(l1.a.x, l1.b.x) < std::min(l2.a.x, l2.b.x)) {
        return {0, Point<T>(), Point<T>()};
    }
    if (std::min(l1.a.x, l1.b.x) > std::max(l2.a.x, l2.b.x)) {
        return {0, Point<T>(), Point<T>()};
    }
    if (std::max(l1.a.y, l1.b.y) < std::min(l2.a.y, l2.b.y)) {
        return {0, Point<T>(), Point<T>()};
    }
    if (std::min(l1.a.y, l1.b.y) > std::max(l2.a.y, l2.b.y)) {
        return {0, Point<T>(), Point<T>()};
    }
    if (cross(l1.b - l1.a, l2.b - l2.a) == 0) {
        if (cross(l1.b - l1.a, l2.a - l1.a) != 0) {
            return {0, Point<T>(), Point<T>()};
        } else {
            const auto &maxx1 = std::max(l1.a.x, l1.b.x);
            const auto &minx1 = std::min(l1.a.x, l1.b.x);
            const auto &maxy1 = std::max(l1.a.y, l1.b.y);
            const auto &miny1 = std::min(l1.a.y, l1.b.y);
            const auto &maxx2 = std::max(l2.a.x, l2.b.x);
            const auto &minx2 = std::min(l2.a.x, l2.b.x);
            const auto &maxy2 = std::max(l2.a.y, l2.b.y);
            const auto &miny2 = std::min(l2.a.y, l2.b.y);
            Point<T> p1(std::max(minx1, minx2), std::max(miny1, miny2));
            Point<T> p2(std::min(maxx1, maxx2), std::min(maxy1, maxy2));
            if (!pointOnSegment(p1, l1)) {
                std::swap(p1.y, p2.y);
            }
            if (p1 == p2) {
                return {3, p1, p2};
            } else {
                return {2, p1, p2};
            }
        }
    }
    const auto &cp1 = cross(l2.a - l1.a, l2.b - l1.a);
    const auto &cp2 = cross(l2.a - l1.b, l2.b - l1.b);
    const auto &cp3 = cross(l1.a - l2.a, l1.b - l2.a);
    const auto &cp4 = cross(l1.a - l2.b, l1.b - l2.b);
    if ((cp1 > 0 and cp2 > 0) or (cp1 < 0 and cp2 < 0) or (cp3 > 0 and cp4 > 0) or (cp3 < 0 and cp4 < 0)) {
        return {0, Point<T>(), Point<T>()};
    }
    Point p = lineIntersection(l1, l2);
    if (cp1 != 0 and cp2 != 0 and cp3 != 0 and cp4 != 0) {
        return {1, p, p};
    } else {
        return {3, p, p};
    }
}

template<class T>
f64 distanceSS(const Line<T> &l1, const Line<T> &l2) {
    if (std::get<0>(segmentIntersection(l1, l2)) != 0) {
        return 0.0;
    }
    return std::min({distancePS(l1.a, l2), distancePS(l1.b, l2), distancePS(l2.a, l1), distancePS(l2.b, l1)});
}

template<class T>
bool segmentInPolygon(const Line<T> &l, const std::vector<Point<T>> &p) {
    int n = p.size();
    if (!pointInPolygon(l.a, p)) {
        return false;
    }
    if (!pointInPolygon(l.b, p)) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        const auto &u = p[i];
        const auto &v = p[(i + 1) % n];
        const auto &w = p[(i + 2) % n];
        const auto &[t, p1, p2] = segmentIntersection(l, Line(u, v));

        if (t == 1) {
            return false;
        }
        if (t == 0) {
            continue;
        }
        if (t == 2) {
            if (pointOnSegment(v, l) and v != l.a and v != l.b) {
                if (cross(v - u, w - v) > 0) {
                    return false;
                }
            }
        } else {
            if (p1 != u and p1 != v) {
                if (pointOnLineLeft(l.a, Line(v, u)) or pointOnLineLeft(l.b, Line(v, u))) {
                    return false;
                }
            } else if (p1 == v) {
                if (l.a == v) {
                    if (pointOnLineLeft(u, l)) {
                        if (pointOnLineLeft(w, l) and pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    } else {
                        if (pointOnLineLeft(w, l) or pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    }
                } else if (l.b == v) {
                    if (pointOnLineLeft(u, Line(l.b, l.a))) {
                        if (pointOnLineLeft(w, Line(l.b, l.a)) and pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    } else {
                        if (pointOnLineLeft(w, Line(l.b, l.a)) or pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    }
                } else {
                    if (pointOnLineLeft(u, l)) {
                        if (pointOnLineLeft(w, Line(l.b, l.a)) or pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    } else {
                        if (pointOnLineLeft(w, l) or pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

template<class T>
std::vector<Point<T>> hp(std::vector<Line<T>> lines) {
    std::sort(lines.begin(), lines.end(), [&](const auto & l1, const auto & l2) {
        const auto &d1 = l1.b - l1.a;
        const auto &d2 = l2.b - l2.a;
        if (sgn(d1) != sgn(d2)) {
            return sgn(d1) == 1;
        }
        return cross(d1, d2) > 0;
    });
    std::deque<Line<T>> ls;
    std::deque<Point<T>> ps;
    for (const auto &l : lines) {
        if (ls.empty()) {
            ls.push_back(l);
            continue;
        }
        while (!ps.empty() and !pointOnLineLeft(ps.back(), l)) {
            ps.pop_back();
            ls.pop_back();
        }
        while (!ps.empty() and !pointOnLineLeft(ps[0], l)) {
            ps.pop_front();
            ls.pop_front();
        }
        if (cross(l.b - l.a, ls.back().b - ls.back().a) == 0) {
            if (dot(l.b - l.a, ls.back().b - ls.back().a) > 0) {

                if (!pointOnLineLeft(ls.back().a, l)) {
                    assert(ls.size() == 1);
                    ls[0] = l;
                }
                continue;
            }
            return {};
        }
        ps.push_back(lineIntersection(ls.back(), l));
        ls.push_back(l);
    }
    while (!ps.empty() and !pointOnLineLeft(ps.back(), ls[0])) {
        ps.pop_back();
        ls.pop_back();
    }
    if (ls.size() <= 2) {
        return {};
    }
    ps.push_back(lineIntersection(ls[0], ls.back()));
    return std::vector(ps.begin(), ps.end());
}

template<class T>
T PolygonArea(const std::vector<Point<T>> &p) {
    T res = T(0);
    int n = p.size();
    for (int i = 0; i < n; i += 1) {
        res += cross(p[i], p[(i + 1) % n]);
    }
    return std::abs(res) * 0.5;
}

template<class T>
std::vector<Point<T>> getHull(std::vector<Point<T>> p) {
    std::vector<Point<T>>h, l;
    std::sort(p.begin(), p.end(), [&](const auto & a, const auto & b) {
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    });
    p.erase(std::unique(p.begin(), p.end()), p.end());
    if (p.size() <= 1) {
        return p;
    }
    for (const auto & a : p) {
        while ((int)h.size() > 1 and cross(a - h.back(), a - h[(int)h.size() - 2]) <= 0) {
            h.pop_back();
        }
        while ((int)l.size() > 1 and cross(a - l.back(), a - l[(int)l.size() - 2]) >= 0) {
            l.pop_back();
        }
        l.push_back(a);
        h.push_back(a);
    }
    l.pop_back();
    std::reverse(h.begin(), h.end());
    h.pop_back();
    l.insert(l.end(), h.begin(), h.end());
    return l;
}

template<class T>
std::tuple<T, Point<T>, Point<T>> getLongest(const std::vector<Point<T>>& ret) {
    std::vector<Point<T>> p = getHull(ret);
    int n = p.size();

    T res = T(0);
    Point<T> a = Point<T>(), b = Point<T>();
    int x = 0, y = 0;
    for (int i = 0; i < n; i += 1) {
        if (p[i].y < p[x].y)x = i;
        if (p[i].y > p[y].y)y = i;
    }
    res = square(p[x] - p[y]);
    a = p[x], b = p[y];
    int i = x, j = y;
    do {
        if (cross(p[(i + 1) % n] - p[i], p[(j + 1) % n] - p[j]) < 0) {
            i = (i + 1) % n;
        } else {
            j = (j + 1) % n;
        }
        if (square(p[i] - p[j]) > res) {
            res = square(p[i] - p[j]);
            a = p[i], b = p[j];
        }
    } while (i != x or j != y);
    return {res, a, b};
}

template<class T>
std::tuple<T, Point<T>, Point<T>> getClostest(std::vector<Point<T>> p) {
    std::sort(p.begin(), p.end(), [&](const auto & a, const auto & b) {
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    });
    T res = std::numeric_limits<T>::max();
    Point<T> a = Point<T>(), b = Point<T>();
    int n = p.size();

    auto update = [&](const Point<T>& u, const Point<T>& v) {
        if (res > square(u - v)) {
            res = square(u - v);
            a = u;
            b = v;
        }
    };

    auto s = std::multiset < Point<T>, decltype([](const Point<T>& u, const Point<T>& v) {
        return u.y == v.y ? u.x < v.x : u.y < v.y;
    }) > ();
    std::vector<typename decltype(s)::const_iterator>its(n);
    for (int i = 0, f = 0; i < n; i += 1) {
        while (f < i and (p[i] - p[f]).x * (p[i] - p[f]).x >= res) {
            s.erase(its[f++]);
        }
        auto u = s.upper_bound(p[i]); {
            auto t = u;
            while (true) {
                if (t == s.begin()) {
                    break;
                }
                t = std::prev(t);
                update(*t, p[i]);
                if ((p[i] - *t).y * (p[i] - *t).y >= res) {
                    break;
                }
            }
        }{
            auto t = u;
            while (true) {
                if (t == s.end()) {
                    break;
                }
                if ((p[i] - *t).y * (p[i] - *t).y >= res) {
                    break;
                }
                update(*t, p[i]);
                t = std::next(t);
            }
        }
        its[i] = s.emplace_hint(u, p[i]);
    }

    return {res, a, b};
}

template<class T>
std::pair<T, std::vector<Point<T>>> rectCoverage(const std::vector<Point<T>>& p) {
    T res = std::numeric_limits<T>::max();
    std::vector<Point<T>>rect;
    std::array<int, 4>pos {};
    int n = p.size();
    if (n < 3) {
        return std::pair(res, rect);
    }
    for (int i = 0, r = 1, j = 1, q = 0; i < n; i += 1) {
        while (cross(p[(i + 1) % n] - p[i], p[(r + 1) % n] - p[i]) >= cross(p[(i + 1) % n] - p[i], p[r] - p[i])) {
            r = (r + 1) % n;
        }
        while (dot(p[(i + 1) % n] - p[i], p[(j + 1) % n] - p[i]) >= dot(p[(i + 1) % n] - p[i], p[j] - p[i])) {
            j = (j + 1) % n;
        }
        if (i == 0) {
            q = j;
        }
        while (dot(p[(i + 1) % n] - p[i], p[(q + 1) % n] - p[i]) <= dot(p[(i + 1) % n] - p[i], p[q] - p[i])) {
            q = (q + 1) % n;
        }
        T d = square(p[i] - p[(i + 1) % n]);
        T area = cross(p[(i + 1) % n] - p[i], p[r] - p[i]) * (dot(p[(i + 1) % n] - p[i], p[j] - p[i]) - dot(p[(i + 1) % n] - p[i], p[q] - p[i])) / d;
        if (area < res) {
            res = area;
            pos[0] = r;
            pos[1] = j;
            pos[2] = q;
            pos[3] = i;
        }
    }
    const auto& [r, j, q, i] = pos;
    Line<T> l1 = Line(p[i], p[(i + 1) % n]);
    Point t = p[(i + 1) % n] - p[i];
    Line<T> l2 = Line(p[r], p[r] + t);
    t = rotate(t);
    Line<T> l3 = Line(p[j], p[j] + t);
    Line<T> l4 = Line(p[q], p[q] + t);

    rect.push_back(lineIntersection(l1, l3));
    rect.push_back(lineIntersection(l1, l4));
    rect.push_back(lineIntersection(l2, l3));
    rect.push_back(lineIntersection(l2, l4));

    rect = getHull(rect);
    return std::pair(res, rect);
}

template<class T>
Point<T> triangleHeart(const Point<T>& A, const Point<T>& B, const Point<T>& C) {
    return (A * square(B - C) + B * square(C - A) + C * square(A - B)) / (square(B - C) + square(C - A) + square(A - B));
}

template<class T>
Point<T> circumcenter(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
    T D = 2 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
    assert(D != 0);
    Point<T> p;
    p.x = ((square(a) * (b.y - c.y) + (square(b) * (c.y - a.y)) + (square(c) * (a.y - b.y)))) / D;
    p.y = ((square(a) * (c.x - b.x) + (square(b) * (a.x - c.x)) + (square(c) * (b.x - a.x)))) / D;
    return p;
}

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

template<class T>
std::pair<Point<T>, T> cirlCoverage(std::vector<Point<T>> p) {
    for (int t = 0; t < 7; t += 1) {
        std::shuffle(p.begin(), p.end(), rng);
    }
    int n = p.size();
    Point<T> o = p[0];
    T r = T(0);
    for (int i = 1; i < n; i += 1) {
        if (length(o - p[i]) > r) {
            o = p[i];
            r = T(0);
            for (int j = 0; j < i; j += 1) {
                if (length(o - p[j]) > r) {
                    o = (p[i] + p[j]) / T(2);
                    r = length(o - p[i]);
                    for (int k = 0; k < j; k += 1) {
                        if (length(o - p[k]) > r) {
                            o = circumcenter(p[i], p[j], p[k]);
                            r = length(o - p[i]);
                        }
                    }
                }
            }
        }
    }
    return std::pair(o, r);
}

template<class F>
f64 asr(f64 l, f64 r, const F& pred) {
    static constexpr f64 eps = 1e-9;
    auto simpson = [&](f64 l, f64 r) {
        f64 mid = (l + r) / 2;
        return (pred(l) + 4 * pred(mid) + pred(r)) * (r - l) / 6;
    };
    auto cal = [&](auto && self, f64 l, f64 r, f64 res) {
        f64 mid = (l + r) / 2;
        f64 lo = simpson(l, mid), hi = simpson(mid, r);
        if (std::abs(lo + hi - res) < eps) {
            return lo + hi;
        }
        return self(self, l, mid, lo) + self(self, mid, r, hi);
    };
    return cal(cal, l, r, simpson(l, r));
}

using P = Point<i64>;
using L = Line<i64>;