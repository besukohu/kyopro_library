#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct UnionFind {
    int sz;
    vector<int> par, size_;

    UnionFind(int node_size) : sz(node_size), par(sz), size_(sz, 1) {
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
        return true;
    }
    int size(int x) {
        x = find(x);
        return size_[x];
    }
    bool same(int x, int y) { return find(x) == find(y); }
};