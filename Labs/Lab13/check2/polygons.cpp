#include "polygons.h"


bool Polygon::HasAllEqualSides() {
  double side = DistanceBetween(verts_[0], verts_[1]);
  for (unsigned int i = 2; i < verts_.size(); i++) {
    if (!EqualSides(side, DistanceBetween(verts_[i-1], verts_[i]))) return false;
  }
  return true;
}

bool IsoscelesTriangle::isIsoscelesTriangle(const Point& p1, const Point& p2, const Point& p3) {
  double side_a = DistanceBetween(p1, p2);
  double side_b = DistanceBetween(p1, p3);
  double side_c = DistanceBetween(p2, p3);
  if (EqualSides(side_a, side_b)) return true;
  if (EqualSides(side_a, side_c)) return true;
  if (EqualSides(side_b, side_c)) return true;
  return false;
}

bool EquilateralTriangle::isEquilateralTriangle(const Point& p1, const Point& p2, const Point& p3) {
  double side_a = DistanceBetween(p1, p2);
  double side_b = DistanceBetween(p1, p3);
  double side_c = DistanceBetween(p2, p3);
  if (EqualSides(side_a, side_b) && EqualSides(side_a, side_c)) return true;
  return false;
}

bool Rectangle::isRectangle(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
  Point cm((p1.x+p2.x+p3.x+p4.x)/4, (p1.y+p2.y+p3.y+p4.y)/4);
  double dist_a = DistanceBetween(cm, p1);
  double dist_b = DistanceBetween(cm, p2);
  double dist_c = DistanceBetween(cm, p3);
  double dist_d = DistanceBetween(cm, p4);
  return dist_a == dist_b && dist_a == dist_c && dist_a == dist_d;
}

bool Square::isSquare(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
  double side_a = DistanceBetween(p1, p2);
  double side_b = DistanceBetween(p1, p3);
  double side_c = DistanceBetween(p1, p4);
  if (EqualSides(side_a, side_b) && EqualSides((sqrt(2) * side_a), side_c) && EqualSides((sqrt(2) * side_a), DistanceBetween(p2, p3))) {
    double side_d = DistanceBetween(p2, p4);
    return (EqualSides(side_d, DistanceBetween(p3, p4)) && EqualSides(side_d, side_a));
  }
  if (EqualSides(side_a, side_c) && EqualSides((sqrt(2) * side_a), side_b) && EqualSides((sqrt(2) * side_a), DistanceBetween(p2, p4))) {
    double side_d = DistanceBetween(p2, p3);
    return (EqualSides(side_d, DistanceBetween(p3, p4)) && EqualSides(side_d, side_a));
  }
  if (EqualSides(side_b, side_c) && EqualSides((sqrt(2) * side_b), side_a) && EqualSides((sqrt(2) * side_b), DistanceBetween(p3, p4))) {
    double side_d = DistanceBetween(p2, p3);
    return (EqualSides(side_d, DistanceBetween(p2, p4)) && EqualSides(side_d, side_c));
  }
  return false;
}
