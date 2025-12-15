#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool chmin(auto& a, const auto& b) { return a > b ? a = b, 1 : 0; }
bool chmax(auto& a, const auto& b) { return a < b ? a = b, 1 : 0; }

template <typename G>
struct Lowlink {
    int n;
    const G g;
    vector<ll> ord, low, arti;
    vector<pair<ll, ll>> bridge;
    Lowlink(G g) : n(g.size()), g(g), ord(g.size(), -1), low(g.size(), -1) {
        int k = 0;
        for(int i = 0; i < n; i++) {
            if(ord[i] == -1) k = dfs(i, k, -1);
        }
    }
    int dfs(int x, int k, int p) {
        low[x] = (ord[x] = k++);
        int cnt = 0;
        bool is_arti = false, second = false;
        for(auto e : g[x]) {
            if(ord[e] == -1) {
                cnt++;
                k = dfs(e, k, x);
                chmin(low[x], low[e]);
                is_arti |= (p != -1) && (low[e] >= ord[x]);
                if(ord[x] < low[e]) bridge.emplace_back(minmax(x, e));
            } else if(e != p or second) {
                chmin(low[x], ord[e]);
            } else {
                second = true;
            }
        }
        is_arti |= p == -1 && cnt > 1;
        if(is_arti) arti.emplace_back(x);
        return k;
    }
};