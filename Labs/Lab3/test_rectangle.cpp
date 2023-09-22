#include "Rectangle.h"
#include <iostream>
#include <vector>
int main() {

  Rectangle one(Point2D(1, 5), Point2D(5, 10));
  Rectangle two(Point2D(4, 10), Point2D(6, 20));
  std::vector<Point2D> allpoints = points_in_both(one, two);
  for (unsigned int i = 0; i < allpoints.size(); i++) {
    std::cout << "points in both:" << allpoints[i].x() << ','
              << allpoints[i].y() << std::endl;
  }
  std::cout << "If point is within: " << one.is_point_within(Point2D(3, 3))
            << std::endl;
  std::cout << "IF the point is within: " << one.add_point(Point2D(6, 6))
            << std::endl;
  print_rectangle(one);
  print_rectangle(two);
  return 0;
}
