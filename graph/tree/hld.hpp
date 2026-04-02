#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
    * Heavy-Light Decomposition
    *
    * Given a tree, decompose it into vertex-disjoint paths such that the path from any vertex to the root is a chain.
    *
    * - HLD(G, v): Construct a Heavy-Light Decomposition of tree G rooted at v.
    * - idx(i): Return the range of vertices in the path from the root to vertex i.
    * - path_query(u, v, vtx, f, commut): Perform a query on the path from u to v. If vtx is true, include the LCA of u
   and v. commut specifies whether the function f is commutative.
    * - subtree_query(u, vtx, f): Perform a query on the subtree rooted at u. If vtx is true, include the root.
    * - lca(a, b): Return the lowest common ancestor of vertices a and b.
    * - dist(a, b): Return the distance between vertices a and b.
    *
    * Time complexity:
    * - O(n) preprocessing
    * - O(log n) per query
    *
    * Usage with Segment Tree:
    * vvc<ll> g(n);
    * HLD hld(g);
    * ll op(ll a, ll b) { return a + b; }
    * ll e() { return 0; }
    * segtree<ll, op, e> seg(n);
    * while(q--) {
    *   ll t, u, v;
    *   cin >> t >> u >> v;
    *  u--, v--;
    *  if(t == 0) {
    *    ll ans = 0;
    *   hld.path_query(u, v, 1, [&](ll l, ll r) { ans += seg.prod(l, r); });
    *  cout << ans << '\n';
    * } else {
    *  seg.set(hld.idx(u).first, v);
    * }
*/
template<class G> struct HLD {
   G& g;
   ll n, id;
   vector<ll> siz, dep, down, up, nxt, par;
   void dfs_sz(ll i) {
      siz[i] = 1;
      if(ssize(g[i]) > 1 && par[i] == g[i][0]) swap(g[i][0], g[i][1]);
      for(auto& j : g[i]) {
         if(j != par[i]) {
            dep[j] = dep[i] + 1;
            par[j] = i;
            dfs_sz(j);
            siz[i] += siz[j];
            if(siz[j] > siz[g[i][0]]) swap(j, g[i][0]);
         }
      }
   }
   void dfs_hld(ll i) {
      down[i] = id++;
      for(auto j : g[i])
         if(j != par[i]) {
            nxt[j] = j == g[i][0] ? nxt[i] : j;
            dfs_hld(j);
         }
      up[i] = id;
   }
   // [u, v)
   vector<pair<ll, ll>> ascend(ll u, ll v) {
      vector<pair<ll, ll>> res;
      while(nxt[u] != nxt[v]) {
         res.emplace_back(down[u], down[nxt[u]]);
         u = par[nxt[u]];
      }
      if(u != v) res.emplace_back(down[u], down[v] + 1);
      return res;
   }
   // (u, v]
   vector<pair<ll, ll>> descend(ll u, ll v) {
      if(u == v) return {};
      if(nxt[u] == nxt[v]) return {{down[u] + 1, down[v]}};
      auto res = descend(u, par[nxt[v]]);
      res.emplace_back(down[nxt[v]], down[v]);
      return res;
   }
   HLD(G& g, ll v = 0) : g(g), n(ssize(g)), id(0), siz(n), dep(n), down(n, -1), up(n, -1), nxt(n, v), par(n, v) {
      dfs_sz(v);
      dfs_hld(v);
   }
   pair<ll, ll> idx(ll i) { return {down[i], up[i]}; }
   void path_query(ll u, ll v, bool vtx, auto f, bool commut = 0) {
      ll l = lca(u, v);
      for(auto [s, t] : ascend(u, l)) {
         s++;
         (!commut && s > t) ? f(t, s) : f(s, t);
      }
      if(vtx) f(down[l], down[l] + 1);
      for(auto [s, t] : descend(l, v)) {
         t++;
         (!commut && s > t) ? f(t, s) : f(s, t);
      }
   }
   void subtree_query(ll u, bool vtx, auto f) { f(down[u] + !vtx, up[u]); }
   ll lca(ll a, ll b) {
      while(nxt[a] != nxt[b]) {
         if(down[a] < down[b]) swap(a, b);
         a = par[nxt[a]];
      }
      return dep[a] < dep[b] ? a : b;
   }
   ll dist(ll a, ll b) { return dep[a] + dep[b] - dep[lca(a, b)] * 2; }
};