/* If a unique intersection point of the lines going throughs1,e1 and s2,e2 exists \{1, point\} is returned.
If no intersection point exists \{0, (0,0)\} is returnedandifinfinitely many exists \{-1, (0,0)\} is returned.
The wrong position will be returned if P is Point<ll> andtheintersection point does not have integer coordinates.
Products of three coordinates are used in intermediate stepssowatch out for overflow if using ll or ll.
* auto res = lineInter(s1,e1,s2,e2);
* if (res.first == 1)
* cout << "intersection point at " << res.second<< endl; */
#include "base.cpp"
template<class P> pair<ll, P> lineInter(P s1, P e1, P s2, P e2) {
   auto d = (e1 - s1).cross(e2 - s2);
   if(d == 0)  // if parallel
      return {-(s1.cross(e1, s2) == 0), P(0, 0)};
   auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
   return {1, (s1 * p + e1 * q) / d};
}
/* Apply the linear transformation (translation, rotationandscaling) which takes line p0-p1 to line q0-q1 to point r. \
 */
using P = Point<double>;
P linearTransformation(P p0, P p1, P q0, P q1, P r) {
   P dp = p1 - p0, dq = q1 - q0, num(dp.cross(dq), dp.dot(dq));
   return q0 + P((r - p0).cross(num), (r - p0).dot(num)) / dp.dist2();
}
/* Returns the signed distance between point p and the linecontaining points a and b. Positive value on left side
 * andnegative on right as seen from a towards b. a==b gives nan. Pis supposed to be Point<T> or Point3D<T> where T is
 * e.g. doubleor long long. It uses products in intermediate steps so watchout for overflow if using int or long long.
 * Using Point3Dwillalways give a non-negative distance. For Point3D, call .distonthe result of the cross product. */
template<class P> double lineDist(const P& a, const P& b, const P& p) {
   return (double)(b - a).cross(p - a) / (b - a).dist();
}