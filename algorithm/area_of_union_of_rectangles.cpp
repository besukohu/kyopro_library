#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using a2 = array<ll, 2>;

const ll INF = (1 << 61);

template <class S, S (*op)(S, S), S (*e)(), class F, S (*mapping)(F, S), F (*composition)(F, F), F (*id)()>
struct lazy_segtree {
   public:
    lazy_segtree() : lazy_segtree(0) {}
    explicit lazy_segtree(int n) : lazy_segtree(vector<S>(n, e())) {}
    explicit lazy_segtree(const vector<S>& v) : _n(int(v.size())) {
        size = (int)bit_ceil((unsigned int)(_n));
        log = countr_zero((unsigned int)size);
        d = vector<S>(2 * size, e());
        lz = vector<F>(size, id());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }
    void set(int p, S x) {
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }

    S prod(int l, int r) {
        if (l == r) return e();
        l += size;
        r += size;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() {
        return d[1];
    }

    void apply(int l, int r, F f) {
        if (l == r) return;
        l += size;
        r += size;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }
        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    template <class G>
    int max_right(int l, G g) {
        if (l == _n) return _n;
        l += size;
        for (int i = log; i >= 1; i--) push(l >> i);
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(op(sm, d[l]))) {
                while (l < size) {
                    push(l);
                    l = (2 * l);
                    if (g(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <class G>
    int min_left(int r, G g) {
        if (r == 0) return 0;
        r += size;
        for (int i = log; i >= 1; i--) push((r - 1) >> i);
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(op(d[r], sm))) {
                while (r < size) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

   private:
    int _n, size, log;
    vector<S> d;
    vector<F> lz;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if (k < size) lz[k] = composition(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }

    unsigned int bit_ceil(unsigned int n) {
        unsigned int x = 1;
        while (x < (unsigned int)(n)) x *= 2;
        return x;
    }
    int countr_zero(unsigned int n) { return __builtin_ctz(n); }
    constexpr int countr_zero_constexpr(unsigned int n) {
        int x = 0;
        while (!(n & (1 << x))) x++;
        return x;
    }
};

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
