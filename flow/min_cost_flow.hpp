#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool chmin(auto &a, const auto &b) { return a > b ? a = b, 1 : 0; }
bool chmax(auto &a, const auto &b) { return a < b ? a = b, 1 : 0; }

struct MCF {
    struct edge {
        int to;
        ll cap, cost;
        int rev;
        bool isrev;
        // edge(int to, ll cap, ll cost, int rev, bool isrev) : to(to),
        // cap(cap), cost(cost), rev(rev), isrev(isrev) {}
    };

    vector<vector<edge>> g;
    vector<ll> pot, cost;
    vector<int> pv, pe;
    const ll INFL = 1LL << 60;
    MCF(int n) : g(n), pot(n, INFL) {}
    void add(int u, int v, ll cap, ll cost) {
        g[u].emplace_back(v, cap, cost, g[v].size(), false);
        g[v].emplace_back(u, 0, -cost, g[u].size() - 1, true);
    }
    ll mcf(int s, int t, ll f) {
        int n = g.size();
        ll ret = 0;
        using P = pair<ll, int>;
        // 負辺があるとき
        pot[s] = 0;
        for(int i = 0; i < n - 1; i++) {
            bool updated = false;
            for(int u = 0; u < n; u++) {
                if(pot[u] == INFL)
                    continue;
                for(auto &e : g[u]) {
                    if(e.cap > 0 && chmin(pot[e.to], pot[u] + e.cost)) {
                        updated = true;
                    }
                }
            }
            if(!updated)
                break;
        }
        while(f > 0) {
            cost.assign(n, INFL);
            pv.assign(n, -1);
            pe.assign(n, -1);
            priority_queue<P, vector<P>, greater<P>> pq;
            cost[s] = 0;
            pq.emplace(0, s);
            while(!pq.empty()) {
                auto [c, u] = pq.top();
                pq.pop();
                if(cost[u] < c)
                    continue;
                for(int i = 0; i < g[u].size(); i++) {
                    edge &e = g[u][i];
                    ll ncost = cost[u] + e.cost + pot[u] - pot[e.to];
                    if(e.cap > 0 && cost[e.to] > ncost) {
                        cost[e.to] = ncost;
                        pv[e.to] = u;
                        pe[e.to] = i;
                        pq.emplace(cost[e.to], e.to);
                    }
                }
            }
            if(cost[t] == INFL)
                return -1;
            for(int i = 0; i < n; i++)
                pot[i] += cost[i];
            ll addflow = f;
            for(int v = t; v != s; v = pv[v])
                chmin(addflow, g[pv[v]][pe[v]].cap);
            f -= addflow;
            ret += addflow * pot[t];
            for(int v = t; v != s; v = pv[v]) {
                edge &e = g[pv[v]][pe[v]];
                e.cap -= addflow;
                g[v][e.rev].cap += addflow;
            }
        }
        return ret;
    }
};