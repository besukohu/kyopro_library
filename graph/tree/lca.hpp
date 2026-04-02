// オイラーツアー + SparseTable <O(N log N), O(1)>
// tour := DFS 順の頂点列
// in[i] := tour の何番⽬に i があるか (親の⽅が番号が⼩さいので// depth
// の代わり) v := ツアーの⾏きの辺に親の in[i] を載せた列
#include "../data-structure/sparse_table.cpp"
struct LCA {
    ll T = 0;
    vector<ll> in, tour, v;
    RMQ<ll> rmq;
    LCA(vector<vector<ll>>& g) : in(g.size()), rmq((dfs(g, -1, 0), v)) {}
    void dfs(vector<vector<ll>>& g, ll p, ll i) {
        in[i] = T++;
        tour.push_back(i);
        for(ll j : g[i])
            if(j != p) {
                v.push_back(in[i]);
                dfs(g, i, j);
            }
    }
    ll lca(ll a, ll b) {
        if(a == b) return a;
        tie(a, b) = minmax(in[a], in[b]);
        return tour[rmq.query(a, b)];
    }
};