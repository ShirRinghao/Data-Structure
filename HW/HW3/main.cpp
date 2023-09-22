// =======================================================
//
// IMPORTANT NOTE: Do not modify this file
//     (except to uncomment the provided test cases
//     and add your test cases where specified)
//
// =======================================================

#include "table.h"
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// helper testing functions
void SimpleTest();
void StudentTests();
void BatchTest(const char *filename, int num);
void ExtraCreditTests();

int main(int argc, char *argv[]) {
  if (argc == 1) {
    SimpleTest();
    std::cout << "Simple test completed." << std::endl;
    StudentTests();
    std::cout << "Student tests completed." << std::endl;

    //
    // uncomment if you have implemented the extra credit features
    //
    ExtraCreditTests();
    //

  } else {
    if (argc != 3) {
      std::cerr << "Usage: " << argv[0] << " <filename> <num_iters>"
                << std::endl;
      exit(1);
    }
    BatchTest(argv[1], atoi(argv[2]));
    std::cout << "Batch test completed." << std::endl;
  }
}

void SimpleTest() {

  // create a table with dimensions 2x5, where all entries are '.'
  Table<char> t(2, 5, '.');
  assert(t.get(0, 0) == '.');
  assert(t.get(1, 4) == '.');
  assert(t.get(1, 2) == '.');
  assert(t.numRows() == 2);
  assert(t.numColumns() == 5);
  t.print();
  std::cout << "constructor test completed" << std::endl;

  // intialize the values in the table
  t.set(0, 0, 'a');
  t.set(0, 1, 'b');
  t.set(0, 2, 'c');
  t.set(0, 3, 'd');
  t.set(0, 4, 'e');
  t.set(1, 0, 'f');
  t.set(1, 1, 'g');
  t.set(1, 2, 'h');
  t.set(1, 3, 'i');
  t.set(1, 4, 'j');
  assert(t.get(0, 0) == 'a');
  assert(t.get(1, 2) == 'h');
  assert(t.get(1, 4) == 'j');
  t.print();
  std::cout << "set & get tests completed" << std::endl;

  // =======================================================
  //
  //     UNCOMMENT THE SECTIONS BELOW AS YOU
  //        COMPLETE THE IMPLEMENTATION
  //
  // =======================================================

  std::vector<char> new_row;
  new_row.push_back('A');
  new_row.push_back('B');
  new_row.push_back('C');
  new_row.push_back('D');
  new_row.push_back('E');
  t.push_back_row(new_row);
  assert(t.numRows() == 3);
  assert(t.numColumns() == 5);
  t.print();
  std::cout << "add row test completed" << std::endl;

  // remove a column
  t.pop_back_column();
  assert(t.numRows() == 3);
  assert(t.numColumns() == 4);
  t.print();
  std::cout << "remove column test completed" << std::endl;

  // add a column
  std::vector<char> new_col;
  new_col.push_back('X');
  new_col.push_back('Y');
  new_col.push_back('Z');
  t.push_back_column(new_col);
  assert(t.numRows() == 3);
  assert(t.numColumns() == 5);
  t.print();
  std::cout << "add column test completed" << std::endl;

  // remove a row
  t.pop_back_row();
  assert(t.numRows() == 2);
  assert(t.numColumns() == 5);
  t.print();
  std::cout << "remove row test completed" << std::endl;

  // example of the copy constructor
  Table<char> another(t);
  // the structures initially look the same
  assert(t.numRows() == another.numRows());
  assert(t.numColumns() == another.numColumns());
  for (unsigned i = 0; i < t.numRows(); i++) {
    for (unsigned j = 0; j < t.numColumns(); j++) {
      assert(t.get(i, j) == another.get(i, j));
    }
  }
  // but future edits show they are different!
  another.set(1, 2, 'Q');
  assert(t.get(1, 2) != another.get(1, 2));
  std::vector<char> new_row2;
  new_row2.push_back('A');
  new_row2.push_back('B');
  new_row2.push_back('C');
  new_row2.push_back('D');
  new_row2.push_back('E');
  another.push_back_row(new_row2);
  assert(t.numRows() + 1 == another.numRows());
  assert(t.numColumns() == another.numColumns());
  t.print();
  another.print();
  std::cout << "copy constructor test completed" << std::endl;

  // example of the assignment operator
  t = another;
  // again the structures look the same
  assert(t.numRows() == another.numRows());
  assert(t.numColumns() == another.numColumns());
  for (unsigned i = 0; i < t.numRows(); i++) {
    for (unsigned j = 0; j < t.numColumns(); j++) {
      assert(t.get(i, j) == another.get(i, j));
    }
  }
  std::cout << "assignment operator test completed" << std::endl;

  // Note: The Table destructor is implicitly called for the
  //   stack-allocated variables 't' and 'another' when we leave the
  //   function and it goes out of scope.
}

void StudentTests() {

  // =======================================================
  //
  // YOU SHOULD ADD YOUR OWN TEST CASES HERE
  //
  // be sure to rigorously test:
  //   * tables that store types other than char
  //   * copy constructor
  //   * assignment operator
  //   * destructor
  //   * invalid requests (comment out for final submission)
  //
  // =======================================================

  // Test for int
  Table<int> x(2, 10, 0);
  assert(x.numRows() == 2);
  assert(x.numColumns() == 10);
  x.set(0, 0, 4);
  x.set(1, 9, 5);
  x.print();

  // Test for string

  Table<std::string> y(2, 10, "string");
  assert(y.numRows() == 2);
  assert(y.numColumns() == 10);
  y.set(0, 0, "start");
  y.set(1, 9, "end");
  y.print();

  // Test for char
  Table<char> z(2, 10, '.');
  assert(z.numRows() == 2);
  assert(z.numColumns() == 10);
  z.set(0, 0, 'a');
  z.set(1, 9, 'z');
  z.print();
  std::cout << "Test for table that contains different types completed"
            << std::endl;

  // Test for pop_back_row and pop_back_column function
  Table<int> a(5, 1, 0);
  assert(a.numRows() == 5);
  assert(a.numColumns() == 1);
  a.pop_back_column();
  a.print();

  Table<int> b(1, 5, 0);
  assert(b.numRows() == 1);
  assert(b.numColumns() == 5);
  b.pop_back_row();
  b.print();
  std::cout << "Test for pop last row and column completed" << std::endl;

  // Test for copy constructor
  Table<int> i(3, 3, 0);
  assert(i.numRows() == 3);
  assert(i.numColumns() == 3);
  Table<int> j(i);
  j.print();
  std::cout << "Test for copy constructor completed" << std::endl;

  // Test for opeartor=
  Table<int> h(4, 4, 0);
  h.print();
  h = i;
  h.print();
  std::cout << "Test for assignment operator= completed" << std::endl;

  // Test for extra credit operator[]
  Table<int> g(5, 5, 0);
  g.print();
  g[4][4] = 2;
  g.print();
  std::cout << "g[4][4] is: " << g[4][4] << std::endl;
  std::cout << "Test for assignment operator[] completed" << std::endl;

  // Test for destructor
  Table<int> k(5, 5, 0);
  k.print();
  std::cout << "Test for destructor completed (failed if there is memory leak)"
            << std::endl;

  // Test for empty table
  // Table<int> o;
  // o.print();
  // Test for invalid request
  // Table<int> d(4, 4, 0);
  // std::vector<int> col;
  // std::vector<int> row;
  // Table<int> e(2, 3, 0);
  // assert(d.numRows() == 4);
  // assert(d.numColumns() == 4);
  // d.push_back_row(row);
  // d.push_back_column(col);
  // d.set(0, 5, 5);
  // d.set(-2, 3, 5);
  // d.get(-1, 3);
  // std::cout << "Test for invalid requests completed" << std::endl;
  std::cout << "Student tests completed" << std::endl;
}

void ExtraCreditTests() {

  // =======================================================
  //
  //            UNCOMMENT THIS SECTION IF YOU
  //      COMPLETE THE EXTRA CREDIT IMPLEMENTATION
  //
  // =======================================================

  Table<char> x(2, 5, 'x');
  assert(x.numRows() == 2);
  assert(x.numColumns() == 5);
  x.set(0, 0, '.');
  x.set(1, 4, 'X');
  x.print();

  Table<char> y(4, 5, 'y');
  y.set(0, 0, '.');
  y.set(3, 4, 'Y');
  x.push_back_rows(y);
  assert(x.numRows() == 6);
  assert(x.numColumns() == 5);
  x.print();

  Table<char> z(6, 2, 'z');
  z.set(0, 0, '.');
  z.set(5, 1, 'Z');
  x.push_back_columns(z);
  assert(x.numRows() == 6);
  assert(x.numColumns() == 7);
  x.print();

  assert(x.get(0, 0) == '.');
  assert(x.get(1, 0) == 'x');
  assert(x.get(0, 1) == 'x');
  assert(x.get(1, 4) == 'X');

  assert(x.get(2, 0) == '.');
  assert(x.get(2, 1) == 'y');
  assert(x.get(3, 0) == 'y');
  assert(x.get(5, 4) == 'Y');

  assert(x.get(0, 5) == '.');
  assert(x.get(1, 5) == 'z');
  assert(x.get(0, 6) == 'z');
  assert(x.get(5, 6) == 'Z');

  std::cout << "extra credit tests completed" << std::endl;
}

// Batch test will repeatedly load & process a file with Table
// operations.  If the program's working memory does not grow when the
// program is run many, many times on a large test case, the data
// structure is probably free of memory leaks.
void BatchTest(const char *filename, int iters) {

  if (iters <= 0) {
    std::cerr << "ERROR: iters should be > 0" << std::endl;
    exit(1);
  }

  while (iters > 0) {
    iters--;

    // open the file stream for reading
    std::ifstream istr(filename);
    if (!istr) {
      std::cerr << "ERROR: cannot open file " << filename << std::endl;
      exit(1);
    }

    std::string token;
    char c;
    int i, j, num;

    // create the initial table
    istr >> token >> i >> j >> c;
    assert(token == "create");
    // note: here we explicitly allocate memory for the Table object
    Table<char> *table = new Table<char>(i, j, c);

    // read in and perform various operations on the array
    while (istr >> token) {
      if (token == "set") {
        istr >> i >> j >> c;
        table->set(i, j, c);
      } else if (token == "get") {
        istr >> i >> j >> c;
        char c2 = table->get(i, j);
        assert(c == c2);
      } else if (token == "push_back_row") {
        istr >> num;
        std::vector<char> tmp(num);
        for (int i = 0; i < num; i++)
          istr >> tmp[i];
        table->push_back_row(tmp);
      } else if (token == "push_back_column") {
        istr >> num;
        std::vector<char> tmp(num);
        for (int i = 0; i < num; i++)
          istr >> tmp[i];
        table->push_back_column(tmp);
      } else if (token == "pop_back_row") {
        table->pop_back_row();
      } else if (token == "pop_back_column") {
        table->pop_back_column();
      } else {
        std::cerr << "ERROR: unknown token " << token << std::endl;
        exit(1);
      }
    }

    if (iters == 0)
      table->print();

    // Because the Table memory was allocated explicitly (using new)
    // we need to explicitly deallocate the memory (using delete)
    delete table;
  }
}
