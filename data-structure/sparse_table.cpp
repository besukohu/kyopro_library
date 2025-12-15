#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <class T> struct RMQ {
    ll n;
    vector<vector<T>> jmp;
    RMQ(vector<T> a) : n(a.size()), jmp(__lg(n) + 1, a) {
        // assert(sz(a));
        for(int l = 0; l < __lg(n); l++) {
            ll w = 1 << l;
            for(int i = 0; i < n + 1 - w * 2; i++)
                jmp[l + 1][i] = min(jmp[l][i], jmp[l][i + w]);
        }
    }
    T query(ll a, ll b) {
        if(a == b)
            return INF;
        ll l = __lg(b - a);
        return min(jmp[l][a], jmp[l][b - (1 << l)]);
    }
};