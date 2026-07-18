#pragma once
#include "base.hpp"

// verified with https://atcoder.jp/contests/abc183/tasks/abc183_f

template <class S, class merge_t>
struct union_find_merge_tech {
    int sz;
    vector<int> par, size_;
    vector<S> dat;
    merge_t op;

    union_find_merge_tech(const vector<S>& node, merge_t op_ = {}) : sz(node.size()), par(sz), size_(sz, 1), dat(node), op(op_) {
        iota(par.begin(), par.end(), 0);
    }
    int find(int x) {
        if (par[x] == x)
            return x;
        else
            return par[x] = find(par[x]);
    }
    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (size_[x] < size_[y]) swap(x, y);
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