#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct UnionFind {
    vector<ll> p, r;
    int gn;
    UnionFind(ll n = 0) : p(n, -1), r(n, 1), gn(n) {}
    void merge(ll a, ll b) {
        ll x = group(a), y = group(b);
        if(x == y)
            return;
        gn--;
        if(r[x] < r[y])
            p[x] = y;
        else {
            p[y] = x;
            if(r[x] == r[y])
                r[x]++;
        }
    }
    ll group(ll a) {
        if(p[a] == -1)
            return a;
        return p[a] = group(p[a]);
    }
    bool same(ll a, ll b) { return group(a) == group(b); }
};