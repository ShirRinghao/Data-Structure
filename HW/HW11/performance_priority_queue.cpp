#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>

// defined in performance.cpp
void usage();

void priority_queue_test(const std::string *input_data, int input_count,
                         const std::string &operation, std::string *output_data,
                         int &output_count) {

  // HINT: declare your priority_queue like this:
  // std::priority_queue<std::string,std::vector<std::string> >
  // pq(input_data,input_data+input_count);
  std::priority_queue<std::string, std::vector<std::string>,
                      std::greater<std::string>>
      pq(input_data, input_data + input_count);
  output_count = input_count;

  // All data has been sorted from smallest to biggest once we have created the
  // priorty queue
  if (operation == "sort") {
    // Going through the priority_queue
    for (int i = 0; i < input_count; i++) {
      // top element in the queue is the current smallest number in the queue,
      // save it to the output_data, call pop to delete it so that we can access
      // next element
      output_data[i] = pq.top();
      pq.pop();
    }
  }
  // Cannot do remove duplicates in the same order operation
  else if (operation == "remove_dups_same_order") {
  }
  // Since everything has already been sorted in the priorty queue, we just need
  // to check whether the current item and previous item are the same, if
  // not, then we should add them into output_data
  else if (operation == "remove_dups_any_order") {
    output_count = 1;
    // set prev item to the first element, and add it into output_data
    std::string prev = pq.top();
    output_data[0] = prev;
    // remove the first element
    pq.pop();
    // Loop that goes through entire priority queue
    for (int i = 0; i < input_count - 1; i++) {
      // Get the current smallest element
      std::string curr = pq.top();
      // If prev and curr are two different string, then add curr into
      // output_data since this is the first time it occurs
      if (curr != prev) {
        output_data[output_count] = curr;
        output_count++;
      }
      // update prev and remove the top element
      prev = curr;
      pq.pop();
    }
  }
  // same strategy as remove duplicats, but now we have to count how many times
  // a string has occured.
  else if (operation == "mode") {
    int mode_count = 1;
    int most_mode = 1;
    // set mode to the first element in the queue
    std::string prev = pq.top();
    std::string mode_string = prev;
    pq.pop();
    // Loop that goes through the queue
    for (int i = 0; i < input_count - 1; i++) {
      // Get the current smallest item
      std::string curr = pq.top();
      // If the curr and prev are the same, which means an item has occured more
      // than once, increment its mode count
      if (curr == prev) {
        mode_count++;
      } else {
        // If a new element is caught
        // check if previous element has a larger mode number then current most
        // mode number
        if (mode_count > most_mode) {
          // If so, update mode
          mode_string = prev;
          most_mode = mode_count;
        }
        // Set the mode count to 1 since a new element is caught
        mode_count = 1;
      }
      // Update the queue and prev string
      prev = curr;
      pq.pop();
    }
    // Output the mode
    output_count = 1;
    output_data[0] = mode_string;
  } else {
    std::cerr << "Error: Unknown operation: " << operation << std::endl;
    usage();
  }
}
