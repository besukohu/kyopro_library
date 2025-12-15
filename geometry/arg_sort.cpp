#include "base.cpp"
bool operator<(Point<ll> P, Point<ll> Q) {
   ll C = P.cross(Q);
   if(C == 0 && P.dot(Q) > 0) {
      return false;
   } else if(P.x < 0 && P.y == 0) {
      return true;
   } else if(Q.x < 0 && Q.y == 0) {
      return false;
   } else if(P.y * Q.y <= 0) {
      return P.y < Q.y;
   } else {
      return C > 0;
   }
}