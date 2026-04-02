#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll INF = (1LL << 60);

// Capacity Scaling O(V E log(max cap))
// 流量を F として O(F E)
// O(ave(cap) E^1.5)
// 多重辺がないとき O(max(cap) V^{2/3} E) (定数個の例外はOK)//
// 頂点容量の平均値を k として O(k V^0.5 E) 無向化したときの s-t 最⻑路⻑を l
// として O(l^2 E)
struct Dinic {
    struct Edge {
        ll to, rev;
        ll c, oc;
        // ll flow() { return max(oc - c, 0LL); }
    };
    vector<ll> lv, it, q;
    vector<vector<Edge>> g;
    Dinic(ll n) : lv(n), it(n), q(n), g(n) {}
    void addEdge(ll a, ll b, ll c, ll rcap = 0) {
        g[a].push_back((Edge){b, g[b].size(), c, c});
        g[b].push_back((Edge){a, g[a].size() - 1, rcap, rcap});
    }
    ll dfs(ll v, ll t, ll f) {
        if(v == t || !f)
            return f;
        for(ll &i = it[v]; i < g[v].size(); i++)
            if(Edge &e = g[v][i]; lv[e.to] == lv[v] + 1)
                if(ll p = dfs(e.to, t, min(f, e.c))) {
                    e.c -= p;
                    g[e.to][e.rev].c += p;
                    return p;
                }
        return 0;
    }
    ll calc(ll s, ll t) {
        ll flow = 0;
        q[0] = s;
        // 'L=30' で 1 回にすると普通のDinic
        for(int L = 0; L < 31; L++)
            do {
                lv = it = vector<ll>(q.size());
                ll qi = 0, qe = lv[s] = 1;
                while(qi < qe && !lv[t]) {
                    ll v = q[qi++];
                    for(Edge e : g[v])
                        if(!lv[e.to] && e.c >> (30 - L)) {
                            q[qe++] = e.to;
                            lv[e.to] = lv[v] + 1;
                        }
                }
                while(ll p = dfs(s, t, INF))
                    flow += p;
            } while(lv[t]);
        return flow;
    }
    bool leftOfMinCut(ll a) { return lv[a]; }
};