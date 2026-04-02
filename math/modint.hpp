// https://github.com/drken1215/algorithm/blob/master/MathNumberTheory/modint_runtime.cpp

// 1<=MOD<=2^31-1
template <int MOD = 998244353, bool PRIME = true>
struct modint {
    // inner value
    unsigned int val;

    // constructor
    constexpr modint() : val(0) {}
    template <std::signed_integral T>
    constexpr modint(T v) {
        long long tmp = (long long)(v % (long long)(get_umod()));
        if(tmp < 0) tmp += get_umod();
        val = (unsigned int)(tmp);
    }
    template <std::unsigned_integral T>
    constexpr modint(T v) {
        val = (unsigned int)(v % get_umod());
    }
    constexpr long long get() const { return val; }
    constexpr static int get_mod() { return MOD; }
    constexpr static unsigned int get_umod() { return MOD; }

    // arithmetic operators
    constexpr modint operator+() const { return modint(*this); }
    constexpr modint operator-() const { return modint() - modint(*this); }
    constexpr modint operator+(const modint& r) const { return modint(*this) += r; }
    constexpr modint operator-(const modint& r) const { return modint(*this) -= r; }
    constexpr modint operator*(const modint& r) const { return modint(*this) *= r; }
    constexpr modint operator/(const modint& r) const { return modint(*this) /= r; }
    constexpr modint& operator+=(const modint& r) {
        val += r.val;
        if(val >= get_umod()) val -= get_umod();
        return *this;
    }
    constexpr modint& operator-=(const modint& r) {
        val -= r.val;
        if(val >= get_umod()) val += get_umod();
        return *this;
    }
    constexpr modint& operator*=(const modint& r) {
        unsigned long long tmp = val;
        tmp *= r.val;
        val = (unsigned int)(tmp % get_umod());
        return *this;
    }
    constexpr modint& operator/=(const modint& r) {
        return *this = *this * r.inv();
    }
    constexpr modint pow(long long n) const {
        assert(n >= 0);
        modint res(1), mul(*this);
        while(n) {
            if(n & 1) res *= mul;
            mul *= mul;
            n >>= 1;
        }
        return res;
    }
    template <class T_VAL, class T_MOD>
    constexpr T_VAL mod_inv(T_VAL a, T_MOD m) {
        if(gcd(a, m) != 1) {
            return 0;
        }
        T_VAL b = m, u = 1, v = 0;
        while(b > 0) {
            T_VAL t = a / b;
            a -= t * b, swap(a, b);
            u -= t * v, swap(u, v);
        }
        u %= m;
        if(u < 0) u += m;
        return u;
    }
    constexpr modint inv() const {
        if(PRIME) {
            assert(val);
            return pow(get_umod() - 2);
        } else {
            assert(val);
            return mod_inv((long long)(val), get_umod());
        }
    }

    // other operators
    constexpr bool operator==(const modint& r) const {
        return this->val == r.val;
    }
    constexpr bool operator!=(const modint& r) const {
        return this->val != r.val;
    }
    constexpr bool operator<(const modint& r) const {
        return this->val < r.val;
    }
    constexpr bool operator>(const modint& r) const {
        return this->val > r.val;
    }
    constexpr bool operator<=(const modint& r) const {
        return this->val <= r.val;
    }
    constexpr bool operator>=(const modint& r) const {
        return this->val >= r.val;
    }
    constexpr modint& operator++() {
        ++val;
        if(val == get_umod()) val = 0;
        return *this;
    }
    constexpr modint& operator--() {
        if(val == 0) val = get_umod();
        --val;
        return *this;
    }
    constexpr modint operator++(int) {
        modint res = *this;
        ++*this;
        return res;
    }
    constexpr modint operator--(int) {
        modint res = *this;
        --*this;
        return res;
    }
    friend constexpr istream& operator>>(istream& is, modint<MOD>& x) {
        long long tmp = 1;
        is >> tmp;
        tmp = tmp % (long long)(get_umod());
        if(tmp < 0) tmp += get_umod();
        x.val = (unsigned int)(tmp);
        return is;
    }
    friend constexpr ostream& operator<<(ostream& os, const modint<MOD>& x) {
        return os << x.val;
    }
    friend constexpr modint<MOD> pow(const modint<MOD>& r, long long n) {
        return r.pow(n);
    }
    friend constexpr modint<MOD> inv(const modint<MOD>& r) {
        return r.inv();
    }
};