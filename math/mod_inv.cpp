#include <bits/stdc++.h>
using namespace std;

// https://github.com/drken1215/algorithm/blob/master/MathNumberTheory/mod_pow_inv.cpp

// aとmは互いに素である必要がある
// そうでない場合0を返す

template <class T_VAL, class T_MOD>
constexpr T_VAL mod_inv(T_VAL a, T_MOD m) {
    if(gcd(a, m) != 1) {
        return 0;
    }
    T_VAL b = m, u = 1, v = 0;
    while(b > 0) {
        T_VAL t = a / b;
        a -= t * b, swap(a, b);
        u -= t * v, swap(u, v);
    }
    u %= m;
    if(u < 0) u += m;
    return u;
}