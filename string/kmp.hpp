#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// kmp[i] := max{ l ≤ i | s[:l] == s[(i+1)-l:i+1] }
// abacaba -> 0010123
auto KMP(string s) {
    vector<ll> p(s.size());
    for(int i = 1; i < s.size(); i++) {
        ll g = p[i - 1];
        while(g && s[i] != s[g])
            g = p[g - 1];
        p[i] = g + (s[i] == s[g]);
    }
    return p;
}