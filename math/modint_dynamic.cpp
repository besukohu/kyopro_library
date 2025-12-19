// https://github.com/drken1215/algorithm/blob/master/MathNumberTheory/modint_runtime.cpp

// IDでMOD共有
template <int ID>
struct modint_dynamic {
    using mint = modint_dynamic;

    // static menber
    static int MOD;

    // inner value
    unsigned int val;

    // constructor
    modint_dynamic() : val(0) {}
    template <std::signed_integral T>
    modint_dynamic(T v) {
        long long tmp = (long long)(v % (long long)(get_umod()));
        if(tmp < 0) tmp += get_umod();
        val = (unsigned int)(tmp);
    }
    template <std::unsigned_integral T>
    modint_dynamic(T v) {
        val = (unsigned int)(v % get_umod());
    }
    long long get() const { return val; }
    static int get_mod() { return MOD; }
    static unsigned int get_umod() { return MOD; }
    static void set_mod(int mod) { MOD = mod; }

    // arithmetic operators
    mint operator+() const { return mint(*this); }
    mint operator-() const { return mint() - mint(*this); }
    mint operator+(const mint& r) const { return mint(*this) += r; }
    mint operator-(const mint& r) const { return mint(*this) -= r; }
    mint operator*(const mint& r) const { return mint(*this) *= r; }
    mint operator/(const mint& r) const { return mint(*this) /= r; }
    mint& operator+=(const mint& r) {
        val += r.val;
        if(val >= get_umod()) val -= get_umod();
        return *this;
    }
    mint& operator-=(const mint& r) {
        val -= r.val;
        if(val >= get_umod()) val += get_umod();
        return *this;
    }
    mint& operator*=(const mint& r) {
        unsigned long long tmp = val;
        tmp *= r.val;
        val = (unsigned int)(tmp % get_umod());
        return *this;
    }
    mint& operator/=(const mint& r) {
        return *this = *this * r.inv();
    }
    mint pow(long long n) const {
        assert(n >= 0);
        mint res(1), mul(*this);
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
    mint inv() const {
        assert(val);
        return mod_inv((long long)(val), get_umod());
    }

    // other operators
    bool operator==(const mint& r) const {
        return this->val == r.val;
    }
    bool operator!=(const mint& r) const {
        return this->val != r.val;
    }
    bool operator<(const mint& r) const {
        return this->val < r.val;
    }
    bool operator>(const mint& r) const {
        return this->val > r.val;
    }
    bool operator<=(const mint& r) const {
        return this->val <= r.val;
    }
    bool operator>=(const mint& r) const {
        return this->val >= r.val;
    }
    mint& operator++() {
        ++val;
        if(val == get_umod()) val = 0;
        return *this;
    }
    mint& operator--() {
        if(val == 0) val = get_umod();
        --val;
        return *this;
    }
    mint operator++(int) {
        mint res = *this;
        ++*this;
        return res;
    }
    mint operator--(int) {
        mint res = *this;
        --*this;
        return res;
    }
    friend istream& operator>>(istream& is, mint& x) {
        long long tmp = 1;
        is >> tmp;
        tmp = tmp % (long long)(get_umod());
        if(tmp < 0) tmp += get_umod();
        x.val = (unsigned int)(tmp);
        return is;
    }
    friend ostream& operator<<(ostream& os, const mint& x) {
        return os << x.val;
    }
    friend mint pow(const mint& r, long long n) {
        return r.pow(n);
    }
    friend mint inv(const mint& r) {
        return r.inv();
    }
};
template <int ID>
int modint_dynamic<ID>::MOD;