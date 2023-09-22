#include <cmath>
#include <iostream>
#include <list>

#include "dslist.h"

int main() {

  // =======================================
  // CHECKPOINT 1

  // create a list of the sqrt of the first 10 integers
  dslist<double> a;
  for (int i = 0; i < 10; ++i)
    a.push_back(sqrt(i));

  // print out details of the list
  assert(a.size() == 10);
  assert(a.front() == 0);
  assert(a.back() == 3);
  dslist<double>::iterator itr;
  std::cout << "Elements = ";
  for (itr = a.begin(); itr != a.end(); ++itr)
    std::cout << " " << *itr;
  std::cout << std::endl;

  // clear out the list
  a.clear();

  /*
  assert (a.size() == 0);
  */

  // simple tests of push_front, pop_front, and pop_back
  a.push_front(5);
  a.push_back(7);
  a.push_front(3);
  a.push_back(9);
  assert(a.size() == 4);

  assert(*(a.begin()) == 3);
  assert(*(++a.begin()) == 5);
  assert(*(++(++a.begin())) == 7);
  assert(*(++(++(++a.begin()))) == 9);

  std::cout << "Elements = ";
  for (itr = a.begin(); itr != a.end(); ++itr)
    std::cout << " " << *itr;
  std::cout << std::endl;

  a.pop_back();
  a.pop_front();
  assert(a.size() == 2);
  assert(*(a.begin()) == 5);
  assert(*(++a.begin()) == 7);

  std::cout << "Elements = ";
  for (itr = a.begin(); itr != a.end(); ++itr)
    std::cout << " " << *itr;
  std::cout << std::endl;

  a.pop_back();
  a.pop_front();
  assert(a.size() == 0);
  assert(a.begin() == a.end());

  // =======================================
  // CHECKPOINT 2

  // USING STL LIST
  std::list<int> b;
  for (int i = 0; i < 5; i++) {
    b.push_back(i);
  }

  // iterate backwards
  std::cout << "Elements: ";
  std::list<int>::iterator itr2 = b.end();
  while (itr2 != b.begin()) {
    itr2--;
    std::cout << " " << *itr2;
  }
  std::cout << std::endl;

  // USING DSLIST
  dslist<int> c;
  for (int i = 0; i < 5; i++) {
    c.push_back(i);
  }

  // iterate backwards
  std::cout << "Elements: ";
  dslist<int>::iterator itr3 = c.end();
  while (itr3 != c.begin()) {
    itr3--;
    std::cout << " " << *itr3;
  }
  std::cout << std::endl;

  // more stress tests of end() iterator with dslist

  // back & forth
  itr3 = c.end();
  itr3--;
  assert(*itr3 == 4);
  itr3++;
  assert(itr3 == c.end());

  // pop_back
  c.pop_back();
  itr3 = c.end();
  itr3--;
  assert(*itr3 == 3);

  // erase
  itr3 = c.erase(itr3);
  assert(itr3 == c.end());
  itr3--;
  assert(*itr3 == 2);

  assert(c.size() == 3);

  // iterate backwards again
  std::cout << "what's left: ";
  dslist<int>::iterator itr4 = c.end();
  while (itr4 != c.begin()) {
    itr4--;
    std::cout << " " << *itr4;
  }
  std::cout << std::endl;

  return 0;
}
