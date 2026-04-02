#include "base.cpp"

ll INF = 1e18;

using P = Point<double>;
/* Computes the pair of points at which two circles intersect.Returns false in case of no intersection. */
bool circleInter(P a, P b, double r1, double r2, pair<P, P>* out) {
   if(a == b) {
      assert(r1 != r2);
      return false;
   }
   P vec = b - a;
   double d2 = vec.dist2(), sum = r1 + r2, dif = r1 - r2, p = (d2 + r1 * r1 - r2 * r2) / (d2 * 2),
          h2 = r1 * r1 - p * p * d2;
   if(sum * sum < d2 || dif * dif > d2) return false;
   P mid = a + vec * p, per = vec.perp() * sqrt(fmax(0, h2) / d2);
   *out = {mid + per, mid - per};
   return true;
}
/* Finds the intersection between a circle and a line.
 * Returns a vector of either 0, 1, or 2 intersection points.* P is intended to be Point<double>.
 * c : center of the circle
 * r : radius of the circle
 * a, b : two distinct points on the line
 */
template<class P> vector<P> circleLine(P c, double r, P a, P b) {
   P ab = b - a, p = a + ab * (c - a).dot(ab) / ab.dist2();
   double s = a.cross(b, c), h2 = r * r - s * s / ab.dist2();
   if(h2 < 0) return {};
   if(h2 == 0) return {p};
   P h = ab.unit() * sqrt(h2);
   return {p - h, p + h};
}
/* Returns the area of the intersection of a circle with a
 * ccw polygon.
 * Time: O(n) */
#define arg(p, q) atan2(p.cross(q), p.dot(q))
double circlePoly(P c, double r, vector<P> ps) {
   auto tri = [&](P p, P q) {
      auto r2 = r * r / 2;
      P d = q - p;
      auto a = d.dot(p) / d.dist2(), b = (p.dist2() - r * r) / d.dist2();
      auto det = a * a - b;
      if(det <= 0) return arg(p, q) * r2;
      auto s = max(0.0, -a - sqrt(det)), t = min(1.0, -a + sqrt(det));
      if(t < 0 || 1 <= s) return arg(p, q) * r2;
      P u = p + d * s, v = p + d * t;
      return arg(p, u) * r2 + u.cross(v) / 2 + arg(v, q) * r2;
   };
   auto sum = 0.0;
   for(int i = 0;i< ps.size();i++) sum += tri(ps[i] - c, ps[(i + 1) % ps.size()] - c);
   return sum;
}
/* Finds the external tangents of two circles, or internal if
r2 is negated. Can return 0, 1, or 2 tangents -- 0 if one
circle contains the other (or overlaps it, in the internal
case, or if the circles are the same);
* 1 if the circles are tangent to each other (in which case
.first = .second and the tangent line is perpendicular to the
line between the centers).
* .first and .second give the tangency points at circle 1 and
2 respectively.
* To find the tangents of a circle with a point set r2 to 0.
*/
template<class P> vector<pair<P, P>> tangents(P c1, double r1, P c2, double r2) {
   P d = c2 - c1;
   double dr = r1 - r2, d2 = d.dist2(), h2 = d2 - dr * dr;
   if(d2 == 0 || h2 < 0) return {};
   vector<pair<P, P>> out;
   for(double sign : {-1, 1}) {
      P v = (d * dr + d.perp() * sqrt(h2) * sign) / d2;
      out.push_back({c1 + v * r1, c2 + v * r2});
   }
   if(h2 == 0) out.pop_back();
   return out;
}
/* Finds the closest pair of points.
 * Time: O(n log n) */
// using P = Point<ll>;
pair<P, P> closest(vector<P> v) {
   assert(v.size() > 1);
   set<P> S;
   ranges::sort(v, {}, &P::y);
   pair<ll, pair<P, P>> ret{INF, {P(), P()}};
   ll j = 0;
   for(P p : v) {
      P d{1 + (ll)sqrt(ret.first), 0};
      while(v[j].y <= p.y - d.x) S.erase(v[j++]);
      auto lo = S.lower_bound(p - d), hi = S.upper_bound(p + d);
      for(; lo != hi; ++lo) ret = min(ret, {(*lo - p).dist2(), {*lo, p}});
      S.insert(p);
   }
   return ret.second;
}