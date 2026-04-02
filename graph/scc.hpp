#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
struct Edge{
    int from,to;
};
*/

struct SCC {
    vector<int> id;
    vector<vector<int>> groups;
};
template <class E> struct SCCExec : SCC {
    int n;
    const vector<vector<E>> &g;
    int tm = 0;
    vector<bool> flag;
    vector<int> low, ord, st;
    void dfs(int v) {
        low[v] = ord[v] = tm++;
        st.push_back(v);
        flag[v] = true;
        for(auto e : g[v]) {
            if(ord[e.to] == -1) {
                dfs(e.to);
                low[v] = min(low[v], low[e.to]);
            } else if(flag[e.to]) {
                low[v] = min(low[v], ord[e.to]);
            }
        }
        if(low[v] == ord[v]) {
            vector<int> gr;
            while(true) {
                int u = st.back();
                st.pop_back();
                gr.push_back(u);
                if(u == v)
                    break;
            }
            for(int x : gr)
                flag[x] = false;
            groups.push_back(gr);
        }
    }
    SCCExec(const vector<vector<E>> &_g) : n(sz(_g)), g(_g), flag(n), low(n), ord(n, -1) {
        id = vc<int>(n);
        for(int i = 0; i < n; i++) {
            if(ord[i] == -1)
                dfs(i);
        }
        reverse(groups.begin(), groups.end());
        for(int i = 0; i < groups.size(); i++) {
            for(int x : groups[i]) {
                id[x] = i;
            }
        }
    }
};
template <class E> SCC get_scc(const vector<vector<E>> &g) {
    return SCCExec<E>(g);
}