#include <iostream>
void all_paths(int x, int y, int &total) {
  if (x == 0 && y == 0) {
    total += 1;
  }
  if (x - 1 >= 0) {
    all_paths(x - 1, y, total);
  }
  if (y - 1 >= 0) {
    all_paths(x, y - 1, total);
  } else {
    return;
  }
}

int main() {
  int total1 = 0;
  all_paths(1, 1, total1);
  std::cout << total1 << " total paths for (1, 1)\n" << std::endl;
  int total2 = 0;
  all_paths(2, 1, total2);
  std::cout << total2 << " total paths for (2, 1)\n" << std::endl;
  int total3 = 0;
  all_paths(2, 2, total3);
  std::cout << total3 << " total paths for (2, 2)\n" << std::endl;
  int total4 = 0;
  all_paths(2, 3, total4);
  std::cout << total4 << " total paths for (2, 3)\n" << std::endl;
  int total5 = 0;
  all_paths(10, 10, total5);
  std::cout << total5 << " total paths for (10,10)\n" << std::endl;
}
