#include <bits/stdc++.h>

#include "data-structure/lazy_segtree.hpp"

using namespace std;
using ll = long long;
using a2 = array<ll, 2>;

namespace besukohu {
const ll INF = (1LL << 61);

using S = a2;
S op(S a, S b) {
    if (a[0] == b[0])
        return S{a[0], a[1] + b[1]};
    else
        return (a < b ? a : b);
}
S e() { return S{INF, 0}; }
using F = ll;
S mapping(F f, S x) { return S{f + x[0], x[1]}; }
F composition(F f, F g) { return f + g; }
F id() { return 0; }

struct area_of_union_of_rectangles {
   private:
    using a3 = array<ll, 3>;
    using a4 = array<ll, 4>;

   public:
    area_of_union_of_rectangles() {
    }

    // [h1,h2)*[w1,w2)の長方形を追加
    void add_rectangle(ll h1, ll w1, ll h2, ll w2) {
        rects.push_back(a4{h1, w1, h2, w2});
    }

    // 長方形領域の和集合の面積を返す
    ll run() {
        if (rects.empty())
            return 0;
        vector<ll> hs, ws;
        for (auto& [h1, w1, h2, w2] : rects) {
            hs.push_back(h1);
            hs.push_back(h2);
            ws.push_back(w1);
            ws.push_back(w2);
        }
        sort(hs.begin(), hs.end());
        sort(ws.begin(), ws.end());
        hs.erase(unique(hs.begin(), hs.end()), hs.end());
        ws.erase(unique(ws.begin(), ws.end()), ws.end());

        vector<vector<a3>> query(hs.size());
        for (auto& [h1, w1, h2, w2] : rects) {
            ll l = lower_bound(ws.begin(), ws.end(), w1) - ws.begin();
            ll r = lower_bound(ws.begin(), ws.end(), w2) - ws.begin();
            ll u = lower_bound(hs.begin(), hs.end(), h1) - hs.begin();
            ll d = lower_bound(hs.begin(), hs.end(), h2) - hs.begin();
            query[u].push_back({l, r, 1});
            query[d].push_back({l, r, -1});
        }

        lazy_segtree<S, op, e, F, mapping, composition, id> seg(vector<S>(ws.size(), a2{0, 0}));
        for (int i = 0; i + 1 < ws.size(); i++) {
            seg.set(i, {0, ws[i + 1] - ws[i]});
        }

        ll w_range = ws.back() - ws.front();

        ll ret = 0;
        for (int i = 0; i < hs.size(); i++) {
            if (i) {
                ll dw = w_range, dh = 0;
                S res = seg.prod(0, ws.size());
                if (res[0] == 0) {
                    dw -= res[1];
                }
                dh = hs[i] - hs[i - 1];
                ret += dh * dw;
            }
            for (auto& [l, r, val] : query[i]) {
                seg.apply(l, r, val);
            }
        }

        return ret;
    }

   private:
    vector<a4> rects;
};
}  // namespace besukohu
