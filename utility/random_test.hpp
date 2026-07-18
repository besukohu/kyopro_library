#pragma once
#include "base.hpp"

namespace random_test {
bool run_test = false;
const ll test_timelimit = 10000;

struct input {
    bool operator==(const input&) const = default;
};

struct output {
    bool operator==(const output&) const = default;
};

input read_input() {
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

output solve_debug(const input& in) {
    optional<output> out;

    // TODO
    {
    }

    assert(out);
    return *out;
}

output naive_debug(const input& in) {
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
}  // namespace random_test

// ランダムテスト時には以下に実装置き換え
// auto in = random_test::read_input();
// auto out = random_test::solve_debug(in);
// random_test::put_output(cout, out);

int main() {
    using namespace random_test;
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

            auto out_solve = solve_debug(in);
            auto out_naive = naive_debug(in);

            if (!compare_output(in, out_solve, out_naive)) {
                cerr << "seed = " << seed << endl;
                return 1;
            }
        }
        cerr << "pass" << endl;
        cerr << "turn = " << turn << endl;
        return 0;
    }
}