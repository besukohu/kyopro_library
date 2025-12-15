#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// sum((ax + b) // m for x in range(n))
// n, m < 2^32
using u64 = unsigned long long;
u64 floor_sum_u(u64 n, u64 m, u64 a, u64 b) {
    u64 ans = 0;
    while(1) {
        if(a >= m) {
            ans += n * (n - 1) / 2 * (a / m);
            a %= m;
        }
        if(b >= m) {
            ans += n * (b / m);
            b %= m;
        }
        u64 y_max = a * n + b;
        if(y_max < m)
            break;
        n = y_max / m;
        b = y_max % m;
        swap(m, a);
    }
    return ans;
}
ll mod(ll a, ll b) {
    a %= b;
    if(a < 0)
        a += b;
    return a;
}
ll floor_sum(ll n, ll m, ll a, ll b) {
    u64 ans = 0;
    if(a < 0) {
        u64 a2 = mod(a, m);
        ans -= (u64)n * (n - 1) / 2 * ((a2 - a) / m);
        a = a2;
    }
    if(b < 0) {
        u64 b2 = mod(b, m);
        ans -= (u64)n * ((b2 - b) / m);
        b = b2;
    }
    return ans + floor_sum_u(n, m, a, b);
}