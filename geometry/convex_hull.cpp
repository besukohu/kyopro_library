/* Returns a vector of the points of the convex hull in
   counter-clockwise order.
 * Time: O(n log n) */
#include "base.cpp"
using P = Point<ll>;
vector<P> convexHull(vector<P> pts) {
   if(pts.size() <= 1) return pts;
   sort(pts.begin(),pts.end());
   vector<P> h(pts.size() + 1);
   ll s = 0, t = 0;
   for(int it = 0; it < 2; ++it, s = --t, reverse(pts.begin(),pts.end())) {
      for(P p : pts) {
         while(t >= s + 2 && h[t - 2].cross(h[t - 1], p) <= 0) t--;
         h[t++] = p;
      }
   }
   return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}