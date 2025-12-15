#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct BIT {
    vector<ll> a;
    BIT(ll n) : a(n + 1) {}
    void add(ll i, ll x) {  // A[i] += x
        i++;
        while(i < a.size())
            a[i] += x, i += i & -i;
    }
    ll sum(ll r) {
        ll s = 0;
        while(r)
            s += a[r], r -= r & -r;
        return s;
    }
    ll sum(ll l, ll r) {  // sum of A[l, r)
        return sum(r) - sum(l);
    }
    /// sum[0, idx) >= x なる最小の idx(sum[0, n) < x なら n+1)
    ll sum_lower_bound(ll x) {
        if(x <= 0)
            return 0;
        ll res = 0, len = 1;
        while(2 * len <= a.size())
            len *= 2;
        for(; len >= 1; len /= 2) {
            if(res + len < a.size() && a[res + len] < x) {
                res += len;
                x -= a[res];
            }
        }
        return res + 1;
    }
};