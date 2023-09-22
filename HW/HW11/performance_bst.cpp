#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>

// defined in performance.cpp
void usage();

void bst_test(const std::string *input_data, int input_count,
              const std::string &operation, std::string *output_data,
              int &output_count) {

  // HINT: declare your binary search tree (BST) like this:
  // std::set<std::string> st;
  // OR
  // std::map<std::string,int> mp;
  std::map<std::string, int> mp;
  // If the operation is remove dups same order, then we have to treat it
  // differently
  if (operation != "remove_dups_same_order") {
    for (int i = 0; i < input_count; i++) {
      if (mp.insert(make_pair(input_data[i], 1)).second == false) {
        mp[input_data[i]]++;
      }
    }
  }

  // Map will automatically sort all items in it, we just need to insert them
  if (operation == "sort") {
    typename std::map<std::string, int>::iterator itr = mp.begin();
    output_count = input_count;
    for (int i = 0; itr != mp.end(); itr++) {
      // If int is bigger than 1, then it has occured more than once, add each
      // copy into output_data
      for (int j = 0; j < itr->second; j++, i++) {
        output_data[i] = itr->first;
      }
    }
  }
  // We will have to check if each item has been inserted during the input since
  // we want to keep it in order
  else if (operation == "remove_dups_same_order") {
    output_count = 0;
    // Using for loop to go through all input data
    for (int i = 0; i < input_count; i++) {
      // First try to insert it
      // Case1: If we cannot insert it into map, which means it has already been
      // inserted, continue the loop
      if (mp.insert(std::make_pair(input_data[i], 1)).second == false) {
        continue;
      }
      // Case2: If we can insert it, then the item has only been seen once, add
      // it to output data, increment output_count
      else {
        output_data[output_count] = input_data[i];
        output_count++;
      }
    }
  }
  // Go through the map once to add all items in the map into
  // output_data
  else if (operation == "remove_dups_any_order") {
    typename std::map<std::string, int>::iterator itr = mp.begin();
    output_count = 0;
    for (int i = 0; itr != mp.end(); itr++, i++) {
      output_data[i] = itr->first;
      output_count++;
    }
  }
  // int value in the map represents how many times a string has occured in the
  // map, we just need to find the string with largest int value, that will be
  // the mode
  else if (operation == "mode") {
    typename std::map<std::string, int>::iterator itr = mp.begin();
    // set mode and mode number to the first element in the map
    std::string mode = itr->first;
    int mode_num = itr->second;
    // Go through entire map to find the string that has largest int value
    for (; itr != mp.end(); itr++) {
      if (itr->second > mode_num) {
        mode = itr->first;
        mode_num = itr->second;
      }
    }
    output_count = 1;
    output_data[0] = mode;
  } else {
    std::cerr << "Error: Unknown operation: " << operation << std::endl;
    usage();
  }
}
