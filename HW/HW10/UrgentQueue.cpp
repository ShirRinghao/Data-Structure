#include "Job.h"

// Function that sort a vector from last index to first index
void UrgentQueue::percolate_up() {
  // Using loop to go up the vector
  for (unsigned int child = heap.size() - 1; child > 0;) {
    // For each location, check it's parents if they are in the right position
    int parent = (child - 1) / 2;
    // If parent is smaller than parent, swap them, then update their new hook
    if (heap[child]->getPriority() > heap[parent]->getPriority()) {
      Job *tmp = heap[child];
      heap[child] = heap[parent];
      heap[parent] = tmp;
      heap[child]->urgent_hook = child;
      heap[parent]->urgent_hook = parent;
      child = parent;
    }
    // Check next index
    else {
      child--;
    }
  }
}

// Function that checks from a given index until the end of the vector to see if
// all Jobs are in the correct order
void UrgentQueue::percolate_down(int parent) {
  // Using loop to go down the vector
  while ((parent * 2) + 1 < (int)heap.size()) {
    // find the index of its children
    int left_child = (parent * 2) + 1;
    int right_child = left_child + 1;
    int swap = parent;
    // first checking left child is in the right location
    if (heap[swap]->getPriority() < heap[left_child]->getPriority()) {
      swap = left_child;
    }
    // Then check the right child
    if (right_child < (int)heap.size() &&
        heap[swap]->getPriority() < heap[right_child]->getPriority()) {
      swap = right_child;
    }
    // If they are not in the right order, swap two to make them right, then
    // update their new hook
    if (swap != parent) {
      Job *tmp = heap[parent];
      heap[parent] = heap[swap];
      heap[swap] = tmp;
      heap[parent]->urgent_hook = parent;
      heap[swap]->urgent_hook = swap;
      parent = swap;
    } else {
      break;
    }
  }
}

// Function that delete first item in the vector
Job *UrgentQueue::pop() {
  // First swap first item with the last item, update their hook
  Job *tmp = heap[0];
  heap[0] = heap[heap.size() - 1];
  heap[0]->urgent_hook = 0;
  // Them delete that item, rearrange them if we need to
  heap.pop_back();
  percolate_down(0);
  return tmp;
}

// Function that adds a job pointer into the vector
void UrgentQueue::push(Job *job) {
  heap.push_back(job);
  // update its hook and pointer
  heap[heap.size() - 1]->urgent_hook = heap.size() - 1;
  job->priority_ptr = this;
  // check if it is in the correct location
  percolate_up();
}

// Function that removes a job from a specific location in a vector
void UrgentQueue::remove_from_index(uq_hook hook) {
  // first swap this location with last item in the vector, update their hook
  heap[hook] = heap[heap.size() - 1];
  heap[hook]->urgent_hook = hook;
  // Delete the job we initally want to delete
  heap.pop_back();
  // Check now if all jobs in the vector are in the correct location
  percolate_down(hook);
}

// Function that prints out the vector size and all jobs in the vector
void UrgentQueue::printHeap(std::ostream &out) {
  out << "UQ " << heap.size() << " jobs:" << std::endl;
  for (unsigned int i = 0; i < heap.size(); i++) {
    out << "\t" << heap[i];
  }
}
