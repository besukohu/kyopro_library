#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// verifyed with https://atcoder.jp/contests/abc183/tasks/abc183_f

template <class S, void (*op)(S&, S&)>
struct UnionFind_Monoid {
    int sz;
    vector<int> par, size_;
    vector<S> dat;

    UnionFind_Monoid(int node_size) : sz(node_size), par(sz), size_(sz, 1) {
        iota(par.begin(), par.end(), 0);
        dat.assign(sz, S());
    }
    UnionFind_Monoid(const vector<S>& node) : sz(node.size()), par(sz), size_(sz, 1), dat(node) {
        iota(par.begin(), par.end(), 0);
    }
    int find(int x) {
        if(par[x] == x)
            return x;
        else
            return par[x] = find(par[x]);
    }
    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if(x == y) return false;
        if(size_[x] < size_[y]) swap(x, y);
        par[y] = x;
        size_[x] += size_[y];
        op(dat[x], dat[y]);
        return true;
    }
    int size(int x) {
        x = find(x);
        return size_[x];
    }
    const S& get(int x) {
        x = find(x);
        return dat[x];
    }
    bool same(int x, int y) { return find(x) == find(y); }
};