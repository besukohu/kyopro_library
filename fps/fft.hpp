#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// {998244353, 3}, {1811939329, 13}, {2013265921, 31}
const ll mod = 998244353;
struct mm {
    ll x;
    mm(ll x_ = 0) : x(x_ % mod) {
        if(x < 0)
            x += mod;
    }
    friend mm operator+(mm a, mm b) { return a.x + b.x; }
    friend mm operator-(mm a, mm b) { return a.x - b.x; }
    friend mm operator*(mm a, mm b) { return a.x * b.x; }
    friend mm operator/(mm a, mm b) { return a * b.inv(); }
    // 4 行コピペ  Alt + Shift + クリックで複数カーソル
    friend mm &operator+=(mm &a, mm b) { return a = a.x + b.x; }
    friend mm &operator-=(mm &a, mm b) { return a = a.x - b.x; }
    friend mm &operator*=(mm &a, mm b) { return a = a.x * b.x; }
    friend mm &operator/=(mm &a, mm b) { return a = a * b.inv(); }
    mm inv() const { return pow(mod - 2); }
    mm pow(ll b) const {
        mm a = *this, c = 1;
        while(b) {
            if(b & 1)
                c *= a;
            a *= a;
            b >>= 1;
        }
        return c;
    }
};
mm g = 3; // 原始根
void fft(vector<mm> &a) {
    ll n = a.size(), lg = __lg(n);
    assert((1 << lg) == n);
    vector<mm> b(n);
    for(int l = 1; l < lg + 1; l++) {
        ll w = n >> l;
        mm s = 1, r = g.pow(mod >> l);
        for(ll u = 0; u < n / 2; u += w) {
            for(int d = 0; d < w; d++) {
                mm x = a[u << 1 | d], y = a[u << 1 | w | d] * s;
                b[u | d] = x + y;
                b[n >> 1 | u | d] = x - y;
            }
            s *= r;
        }
        swap(a, b);
    }
}
vector<mm> conv(vector<mm> a, vector<mm> b) {
    if(a.empty() || b.empty())
        return {};
    size_t s = a.size() + b.size() - 1, n = bit_ceil(s);
    // if(min(sz(a), sz(b)) <= 60) 愚直に掛け算
    a.resize(n);
    b.resize(n);
    fft(a);
    fft(b);
    mm inv = mm(n).inv();
    for(int i = 0; i < n; i++)
        a[i] *= b[i] * inv;
    reverse(a.begin() + 1, a.end());
    fft(a);
    a.resize(s);
    return a;
}