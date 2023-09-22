#ifndef __URGENTQ_H_
#define __URGENTQ_H_
// You can change/add to these #includes
#include <ctime>
#include <ostream>
#include <vector>

// Used to point to a location in the heap, fill in the "???"
typedef int uq_hook;

// Forward declaration of Job class, do not remove this line, do not change.
class Job;

// Promise to declare stream output operator for internal vector heap
// representation
std::ostream &operator<<(std::ostream &out, const std::vector<Job *> &heap);

class UrgentQueue {

  //////////FILL THIS IN///////////
public:
  // Sort functions
  void percolate_up();
  void percolate_down(int index);

  // Get first item in the vector
  Job *top() { return heap[0]; }
  // Delete last item in the vector
  Job *pop();
  // Add a item into a vector
  void push(Job *job);
  // Remove an item from an index
  void remove_from_index(uq_hook hook);
  // Results print function
  void printHeap(std::ostream &out);

private:
  std::vector<Job *> heap;
};

#endif
