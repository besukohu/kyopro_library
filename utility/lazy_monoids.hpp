#pragma once
#include "base.hpp"

template <class M>
concept lazy_monoid = requires {
    typename M::value_t;
    typename M::lazy_t;
    { M::op(declval<typename M::value_t>(), declval<typename M::value_t>()) } -> same_as<typename M::value_t>;
    { M::e() } -> same_as<typename M::value_t>;
    { M::mapping(declval<typename M::value_t>(), declval<typename M::lazy_t>()) } -> same_as<typename M::value_t>;
    { M::composition(declval<typename M::lazy_t>(), declval<typename M::lazy_t>()) } -> same_as<typename M::lazy_t>;
    { M::id() } -> same_as<typename M::lazy_t>;
};

struct range_add_range_sum {
    using value_t = pair<ll, int>;  // (sum, length)
    using lazy_t = ll;
    static value_t op(value_t a, value_t b) { return {a.first + b.first, a.second + b.second}; }
    static value_t e() { return {0, 0}; }
    static value_t mapping(lazy_t f, value_t x) { return {x.first + f * x.second, x.second}; }
    static lazy_t composition(lazy_t f, lazy_t g) { return f + g; }
    static lazy_t id() { return 0; }
};

struct range_set_range_sum {
    using value_t = pair<ll, int>;
    using lazy_t = optional<ll>;
    static value_t op(value_t a, value_t b) { return {a.first + b.first, a.second + b.second}; }
    static value_t e() { return {0, 0}; }
    static value_t mapping(lazy_t f, value_t x) { return f ? value_t{*f * x.second, x.second} : x; }
    static lazy_t composition(lazy_t f, lazy_t g) { return f ? f : g; }
    static lazy_t id() { return nullopt; }
};

struct range_add_range_min {
    using value_t = ll;
    using lazy_t = ll;
    static value_t op(value_t a, value_t b) { return min(a, b); }
    static value_t e() { return INF; }
    static value_t mapping(lazy_t f, value_t x) { return x + f; }
    static lazy_t composition(lazy_t f, lazy_t g) { return f + g; }
    static lazy_t id() { return 0; }
};

struct range_set_range_min {
    using value_t = ll;
    using lazy_t = optional<ll>;
    static value_t op(value_t a, value_t b) { return min(a, b); }
    static value_t e() { return INF; }
    static value_t mapping(lazy_t f, value_t x) { return f ? *f : x; }
    static lazy_t composition(lazy_t f, lazy_t g) { return f ? f : g; }
    static lazy_t id() { return nullopt; }
};

struct range_add_range_max {
    using value_t = ll;
    using lazy_t = ll;
    static value_t op(value_t a, value_t b) { return max(a, b); }
    static value_t e() { return -INF; }
    static value_t mapping(lazy_t f, value_t x) { return x + f; }
    static lazy_t composition(lazy_t f, lazy_t g) { return f + g; }
    static lazy_t id() { return 0; }
};

struct range_set_range_max {
    using value_t = ll;
    using lazy_t = optional<ll>;
    static value_t op(value_t a, value_t b) { return max(a, b); }
    static value_t e() { return -INF; }
    static value_t mapping(lazy_t f, value_t x) { return f ? *f : x; }
    static lazy_t composition(lazy_t f, lazy_t g) { return f ? f : g; }
    static lazy_t id() { return nullopt; }
};

template <typename S>
struct range_affine_range_sum {
    using value_t = pair<S, int>;
    using lazy_t = pair<S, S>;
    static value_t op(value_t a, value_t b) { return {a.first + b.first, a.second + b.second}; }
    static value_t e() { return {S(0), 0}; }
    static value_t mapping(lazy_t f, value_t x) { return {f.first * x.first + f.second * x.second, x.second}; }
    static lazy_t composition(lazy_t f, lazy_t g) { return {f.first * g.first, f.first * g.second + f.second}; }
    static lazy_t id() { return {S(1), S(0)}; }
};
