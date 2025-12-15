// siro53.github.io/compro_library/geometry/geometry.hpp
#include "bits/stdc++.h"

namespace geometry {
// Point : 複素数型を位置ベクトルとして扱う
// 実軸(real)をx軸、挙軸(imag)をy軸として見る
using D = long double;
using Point = std::complex<D>;
const D EPS = 1e-10;
const D PI = std::acos(D(-1));

inline bool equal(const D& a, const D& b) { return std::fabs(a - b) < EPS; }

// 単位ベクトル(unit vector)を求める
Point unitVector(const Point& a) { return a / std::abs(a); }

// 法線ベクトル(normal vector)を求める
// 90度回転した単位ベクトルをかける
// -90度がよければPoint(0, -1)をかける
Point normalVector(const Point& a) { return a * Point(0, 1); }

// 内積(dot product) : a・b = |a||b|cosΘ
D dot(const Point& a, const Point& b) {
    return (a.real() * b.real() + a.imag() * b.imag());
}

// 外積(cross product) : a×b = |a||b|sinΘ
D cross(const Point& a, const Point& b) {
    return (a.real() * b.imag() - a.imag() * b.real());
}

// 点pを反時計回りにtheta度回転
// thetaはラジアン！！！
Point rotate(const Point& p, const D& theta) {
    return Point(std::cos(theta) * p.real() - std::sin(theta) * p.imag(),
                 std::sin(theta) * p.real() + std::cos(theta) * p.imag());
}

// ラジアン->度
D radianToDegree(const D& radian) { return radian * 180.0 / PI; }

// 度->ラジアン
D degreeToRadian(const D& degree) { return degree * PI / 180.0; }

// 点の回転方向
// 点a, b, cの位置関係について(aが基準点)
int ccw(const Point& a, Point b, Point c) {
    b -= a, c -= a;
    // 点a, b, c が
    // 反時計回りの時、
    if(cross(b, c) > EPS) return 1;
    // 時計回りの時、
    if(cross(b, c) < -EPS) return -1;
    // c, a, bがこの順番で同一直線上にある時、
    if(dot(b, c) < 0) return 2;
    // a, b, cがこの順番で同一直線上にある場合、
    if(std::norm(b) < std::norm(c)) return -2;
    // cが線分ab上にある場合、
    return 0;
}

// Line : 直線を表す構造体
// b - a で直線・線分を表せる
struct Line {
    Point a, b;
    Line() = default;
    Line(Point a, Point b) : a(a), b(b) {}
    // Ax+By=C
    Line(D A, D B, D C) {
        if(equal(A, 0)) {
            a = Point(0, C / B), b = Point(1, C / B);
        } else if(equal(B, 0)) {
            a = Point(C / A, 0), b = Point(C / A, 1);
        } else if(equal(C, 0)) {
            a = Point(0, C / B), b = Point(1, (C - A) / B);
        } else {
            a = Point(0, C / B), b = Point(C / A, 0);
        }
    }
};

// Segment : 線分を表す構造体
// Lineと同じ
struct Segment : Line {
    Segment() = default;

    Segment(Point a, Point b) : Line(a, b) {}
    D get_dist() { return std::abs(a - b); }
};

// Circle : 円を表す構造体
// pが中心の位置ベクトル、rは半径
struct Circle {
    Point p;
    D r;

    Circle() = default;

    Circle(Point p, D r) : p(p), r(r) {}
};

// 2直線の直交判定 : a⊥b <=> dot(a, b) = 0
bool isOrthogonal(const Line& a, const Line& b) {
    return equal(dot(a.b - a.a, b.b - b.a), 0);
}
// 2直線の平行判定 : a//b <=> cross(a, b) = 0
bool isParallel(const Line& a, const Line& b) {
    return equal(cross(a.b - a.a, b.b - b.a), 0);
}

// 点cが直線ab上にあるか
bool isPointOnLine(const Point& a, const Point& b, const Point& c) {
    return isParallel(Line(a, b), Line(a, c));
}

// 点cが"線分"ab上にあるか
bool isPointOnSegment(const Point& a, const Point& b, const Point& c) {
    // |a-c| + |c-b| <= |a-b| なら線分上
    return (std::abs(a - c) + std::abs(c - b) < std::abs(a - b) + EPS);
}

// 直線lと点pの距離を求める
D distanceBetweenLineAndPoint(const Line& l, const Point& p) {
    return std::abs(cross(l.b - l.a, p - l.a)) / std::abs(l.b - l.a);
}

// 線分lと点pの距離を求める
// 定義：点pから「線分lのどこか」への最短距離
D distanceBetweenSegmentAndPoint(const Segment& l, const Point& p) {
    if(dot(l.b - l.a, p - l.a) < EPS) return std::abs(p - l.a);
    if(dot(l.a - l.b, p - l.b) < EPS) return std::abs(p - l.b);
    return std::abs(cross(l.b - l.a, p - l.a)) / std::abs(l.b - l.a);
}

// 直線s, tの交点の計算
Point crossPoint(const Line& s, const Line& t) {
    D d1 = cross(s.b - s.a, t.b - t.a);
    D d2 = cross(s.b - s.a, s.b - t.a);
    if(equal(std::abs(d1), 0) && equal(std::abs(d2), 0)) return t.a;
    return t.a + (t.b - t.a) * (d2 / d1);
}

// 線分s, tの交点の計算
Point crossPoint(const Segment& s, const Segment& t) {
    return crossPoint(Line(s), Line(t));
}

// 線分sと線分tが交差しているかどうか
// bound:線分の端点を含むか
bool isIntersect(const Segment& s, const Segment& t, bool bound) {
    return ccw(s.a, s.b, t.a) * ccw(s.a, s.b, t.b) < bound &&
           ccw(t.a, t.b, s.a) * ccw(t.a, t.b, s.b) < bound;
}

// 線分sとtの距離
D distanceBetweenSegments(const Segment& s, const Segment& t) {
    if(isIntersect(s, t, 1)) return (D)(0);
    D ans = distanceBetweenSegmentAndPoint(s, t.a);
    ans = std::min(ans, distanceBetweenSegmentAndPoint(s, t.b));
    ans = std::min(ans, distanceBetweenSegmentAndPoint(t, s.a));
    ans = std::min(ans, distanceBetweenSegmentAndPoint(t, s.b));
    return ans;
}

// 射影(projection)
// 直線(線分)lに点pから引いた垂線の足を求める
Point projection(const Line& l, const Point& p) {
    D t = dot(p - l.a, l.a - l.b) / std::norm(l.a - l.b);
    return l.a + (l.a - l.b) * t;
}

Point projection(const Segment& l, const Point& p) {
    D t = dot(p - l.a, l.a - l.b) / std::norm(l.a - l.b);
    return l.a + (l.a - l.b) * t;
}

// 反射(reflection)
// 直線lを対称軸として点pと線対称の位置にある点を求める
Point reflection(const Line& l, const Point& p) {
    return p + (projection(l, p) - p) * (D)2.0;
}

// 2つの円の交差判定
// 返り値は共通接線の数
int isIntersect(const Circle& c1, const Circle& c2) {
    D d = std::abs(c1.p - c2.p);
    // 2つの円が離れている場合
    if(d > c1.r + c2.r + EPS) return 4;
    // 外接している場合
    if(equal(d, c1.r + c2.r)) return 3;
    // 内接している場合
    if(equal(d, std::abs(c1.r - c2.r))) return 1;
    // 内包している場合
    if(d < std::abs(c1.r - c2.r) - EPS) return 0;
    return 2;
}

// 2つの円の交点
std::vector<Point> crossPoint(const Circle& c1, const Circle& c2) {
    std::vector<Point> res;
    int mode = isIntersect(c1, c2);
    // 2つの中心の距離
    D d = std::abs(c1.p - c2.p);
    // 2円が離れている場合
    if(mode == 4) return res;
    // 1つの円がもう1つの円に内包されている場合
    if(mode == 0) return res;
    // 2円が外接する場合
    if(mode == 3) {
        D t = c1.r / (c1.r + c2.r);
        res.emplace_back(c1.p + (c2.p - c1.p) * t);
        return res;
    }
    // 内接している場合
    if(mode == 1) {
        if(c2.r < c1.r - EPS) {
            res.emplace_back(c1.p + (c2.p - c1.p) * (c1.r / d));
        } else {
            res.emplace_back(c2.p + (c1.p - c2.p) * (c2.r / d));
        }
        return res;
    }
    // 2円が重なる場合
    D rc1 = (c1.r * c1.r + d * d - c2.r * c2.r) / (2 * d);
    D rs1 = std::sqrt(c1.r * c1.r - rc1 * rc1);
    if(c1.r - std::abs(rc1) < EPS) rs1 = 0;
    Point e12 = (c2.p - c1.p) / std::abs(c2.p - c1.p);
    res.emplace_back(c1.p + rc1 * e12 + rs1 * e12 * Point(0, 1));
    res.emplace_back(c1.p + rc1 * e12 + rs1 * e12 * Point(0, -1));
    return res;
}

// 点pが円cの内部(円周上も含む)に入っているかどうか
bool isInCircle(const Circle& c, const Point& p) {
    D d = std::abs(c.p - p);
    return (equal(d, c.r) || d < c.r - EPS);
}

// 円cと直線lの交点
std::vector<Point> crossPoint(const Circle& c, const Line& l) {
    std::vector<Point> res;
    D d = distanceBetweenLineAndPoint(l, c.p);
    // 交点を持たない
    if(d > c.r + EPS) return res;
    // 接する
    Point h = projection(l, c.p);
    if(equal(d, c.r)) {
        res.emplace_back(h);
        return res;
    }
    Point e = unitVector(l.b - l.a);
    D ph = std::sqrt(c.r * c.r - d * d);
    res.emplace_back(h - e * ph);
    res.emplace_back(h + e * ph);
    return res;
}

// 点pを通る円cの接線
// 2本あるので、接点のみを返す
std::vector<Point> tangentToCircle(const Point& p, const Circle& c) {
    return crossPoint(c, Circle(p, std::sqrt(std::norm(c.p - p) - c.r * c.r)));
}

// 円の共通接線
std::vector<Line> tangent(const Circle& a, const Circle& b) {
    std::vector<Line> ret;
    // 2円の中心間の距離
    D g = std::abs(a.p - b.p);
    // 円が内包されている場合
    if(equal(g, 0)) return ret;
    Point u = unitVector(b.p - a.p);
    Point v = rotate(u, PI / 2);
    for(int s : {-1, 1}) {
        D h = (a.r + b.r * s) / g;
        if(equal(h * h, 1)) {
            ret.emplace_back(a.p + (h > 0 ? u : -u) * a.r,
                             a.p + (h > 0 ? u : -u) * a.r + v);

        } else if(1 - h * h > 0) {
            Point U = u * h, V = v * std::sqrt(1 - h * h);
            ret.emplace_back(a.p + (U + V) * a.r, b.p - (U + V) * (b.r * s));
            ret.emplace_back(a.p + (U - V) * a.r, b.p - (U - V) * (b.r * s));
        }
    }
    return ret;
}

// 多角形の面積を求める
D PolygonArea(const std::vector<Point>& p) {
    D res = 0;
    int n = p.size();
    for(int i = 0; i < n - 1; i++) res += cross(p[i], p[i + 1]);
    res += cross(p[n - 1], p[0]);
    return res * 0.5;
}

// 凸多角形かどうか
bool isConvex(const std::vector<Point>& p) {
    int n = p.size();
    int now, pre, nxt;
    for(int i = 0; i < n; i++) {
        pre = (i - 1 + n) % n;
        nxt = (i + 1) % n;
        now = i;
        if(ccw(p[pre], p[now], p[nxt]) == -1) return false;
    }
    return true;
}

// 凸包 O(NlogN)
std::vector<Point> ConvexHull(std::vector<Point> p) {
    int n = (int)p.size(), k = 0;
    std::sort(p.begin(), p.end(), [](const Point& a, const Point& b) {
        return (a.real() != b.real() ? a.real() < b.real()
                                     : a.imag() < b.imag());
    });
    std::vector<Point> ch(2 * n);
    // 一直線上の3点を含める -> (< -EPS)
    // 含め無い -> (< EPS)
    for(int i = 0; i < n; ch[k++] = p[i++]) {  // lower
        while(k >= 2 && cross(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1]) < EPS)
            --k;
    }
    for(int i = n - 2, t = k + 1; i >= 0; ch[k++] = p[i--]) {  // upper
        while(k >= t && cross(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1]) < EPS)
            --k;
    }
    ch.resize(k - 1);
    return ch;
}

// 多角形gに点pが含まれているか?
// 含まれる:2, 辺上にある:1, 含まれない:0
int isContained(const std::vector<Point>& g, const Point& p) {
    bool in = false;
    int n = (int)g.size();
    for(int i = 0; i < n; i++) {
        Point a = g[i] - p, b = g[(i + 1) % n] - p;
        if(imag(a) > imag(b)) swap(a, b);
        if(imag(a) <= EPS && EPS < imag(b) && cross(a, b) < -EPS) in = !in;
        if(cross(a, b) == 0 && dot(a, b) <= 0) return 1;
    }
    return (in ? 2 : 0);
}

// 凸多角形pを直線lで切断し、その左側を返す
std::vector<Point> ConvexCut(std::vector<Point> p, Line l) {
    std::vector<Point> ret;
    int sz = (int)p.size();
    for(int i = 0; i < sz; i++) {
        Point now = p[i];
        Point nxt = p[i == sz - 1 ? 0 : i + 1];
        if(ccw(l.a, l.b, now) != -1) ret.emplace_back(now);
        if(ccw(l.a, l.b, now) * ccw(l.a, l.b, nxt) < 0) {
            ret.emplace_back(crossPoint(Line(now, nxt), l));
        }
    }
    return ret;
}

}  // namespace geometry