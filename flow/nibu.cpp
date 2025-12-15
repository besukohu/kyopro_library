#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Bimatch {
    vector<vector<ll>> g;
    vector<ll> d, mc, used, vv;
    Bimatch(int n, int m) : g(n), mc(m, -1), used(n) {}
    void add(int u, int v) { g[u].emplace_back(v); }
    void bfs() {
        d.assign(g.size(), -1);
        queue<int> q;
        for(int i = 0; i < g.size(); i++) {
            if(!used[i]) {
                q.emplace(i);
                d[i] = 0;
            }
        }
        while(!q.empty()) {
            int x = q.front();
            q.pop();
            for(auto e : g[x]) {
                int c = mc[e];
                if(c >= 0 && d[c] == -1) {
                    d[c] = d[x] + 1;
                    q.emplace(c);
                }
            }
        }
    }
    bool dfs(int x) {
        vv[x] = true;
        for(auto e : g[x]) {
            int c = mc[e];
            if(c < 0 || (!vv[c] && d[c] == d[x] + 1 && dfs(c))) {
                mc[e] = x;
                used[x] = true;
                return true;
            }
        }
        return false;
    }
    int match() {
        int ret = 0;
        while(true) {
            bfs();
            vv.assign(g.size(), false);
            int f = 0;
            for(int i = 0; i < g.size(); i++)
                if(!used[i] && dfs(i)) f++;
            if(!f) return ret;
            ret += f;
        }
    }
};