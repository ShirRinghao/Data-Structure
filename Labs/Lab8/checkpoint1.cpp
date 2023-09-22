#include <fstream>
#include <iostream>
#include <map>
int main(int argc, char *argv[]) {
  std::ifstream infile(argv[1]);
  int curr;
  std::map<int, int> counters;
  while (infile >> curr) {
    ++counters[curr];
  }
  std::map<int, int>::iterator itr1 = counters.begin();
  std::map<int, int>::iterator itr2 = counters.begin();
  int mode = 0;
  for (; itr1 != counters.end(); itr1++) {
    if (itr1->second > mode) {
      mode = itr1->second;
    }
  }
  for (; itr2 != counters.end(); itr2++) {
    if (itr2->second == mode) {
      std::cout << "Mode is " << itr2->first << std::endl;
    }
  }
  return 0;
}
