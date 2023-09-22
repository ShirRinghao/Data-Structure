#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

// defined in performance.cpp
void usage();

void hash_table_test(const std::string *input_data, int input_count,
                     const std::string &operation, std::string *output_data,
                     int &output_count) {

  // HINT: declare your hash table like this:
  // std::unordered_set<std::string> ht(input_count);
  // OR
  // std::unordered_map<std::string,int> ht(input_count);

  std::unordered_map<std::string, int> ht(input_count);
  output_count = input_count;
  // If the operation is remove dups same order, then we have to treat it
  // differently
  if (operation != "remove_dups_same_order") {
    for (int i = 0; i < input_count; i++) {
      if (ht.insert(make_pair(input_data[i], 1)).second == false) {
        ht[input_data[i]]++;
      }
    }
  }

  // cannot do sort in hash table
  if (operation == "sort") {
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
      if ((ht.insert(std::make_pair(input_data[i], 1))).second == false) {
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
    typename std::unordered_map<std::string, int>::iterator itr = ht.begin();
    output_count = 0;
    for (; itr != ht.end(); itr++) {
      if (itr->first != "") {
        output_data[output_count] = itr->first;
        output_count++;
      }
    }
  }
  // int value in the map represents how many times a string has occured in the
  // map, we just need to find the string with largest int value, that will be
  // the mode
  else if (operation == "mode") {
    std::unordered_map<std::string, int>::iterator itr = ht.begin();
    // set mode and mode number to the first element in the map
    std::string mode = itr->first;
    int mode_num = itr->second;
    // Go through entire map to find the string that has largest int value
    for (; itr != ht.end(); itr++) {
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
