#include <fstream>
#include <iostream>
#include <map>

int main(int argc, char const *argv[]) {
  std::ifstream infile(argv[1]);
  int curr;
  std::map<int, int> counters;
  while (infile >> curr) {
    std::map<int, int>::iterator itr = counters.find(curr);
    if (itr == counters.end()) {
      counters.insert(std::make_pair(curr, 1));
    } else {
      itr->second++;
    }
  }
  // write the words and associated counts
  std::map<int, int>::iterator it;
  std::map<int, int>::iterator it2 = it;
  int mode = 0;
  for (it = counters.begin(); it != counters.end(); ++it) {
    if (it->second > mode) {
      mode = it->second;
    };
  }
  for (it2 = counters.begin(); it2 != counters.end(); ++it2) {
    if (it2->second == mode) {
      std::cout << "mode is " << it2->first << std::endl;
    }
  }
  return 0;
}
