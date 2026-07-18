#pragma once
#include "base.hpp"

template <class M>
concept monoid = requires {
    typename M::value_t;
    { M::op(declval<typename M::value_t>(), declval<typename M::value_t>()) } -> same_as<typename M::value_t>;
    { M::e() } -> same_as<typename M::value_t>;
};

template <typename S>
struct add_monoid {
    using value_t = S;
    static value_t op(value_t a, value_t b) { return a + b; }
    static value_t e() { return 0; }
};

// f(x) = ax + b
// op(f, g) = f(g(x)) = f.a * (g.a * x + g.b) + f.b
template <typename S>
struct affine_monoid {
    using value_t = pair<S, S>;
    static value_t op(value_t f, value_t g) {
        return {f.first * g.first, f.first * g.second + f.second};
    }
    static value_t e() { return {S(1), S(0)}; }
};

struct min_monoid {
    using value_t = ll;
    static value_t op(value_t a, value_t b) { return min(a, b); }
    static value_t e() { return INF; }
};
struct min_count_monoid {
    using value_t = pair<ll, int>;
    static value_t op(value_t a, value_t b) {
        if (a.first == b.first)
            return {a.first, a.second + b.second};
        else
            return (a < b ? a : b);
    }
    static value_t e() { return {INF, 0}; }
};

struct max_monoid {
    using value_t = ll;
    static value_t op(value_t a, value_t b) { return max(a, b); }
    static value_t e() { return -INF; }
};
struct max_count_monoid {
    using value_t = pair<ll, int>;
    static value_t op(value_t a, value_t b) {
        if (a.first == b.first)
            return {a.first, a.second + b.second};
        else
            return (a > b ? a : b);
    }
    static value_t e() { return {-INF, 0}; }
};