#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// returns pair{sa, lcp}
// sa 長さ n : s[sa[0]:] < s[sa[1]:] < … < s[sa[n-1]:]
// lcp 長さ n-1 : lcp[i] = LCP(s[sa[i]:], s[sa[i+1]:])
auto SA(string s) {
    ll n = s.size() + 1, lim = 256;
    // assert(lim > ranges::max(s));
    vector<ll> sa(n), lcp(n), x(s.begin(), s.end() + 1), y(n), ws(max(n, lim)),
        rk(n);
    iota(sa.begin(), sa.end(), 0);
    for(ll j = 0, p = 0; p < n; j = max(1LL, j * 2), lim = p) {
        p = j;
        iota(y.begin(), y.end(), n - j);
        for(int i = 0; i < n; i++)
            if(sa[i] >= j)
                y[p++] = sa[i] - j;
        fill(ws.begin(), ws.end(), 0);
        for(int i = 0; i < n; i++)
            ws[x[i]]++;
        for(int i = 1; i < lim; i++)
            ws[i] += ws[i - 1];
        for(ll i = n; i--;)
            sa[--ws[x[y[i]]]] = y[i];
        swap(x, y);
        p = 1;
        x[sa[0]] = 0;
        for(int i = 1; i < n; i++) {
            ll a = sa[i - 1], b = sa[i];
            x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
        }
    }
    for(int i = 1; i < n; i++)
        rk[sa[i]] = i;
    for(ll i = 0, k = 0; i < n - 1; lcp[rk[i++]] = k) {
        if(k)
            k--;
        while(s[i + k] == s[sa[rk[i] - 1] + k])
            k++;
    }
    sa.erase(begin(sa));
    lcp.erase(begin(lcp));
    return pair{sa, lcp};
}