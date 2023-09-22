#ifndef _POLYGON_H_
#define _POLYGON_H_

#include <vector>

#include "utilities.h"

// =============================================================================
class Polygon {
public:
  Polygon() { assert(false); }
  Polygon(const std::string &name, const std::vector<Point> &p) {
    assert(p.size() > 2); // check for making shapes with less than 3 points
    name_ = name;
    verts_ = p;
  }
  virtual ~Polygon() {}
  int NumVerts() { return verts_.size(); }
  std::string getName() { return name_; }
  virtual bool HasAllEqualSides();
  virtual bool HasrightAngle() { return false; }
  virtual bool HasEqualAngle() { return false; }

protected:
  std::string name_;
  std::vector<Point> verts_;
};

// =============================================================================
class Triangle : public Polygon {
public:
  Triangle() { assert(false); }
  Triangle(const std::string &name, const std::vector<Point> &p)
      : Polygon(name, p) {
    if (p.size() != 3)
      throw 1;
  }
  virtual bool HasAllEqualSides() { return false; }
  virtual bool HasrightAngle() { return false; }
  virtual bool HasEqualAngle() { return false; }
};

// =============================================================================
class IsoscelesTriangle : public Triangle {
public:
  IsoscelesTriangle() { assert(false); }
  IsoscelesTriangle(const std::string &name, const std::vector<Point> &p)
      : Triangle(name, p) {
    if (p.size() != 3)
      throw 1;
    if (!isIsoscelesTriangle(p[0], p[1], p[2]))
      throw 2;
  }
  virtual bool HasAllEqualSides() { return false; }
  virtual bool HasrightAngle() { return false; }
  virtual bool HasEqualAngle() {
    double angle = Angle(verts_[0], , verts_[1], verts_[2]);
    if (angle == 90) {
      return true;
    } else
      return false;
  }
  /* code */

private:
  bool isIsoscelesTriangle(const Point &p1, const Point &p2, const Point &p3);
};

// =============================================================================
class EquilateralTriangle : public IsoscelesTriangle {
public:
  EquilateralTriangle() { assert(false); }
  EquilateralTriangle(const std::string &name, const std::vector<Point> &p)
      : IsoscelesTriangle(name, p) {
    if (p.size() != 3)
      throw 1;
    if (!isEquilateralTriangle(p[0], p[1], p[2]))
      throw 2;
  }
  virtual bool HasAllEqualSides() { return true; }
  virtual bool HasrightAngle() { return false; }
  virtual bool HasEqualAngle() { return false; }

private:
  bool isEquilateralTriangle(const Point &p1, const Point &p2, const Point &p3);
};

// =============================================================================
class Quadrilateral : public Polygon {
public:
  Quadrilateral() { assert(false); }
  Quadrilateral(const std::string &name, const std::vector<Point> &p)
      : Polygon(name, p) {
    if (p.size() != 4)
      throw 1;
  }
  virtual bool HasAllEqualSides() { return false; }
  virtual bool HasrightAngle() { return false; }
  virtual bool HasEqualAngle() { return false; }
};

// =============================================================================
class Rectangle : public Quadrilateral {
public:
  Rectangle() { assert(false); }
  Rectangle(const std::string &name, const std::vector<Point> &p)
      : Quadrilateral(name, p) {
    if (p.size() != 4)
      throw 1;
    if (!isRectangle(p[0], p[1], p[2], p[3]))
      throw 2;
  }
  virtual bool HasAllEqualSides() { return false; }

private:
  bool isRectangle(const Point &p1, const Point &p2, const Point &p3,
                   const Point &p4);
};

// =============================================================================
class Square : public Rectangle {
public:
  Square() { assert(false); }
  Square(const std::string &name, const std::vector<Point> &p)
      : Rectangle(name, p) {
    if (p.size() != 4)
      throw 1;
    if (!isSquare(p[0], p[1], p[2], p[3]))
      throw 2;
  }

private:
  bool isSquare(const Point &p1, const Point &p2, const Point &p3,
                const Point &p4);
};

#endif
