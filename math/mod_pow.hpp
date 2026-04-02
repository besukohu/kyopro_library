// https://github.com/drken1215/algorithm/blob/master/MathNumberTheory/mod_pow_inv.cpp

template <class T_VAL, class T_MOD>
constexpr T_VAL mod_pow(T_VAL a, T_VAL n, T_MOD m) {
    T_VAL res = 1;
    while(n > 0) {
        if(n % 2 == 1) res = res * a % m;
        a = a * a % m;
        n >>= 1;
    }
    return res;
}