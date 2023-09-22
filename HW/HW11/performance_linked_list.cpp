#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <list>
#include <string>

// defined in performance.cpp
void usage();

void list_test(const std::string *input_data, int input_count,
               const std::string &operation, std::string *output_data,
               int &output_count) {

  // HINT: declare your list like this:
  std::list<std::string> lst;
  output_count = input_count;
  // for all cases, simpy put the data into a list
  for (int i = 0; i < input_count; i++) {
    lst.push_back(input_data[i]);
  }

  if (operation == "sort") {
    // Use the list sort algorithm
    lst.sort();
    std::list<std::string>::iterator itr = lst.begin();
    for (int i = 0; itr != lst.end(); itr++, i++) {
      output_data[i] = *itr;
    }
  } else if (operation == "remove_dups_same_order") {
    // don't reorder the elements, just do all pairwise comparisons
    output_count = 0;
    std::list<std::string>::iterator itr = lst.begin();
    for (; itr != lst.end(); itr++) {
      bool dup = false;
      for (int j = 0; j < output_count; j++) {
        if (*itr == output_data[j]) {
          dup = true;
          break;
        }
      }
      // if it has not already been added to the output list
      if (!dup) {
        output_data[output_count] = *itr;
        output_count++;
      }
    }
  } else if (operation == "remove_dups_any_order") {
    // use the list sort algorithm
    output_count = 0;
    lst.sort();
    if (lst.empty()) {
      return;
    }
    // keep track of two pointers into the structure
    std::list<std::string>::iterator itr1 = lst.begin();
    std::list<std::string>::iterator itr2 = itr1;
    itr2++;
    for (; itr2 != lst.end(); itr2++) {
      if (*itr1 != *itr2) {
        // found a new item that has not been added into output_data
        output_data[output_count] = *itr1;
        output_count++;
      }
      itr1 = itr2;
    }
    // Last entry is a new item
    if (*itr1 != output_data[output_count - 1]) {
      output_data[output_count] = *itr1;
      output_count++;
    }
  } else if (operation == "mode") {
    // use the list sort algorithm
    lst.sort();
    int current_count = 1;
    std::string mode;
    int mode_count = 0;
    // keep track of two pointers into the structure
    std::list<std::string>::iterator curr = lst.begin();
    std::list<std::string>::iterator prev = lst.begin();
    curr++;
    for (; curr != lst.end(); ++curr, ++prev) {
      if (*curr == *prev) {
        // if they are the same increment the count
        current_count++;
      } else if (current_count >= mode_count) {
        // found a new mode!
        mode = *prev;
        mode_count = current_count;
        current_count = 1;
      } else {
        current_count = 1;
      }
    }
    if (current_count >= mode_count) {
      // last entry is a new mode!
      mode = *prev;
      mode_count = current_count;
    }
    // save the mode to the output vector
    output_count = 1;
    output_data[0] = mode;
  } else {
    std::cerr << "Error: Unknown operation: " << operation << std::endl;
    usage();
  }
}
