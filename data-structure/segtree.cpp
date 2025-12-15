#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
ll op(ll a, ll b) { return a + b; }
ll e() { return 0; }
segtree<ll, op, e> seg(n);
*/
template<class S, S (*op)(S, S), S (*e)()> struct segtree {
   public:
   explicit segtree(int n) : _n(n), size(1) {
      while(size < _n) size *= 2;
      d.assign(2 * size, e());
   }
   explicit segtree(const std::vector<S>& v) : _n(int(v.size())), size(1) {
      while(size < _n) size *= 2;
      d.assign(2 * size, e());
      for(int i = 0; i < _n; i++) d[size + i] = v[i];
      for(int i = size - 1; i >= 1; i--) update(i);
   }
   void set(int p, S x) {
      assert(0 <= p && p < _n);
      p += size;
      d[p] = x;
      for(int i = p / 2; i >= 1; i /= 2) update(i);
   }
   S get(int p) const {
      assert(0 <= p && p < _n);
      return d[p + size];
   }
   S prod(int l, int r) const {
      assert(0 <= l && l <= r && r <= _n);
      S sml = e(), smr = e();
      l += size;
      r += size;
      while(l < r) {
         if(l & 1) sml = op(sml, d[l++]);
         if(r & 1) smr = op(d[--r], smr);
         l /= 2;
         r /= 2;
      }
      return op(sml, smr);
   }

   private:
   int _n, size;
   std::vector<S> d;
   void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};