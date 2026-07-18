#pragma once
#include <bits/stdc++.h>

#include <cassert>

using namespace std;
using ll = long long;
using ld = long double;

using i2 = array<ll, 2>;
using i3 = array<ll, 3>;
using i4 = array<ll, 4>;

using f2 = array<ld, 2>;
using f3 = array<ld, 3>;
using f4 = array<ld, 4>;

template <class T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;

template <class T>
using max_pq = priority_queue<T, vector<T>, less<T>>;

const ll INF = (1LL << 61);

bool chmin(auto& a, const auto& b) { return a > b ? a = b, 1 : 0; }
bool chmax(auto& a, const auto& b) { return a < b ? a = b, 1 : 0; }

ll floor_div(ll a, ll b) { return a / b - (a % b != 0 && (a ^ b) < 0); }
ll ceil_div(ll a, ll b) { return a / b + (a % b != 0 && (a ^ b) > 0); }
ll floor_mod(ll a, ll b) { return a % b + (a % b != 0 && (a ^ b) < 0) * b; }

mt19937 mt(time(0));
class xor_shift_128 {
   public:
    typedef uint32_t result_type;
    xor_shift_128(result_type seed = mt()) {
        set_seed(seed);
    }
    void set_seed(result_type seed) {
        a = seed = 1812433253 * (seed ^ (seed >> 30));
        b = seed = 1812433253 * (seed ^ (seed >> 30)) + 1;
        c = seed = 1812433253 * (seed ^ (seed >> 30)) + 2;
        d = seed = 1812433253 * (seed ^ (seed >> 30)) + 3;
    }
    result_type gen() {
        result_type t = (a ^ (a << 11));
        a = b;
        b = c;
        c = d;
        return d = (d ^ (d >> 19)) ^ (t ^ (t >> 8));
    }
    result_type operator()() {
        return gen();
    }
    ll gen_range(ll min_inclusive, ll max_exclusive) {
        ll diff = max_exclusive - min_inclusive;
        assert(diff);
        return min_inclusive + gen() % diff;
    }

    static constexpr result_type max() { return numeric_limits<result_type>::max(); }
    static constexpr result_type min() { return numeric_limits<result_type>::min(); }

   private:
    result_type a, b, c, d;
};
xor_shift_128 xorrand;

template <class T, size_t N>
istream& operator>>(istream& is, array<T, N>& a) {
    for (auto& x : a) is >> x;
    return is;
}
template <class T, size_t N>
ostream& operator<<(ostream& os, const array<T, N>& a) {
    for (size_t i = 0; i < N; i++)
        os << (i ? " " : "") << a[i];
    return os;
}

template <class T>
istream& operator>>(istream& is, vector<T>& v) {
    for (auto& x : v) is >> x;
    return is;
}
template <class T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    for (int i = 0; i < (int)v.size(); i++)
        os << (i ? " " : "") << v[i];
    return os;
}
template <class T>
ostream& operator<<(ostream& os, const vector<vector<T>>& vv) {
    for (int i = 0; i < (int)vv.size(); i++)
        os << (i ? "\n" : "") << vv[i];
    return os;
}

#define dbg(...) cerr << #__VA_ARGS__ << " = ", debug_print(__VA_ARGS__);
void debug_print() { cerr << endl; }
template <class T, class... Args>
void debug_print(const T& x, const Args&... args) {
    cerr << x;
    if constexpr (sizeof...(args) > 0) cerr << ", ";
    debug_print(args...);
}

struct sep {
    const char* s;
    sep(const char* s) : s(s) {}
};

template <class... Args>
void print(sep sp, const Args&... args) {
    int i = 0;
    ((cout << (i++ ? sp.s : "") << args), ...);
    cout << "\n";
}

template <class... Args>
void print(const Args&... args) {
    print(sep{" "}, args...);
}

template <class T>
void print(const vector<T>& v) {
    for (int i = 0; i < (int)v.size(); i++)
        cout << (i ? " " : "") << v[i];
    cout << "\n";
}

template <class T>
void print(sep sp, const vector<T>& v) {
    for (int i = 0; i < (int)v.size(); i++)
        cout << (i ? sp.s : "") << v[i];
    cout << "\n";
}
