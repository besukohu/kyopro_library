#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/**
    CHT cht;
    cht.add_line(2, 3);            // y = 2x + 3
    cht.add_line(-1, 10);          // y = -x + 10
    cout << cht.query(5) << endl;  // x = 5での最小値
**/
// 単調
struct L {
   ll A, B;
   L(ll a, ll b) : A(a), B(b) {}
   ll eval(ll x) const { return A * x + B; }
};
class CHT_mono {
   deque<L> ls;
   bool noNeed(const L& l1, const L& l2, const L& nl) {
      return (nl.B - l2.B) * (l1.A - l2.A) <= (l2.B - l1.B) * (l2.A - nl.A);
   }

   public:
   void add_line(ll a, ll b) {
      L nl(a, b);
      while(ls.size() >= 2 && noNeed(ls[ls.size() - 2], ls.back(), nl)) ls.pop_back();
      ls.push_back(nl);
   }
   ll query(ll x) {
      while(ls.size() >= 2 && ls[0].eval(x) >= ls[1].eval(x)) ls.pop_front();
      return ls[0].eval(x);
   }
};
// 非単調
// CHT(lpos,rpos) : [lpos,rpos) の範囲で直線を追加、クエリを行う
template<typename T> class CHT {
   private:
   struct node {
      node *left, *right;
      static const T inf = numeric_limits<T>::max();
      T a, b;
      node() : node(0, inf) {}
      node(const T _a, const T _b) : left(nullptr), right(nullptr), a(_a), b(_b) {}
      T f(const T x) const { return a * x + b; }
   };
   static void swap(node* x, node* y) { swap(x->a, y->a), swap(x->b, y->b); }
   void _add_line(node* cur, node* nw, T l, T r) {
      while(true) {
         if(nw->f(l) < cur->f(l)) swap(cur, nw);
         if(cur->f(r - 1) <= nw->f(r - 1)) break;
         const T mid = (l + r) / 2;
         if(cur->f(mid) <= nw->f(mid)) {
            if(!cur->right) {
               cur->right = new node(*nw);
               break;
            } else {
               cur = cur->right, l = mid;
            }
         } else {
            swap(cur, nw);
            if(!cur->left) {
               cur->left = new node(*nw);
               break;
            } else {
               cur = cur->left, r = mid;
            }
         }
      }
   }
   T query(node* cur, const T k, T l, T r) const {
      T ans = numeric_limits<T>::max();
      while(cur) {
         ans = min(ans, cur->f(k));
         const T mid = (l + r) / 2;
         if(k < mid) {
            cur = cur->left, r = mid;
         } else {
            cur = cur->right, l = mid;
         }
      }
      return ans;
   }
   void clear(node* cur) {
      if(cur->left) clear(cur->left);
      if(cur->right) clear(cur->right);
      delete cur;
   }
   const T lpos, rpos;
   node* root;

   public:
   CHT(const T _lpos, const T _rpos) : lpos(_lpos), rpos(_rpos), root(new node()) { assert(lpos < rpos); }
   // ~CHT(){ clear(root); }
   // f(x) = a * x + b を挿入
   void add_line(const T a, const T b) {
      node nw(a, b);
      return _add_line(root, &nw, lpos, rpos);
   }
   // x = k での最小値
   T query(const T k) const { return query(root, k, lpos, rpos); }
};