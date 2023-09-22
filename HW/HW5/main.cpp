//
// NOTE: YOUR FINAL SUBMITTED VERSION SHOULD ONLY CONTAIN
//       CHANGES TO MoreTests()
//

#include <cassert>
#include <cmath>
#include <iostream>
#include <list>

#include "unrolled.h"

// ===================================================================
// This function compares an unrolled linked list to an STL list.  It
// returns true iff the lists are the same size, and contain the same
// elements in the same order.
template <class T> bool SAME(UnrolledLL<T> &a, std::list<T> &b) {
  if (a.size() != b.size())
    return false;
  typename UnrolledLL<T>::iterator a_iter = a.begin();
  typename std::list<T>::iterator b_iter = b.begin();
  while (a_iter != a.end() && b_iter != b.end()) {
    if (*a_iter != *b_iter)
      return false;
    a_iter++;
    b_iter++;
  }
  assert(a_iter == a.end() && b_iter == b.end());
  return true;
}

// ===================================================================
void BasicTests();
void MoreTests();

int main() {
  BasicTests();
  MoreTests();
  std::cout << "Finished MoreTests()" << std::endl;
}

// ===================================================================
// NOTE: Your internal data structure may be different (& thus print
// differently), depending on how you implement your internal member
// functions.  That's ok!
void BasicTests() {

  // make two matching list of integers, one using an unrolled list,
  // one using an STL list.  They should stay the "SAME" throughout
  // these tests.
  UnrolledLL<int> a;
  std::list<int> b;
  for (int i = 10; i < 30; ++i) {
    a.push_back(i);
    b.push_back(i);
  }

  // iterate through the integers and print them out
  std::cout << "the integers from 10->29" << std::endl;
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++) {
    std::cout << " " << *itr;
  }
  std::cout << std::endl << std::endl;
  assert(SAME(a, b));

  // use the output operator to print the underlying representation
  std::cout << "initial" << std::endl;
  a.print(std::cout);
  std::cout << std::endl;

  // testing some basic functions in the class
  std::cout << "some editing with pop & push" << std::endl;
  assert(a.size() == 20);
  assert(a.front() == 10);
  assert(a.back() == 29);
  a.pop_front();
  b.pop_front();
  assert(a.size() == 19);
  assert(a.front() == 11);
  a.pop_back();
  b.pop_back();
  assert(a.size() == 18);
  assert(a.back() == 28);
  a.print(std::cout);
  std::cout << std::endl;
  assert(SAME(a, b));

  // more editing
  std::cout << "more editing with pop & push" << std::endl;
  a.pop_front();
  a.pop_front();
  a.pop_front();
  a.pop_front();
  a.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  a.print(std::cout);
  a.pop_back();
  b.pop_back();
  a.print(std::cout);
  assert(a.size() == 12);
  assert(a.front() == 16);
  assert(a.back() == 27);
  a.push_front(90);
  a.push_front(91);
  a.push_front(92);
  a.push_front(93);
  b.push_front(90);
  b.push_front(91);
  b.push_front(92);
  b.push_front(93);
  a.print(std::cout);
  std::cout << std::endl;
  assert(a.size() == 16);
  assert(a.front() == 93);
  assert(SAME(a, b));

  // erase the multiples of 3
  std::cout << "erase the multiples of 3" << std::endl;
  UnrolledLL<int>::iterator a_iter = a.begin();
  while (a_iter != a.end()) {
    if (*a_iter % 3 == 0) {
      a_iter = a.erase(a_iter);
    } else {
      a_iter++;
    }
  }
  std::list<int>::iterator b_iter = b.begin();
  while (b_iter != b.end()) {
    if (*b_iter % 3 == 0) {
      b_iter = b.erase(b_iter);
    } else {
      b_iter++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert(a.size() == 10);
  assert(SAME(a, b));

  // inserting elements
  std::cout << "do some inserts" << std::endl;
  // insert some stuff
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++) {
    if (*itr == 92 || *itr == 16 || *itr == 19 || *itr == 26) {
      itr = a.insert(itr, 77);
      itr++;
    }
  }
  for (std::list<int>::iterator itr = b.begin(); itr != b.end(); itr++) {
    if (*itr == 92 || *itr == 16 || *itr == 19 || *itr == 26) {
      itr = b.insert(itr, 77);
      itr++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert(a.size() == 14);
  assert(SAME(a, b));

  // overflowing an insert
  std::cout << "insert that overflows the node" << std::endl;
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++) {
    if (*itr == 17) {
      itr = a.insert(itr, 88);
      itr++;
    }
  }
  for (std::list<int>::iterator itr = b.begin(); itr != b.end(); itr++) {
    if (*itr == 17) {
      itr = b.insert(itr, 88);
      itr++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert(a.size() == 15);
  assert(SAME(a, b));

  // more erasing
  std::cout << "erasing that removes a node" << std::endl;
  a_iter = a.begin();
  while (a_iter != a.end()) {
    if (*a_iter == 77 || *a_iter == 16 || *a_iter == 88) {
      a_iter = a.erase(a_iter);
    } else {
      a_iter++;
    }
  }
  b_iter = b.begin();
  while (b_iter != b.end()) {
    if (*b_iter == 77 || *b_iter == 16 || *b_iter == 88) {
      b_iter = b.erase(b_iter);
    } else {
      b_iter++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert(a.size() == 9);
  assert(SAME(a, b));
}

// ===================================================================
void MoreTests() {
  //
  //
  // ADD YOUR OWN TEST CASES HERE
  // ADD COMMENTS TO EXPLAIN THE PURPOSE OF THE TEST CASES
  // TEST CASES SHOULD FINISH AND NOT CRASH. OUTPUT IS HELPFUL AS WELL.
  //
  //
  std::cout << "simple tests start here:" << std::endl;
  UnrolledLL<int> a;
  UnrolledLL<int> b;
  a.push_back(1);
  b.push_back(1);

  std::cout << "delete the last element in the list using pop_back:"
            << std::endl;
  std::cout << "BEFORE: ";
  a.print(std::cout);
  a.pop_back();
  std::cout << "AFTER: ";
  a.print(std::cout);

  std::cout << "delete the last element in the list using pop_front:"
            << std::endl;
  std::cout << "BEFORE: ";
  b.print(std::cout);
  b.pop_front();
  std::cout << "AFTER: ";
  b.print(std::cout);

  std::cout << "Push front when first node is full:" << std::endl;
  for (int i = 0; i < 6; i++) {
    a.push_back(i);
  }
  std::cout << "BEFORE: ";
  a.print(std::cout);
  a.push_front(999);
  std::cout << "AFTER: ";
  a.print(std::cout);

  a.clear();
  typename UnrolledLL<int>::iterator a_iter = a.begin();
  typename UnrolledLL<int>::iterator b_iter1 = b.begin();
  std::cout << "Insert an element into empty list:" << std::endl;
  std::cout << "BEFORE: ";
  a.print(std::cout);
  a_iter = a.insert(a_iter, 5);
  std::cout << "AFTER: ";
  a.print(std::cout);

  std::cout << "Erase last element in the list:" << std::endl;
  b.push_back(10);
  std::cout << "BEFORE: ";
  b.print(std::cout);
  b_iter1 = b.erase(b_iter1);
  std::cout << "AFTER: ";
  b.print(std::cout);

  std::cout << "Erase last two elements in the list:" << std::endl;
  b.push_back(1);
  b.push_front(2);
  typename UnrolledLL<int>::iterator b_iter2 = b.begin();
  std::cout << "BEFORE: ";
  b.print(std::cout);
  while (b_iter2 != b.end()) {
    if (*b_iter2 == 1 || *b_iter2 == 2) {
      b_iter2 = b.erase(b_iter2);
    } else {
      b_iter2++;
    }
  }
  std::cout << "AFTER: ";
  b.print(std::cout);

  std::cout << "More tests starts here:" << std::endl;
  UnrolledLL<int> c;
  UnrolledLL<int> d;
  for (int i = 10; i < 30; ++i) {
    c.push_back(i);
    d.push_back(i);
  }

  std::cout << "Erase a node in the middle of the list:" << std::endl;
  std::cout << "BEFORE: ";
  c.print(std::cout);
  typename UnrolledLL<int>::iterator c_iter = c.begin();
  while (c_iter != c.end()) {
    if (*c_iter >= 16 && *c_iter <= 21) {
      c_iter = c.erase(c_iter);
    } else {
      c_iter++;
    }
  }
  std::cout << "AFTER: ";
  c.print(std::cout);

  std::cout << "Erase a node at the beginning of the list:" << std::endl;
  std::cout << "BEFORE: ";
  c.print(std::cout);
  c_iter = c.begin();
  while (c_iter != c.end()) {
    if (*c_iter >= 10 && *c_iter <= 15) {
      c_iter = c.erase(c_iter);
    } else {
      c_iter++;
    }
  }
  std::cout << "AFTER: ";
  c.print(std::cout);

  std::cout << "Erase a node at the end of the list:" << std::endl;
  std::cout << "BEFORE: ";
  c.print(std::cout);
  c_iter = c.begin();
  while (c_iter != c.end()) {
    if (*c_iter == 28 || *c_iter == 29) {
      c_iter = c.erase(c_iter);
    } else {
      c_iter++;
    }
  }
  std::cout << "AFTER: ";
  c.print(std::cout);

  std::cout << "Insert into the first position of the list:" << std::endl;
  typename UnrolledLL<int>::iterator d_iter1 = d.begin();
  for (int i = 1; i < 5; i++) {
    d.push_back(i);
  }
  std::cout << "BEFORE: ";
  d.print(std::cout);
  d.insert(d_iter1, 1);
  std::cout << "AFTER: ";
  d.print(std::cout);

  std::cout << "Insert into the last position of the list:" << std::endl;
  typename UnrolledLL<int>::iterator d_iter2 = d.begin();
  std::cout << "BEFORE: ";
  d.print(std::cout);
  for (unsigned int i = 0; i < d.size() - 1; i++) {
    d_iter2++;
  }
  d.insert(d_iter2, 999);
  std::cout << "AFTER: ";
  d.print(std::cout);

  std::cout << "Insert that will overflow the node:" << std::endl;
  typename UnrolledLL<int>::iterator d_iter3 = d.begin();
  while (d_iter3 != d.end()) {
    if (*d_iter3 == 2) {
      break;
    }
    d_iter3++;
  }
  std::cout << "BEFORE: ";
  d.print(std::cout);
  d.insert(d_iter2, 666);
  std::cout << "AFTER: ";
  d.print(std::cout);

  std::cout << "Test for copy constructor:" << std::endl;
  UnrolledLL<int> e(d);
  assert(e == d);
  std::cout << "Passed assert copy constructor test!" << std::endl;
  std::cout << '\n';
}
