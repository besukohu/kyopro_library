#pragma once
#include "base.hpp"

struct StaticTopTree {
    ll n, root_g, root_stt;
    vector<char> is_compress;
    vector<ll> lch, rch, top_exc, bot_inc, par, comp_leaf;
    vector<vector<ll>> g;
    StaticTopTree() {}
    StaticTopTree(ll n, const vector<vector<ll>>& G, ll root)
        : n(n), root_g(root) {
        g.resize(n);
        lch.assign(n, -1);
        rch.assign(n, -1);
        top_exc.assign(n, -1);
        bot_inc.assign(n, -1);
        par.assign(n, -1);
        comp_leaf.assign(n, -1);
        is_compress.assign(n, 0);
        auto dfs = [&](auto self, ll now, ll p) -> ll {
            ll siz = 1, best = 0;
            top_exc[now] = p;
            bot_inc[now] = now;
            for (auto& x : G[now]) {
                if (p == x) continue;
                g[now].push_back(x);
                ll res = self(self, x, now);
                siz += res;
                if (best < res) best = res, swap(g[now][0], g[now].back());
            }
            return siz;
        };
        dfs(dfs, root_g, -1);

        build(root_g);
    }

   private:
    ll add_node(ll l, ll r, ll t, ll b, bool c) {
        int idx = par.size();
        par.emplace_back(-1);
        lch.emplace_back(l);
        rch.emplace_back(r);
        top_exc.emplace_back(t);
        bot_inc.emplace_back(b);
        is_compress.emplace_back(c);
        par[l] = idx;
        par[r] = idx;
        return idx;
    }
    ll build(ll v) {
        vector<ll> path(1, v);
        ll now = v;
        while (g[now].size()) {
            now = g[now][0];
            path.push_back(now);
        }

        vector<ll> comp(1, v);
        comp_leaf[v] = v;
        for (int i = 1; i < path.size(); i++) {
            ll k = path[i], kp = path[i - 1];
            vector<ll> rake(1, k);
            for (int j = 1; j < g[kp].size(); j++) {
                rake.emplace_back(build(g[kp][j]));
            }
            while (rake.size() > 1) {
                vector<ll> rake2;
                for (int j = 0; j + 1 < rake.size(); j += 2) {
                    ll idx1 = rake[j], idx2 = rake[j + 1];
                    if (idx2 == k) swap(idx1, idx2);
                    ll add_idx = add_node(idx1, idx2, top_exc[idx1], bot_inc[idx1], false);
                    if (idx1 == k) k = add_idx;
                    rake2.push_back(add_idx);
                }
                if (rake.size() % 2) rake2.push_back(rake.back());
                swap(rake, rake2);
            }
            comp.push_back(rake.back());
            comp_leaf[path[i]] = rake.back();
        }
        while (comp.size() > 1) {
            vector<ll> comp2;
            for (int j = 0; j + 1 < comp.size(); j += 2) {
                ll idx1 = comp[j], idx2 = comp[j + 1];
                ll add_idx = add_node(idx1, idx2, top_exc[idx1], bot_inc[idx2], true);
                comp2.push_back(add_idx);
            }
            if (comp.size() % 2) comp2.push_back(comp.back());
            swap(comp, comp2);
        }
        return comp.back();
    }
};

template <typename TREEDP>
struct DynamicTreeDp {
    using S = typename TREEDP::value_type;
    StaticTopTree STT;
    vector<S> dp;

    DynamicTreeDp(const vector<vector<ll>>& g, const vector<S>& a, ll root) {
        STT = StaticTopTree(g.size(), g, root);
        ll gn = g.size();
        ll sttn = STT.par.size();
        dp.resize(sttn);
        for (int i = 0; i < gn; i++)
            dp[i] = a[i];
        for (int i = gn; i < sttn; i++)
            update(i);
    }

    void set(int v, S x) {
        dp[v] = x;
        for (int i = STT.par[v]; i != -1; i = STT.par[i]) update(i);
    }

    S subtree_query(int v) {
        S res = dp[v];
        int now = STT.comp_leaf[v];
        while (STT.par[now] != -1 && STT.is_compress[STT.par[now]]) {
            if (STT.lch[STT.par[now]] == now) {
                res = TREEDP::compress(res, dp[STT.rch[STT.par[now]]]);
            }
            now = STT.par[now];
        }
        return res;
    }

    S prod_all() { return dp.back(); }

   private:
    inline void update(int i) {
        S &L = dp[STT.lch[i]], &R = dp[STT.rch[i]];
        dp[i] = (STT.is_compress[i] ? TREEDP::compress(L, R) : TREEDP::rake(L, R));
    }
};

struct S {
    ll ans;
};

struct TREEDP {
    using value_type = S;
    static S rake(S& L, S& R) { return {L.ans + R.ans}; }
    static S compress(S& L, S& R) { return {L.ans + R.ans}; }
};