#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using a2 = array<ll, 2>;
using a3 = array<ll, 3>;

bool chmin(auto& a, const auto& b) { return a > b ? a = b, 1 : 0; }
bool chmax(auto& a, const auto& b) { return a < b ? a = b, 1 : 0; }

ll floor_div(ll a, ll b) { return a / b - (a % b != 0 && (a ^ b) < 0); }
ll ceil_div(ll a, ll b) { return a / b + (a % b != 0 && (a ^ b) > 0); }
ll floor_mod(ll a, ll b) { return a % b + (a % b != 0 && (a ^ b) < 0) * b; }

std::mt19937 mt(time(0));
class xor_shift_128 {
   public:
    typedef uint32_t result_type;
    xor_shift_128(result_type seed = mt()) {
        set_seed(seed);
    }
    void set_seed(result_type seed) {
        a = seed = 1812433253 * (seed ^ (seed >> 30));
        b = seed = 1812433253 * (seed ^ (seed >> 30)) + 1;
        c = seed = 1812433253 * (seed ^ (seed >> 30)) + 2;
        d = seed = 1812433253 * (seed ^ (seed >> 30)) + 3;
    }
    result_type gen() {
        result_type t = (a ^ (a << 11));
        a = b;
        b = c;
        c = d;
        return d = (d ^ (d >> 19)) ^ (t ^ (t >> 8));
    }
    result_type operator()() {
        return gen();
    }
    result_type gen_range(result_type min_inclusive, result_type max_exclusive) {
        result_type diff = max_exclusive - min_inclusive;
        return min_inclusive + gen() % diff;
    }

    static constexpr result_type max() { return numeric_limits<result_type>::max(); }
    static constexpr result_type min() { return numeric_limits<result_type>::min(); }

   private:
    result_type a, b, c, d;
};
xor_shift_128 xorrand;
ifstream inst;
ofstream outst;

const ll INF = (1LL << 61);
ll mod = 998244353;

struct input {
    bool operator==(const input&) const = default;
};

struct output {
    bool operator==(const output&) const = default;
};

bool is_multi = false;

bool run_test = false;
const ll test_timelimit = 10000;

input get_input() {
    optional<input> in;

    // TODO
    {
    }

    assert(in);
    return *in;
}

void put_input(ostream& os, const input& in) {
    // osを使おう
}

void put_output(ostream& os, const output& out) {
    // osを使おう
}

output solve(const input& in) {
    optional<output> out;

    // TODO
    {
    }

    assert(out);
    return *out;
}

output naive(const input& in) {
    optional<output> out;

    // TODO
    {
    }

    assert(out);
    return *out;
}

input gen() {
    optional<input> in;

    // TODO
    {
    }

    assert(in);
    return *in;
}

// 構築の場合チェッカーを書く
bool compare_output(const input& in, const output& out_solve, const output& out_naive) {
    if (out_solve != out_naive) {
        cerr << "case:" << endl;
        put_input(cerr, in);
        cerr << "solve:" << endl;
        put_output(cerr, out_solve);
        cerr << "naive:" << endl;
        put_output(cerr, out_naive);
        return false;
    }
    return true;
}

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    if (argc >= 3) {
        inst.open(argv[1]);
        cin.rdbuf(inst.rdbuf());
        outst.open(argv[2]);
        cout.rdbuf(outst.rdbuf());
    }

    if (run_test) {
        auto starttime = chrono::system_clock::now();

        ll turn = 0;
        for (;; turn++) {
            ll timediff = duration_cast<chrono::milliseconds>(chrono::system_clock::now() - starttime).count();
            if (timediff > test_timelimit) {
                break;
            }
            ll seed = mt();
            xorrand.set_seed(seed);
            auto in = gen();

            auto out_solve = solve(in);
            auto out_naive = naive(in);

            if (!compare_output(in, out_solve, out_naive)) {
                cerr << "seed = " << seed << endl;
                return 0;
            }
        }
        cerr << "pass" << endl;
        cerr << "turn = " << turn << endl;
        return 1;
    }

    ll tests = 1;
    if (is_multi) {
        cin >> tests;
    }

    while (tests--) {
        auto in = get_input();
        auto out = solve(in);
        put_output(cout, out);
    }

    return 0;
}