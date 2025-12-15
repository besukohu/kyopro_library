#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Z[i] := LCP(s, s[i:])
// abacaba -> 7010301
auto Z(string s) {
    ll n = s.size(), l = -1, r = -1;
    vector<ll> z(n, n);
    for(int i = 1; i < n; i++) {
        ll &x = z[i] = i < r ? min(r - i, z[i - l]) : 0;
        while(i + x < n && s[i + x] == s[x])
            x++;
        if(i + x > r)
            l = i, r = i + x;
    }
    return z;
}