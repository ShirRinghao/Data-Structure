#ifndef priority_queue_h_
#define priority_queue_h_

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

template <class T> class priority_queue {
private:
  std::vector<T> m_heap;

  void percolate_up() {
    for (unsigned int child = m_heap.size() - 1; child > 0;) {
      int parent = (child - 1) / 2;
      if (m_heap[child] < m_heap[parent]) {
        T tmp = m_heap[child];
        m_heap[child] = m_heap[parent];
        m_heap[parent] = tmp;
        child = parent;
      } else {
        child--;
      }
    }
  }

  void percolate_down() {
    int parent = 0;
    while ((parent * 2) + 1 < (int)m_heap.size()) {
      int left_child = (parent * 2) + 1;
      int right_child = left_child + 1;
      int swap = parent;
      if (m_heap[swap] > m_heap[left_child]) {
        swap = left_child;
      }
      if (right_child < (int)m_heap.size() &&
          m_heap[swap] > m_heap[right_child]) {
        swap = right_child;
      }
      if (swap != parent) {
        T tmp = m_heap[parent];
        m_heap[parent] = m_heap[swap];
        m_heap[swap] = tmp;
        parent = swap;
      } else {
        parent++;
      }
    }
  }

public:
  priority_queue() {}

  priority_queue(std::vector<T> const &values) {
    m_heap = values;
    while (!check_heap(m_heap)) {
      percolate_down();
    }
  }

  const T &top() const {
    assert(!m_heap.empty());
    return m_heap[0];
  }

  void push(const T &entry) {
    m_heap.push_back(entry);
    percolate_up();
  }

  void pop() {
    assert(!m_heap.empty());
    m_heap.erase(m_heap.begin());
    percolate_down();
  }

  int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }

  //  The following three functions are used for debugging.

  //  Check to see that internally the heap property is realized.
  bool check_heap() { return this->check_heap(this->m_heap); }

  //  Check an external vector to see that the heap property is realized.
  bool check_heap(const std::vector<T> &heap) {
    if (heap.size() == 0)
      return true;
    for (unsigned int i = 0; i < heap.size(); ++i) {
      if ((2 * i + 1) < heap.size() && heap[2 * i + 1] < heap[i]) {
        return false;
      } else if ((2 * i + 2) < heap.size() && heap[2 * i + 2] < heap[i]) {
        return false;
      }
    }
    return true;
  }

  //  A utility to print the contents of the heap.  Use it for debugging.
  void print_heap(std::ostream &ostr) {
    for (unsigned int i = 0; i < m_heap.size(); ++i)
      ostr << i << ": " << m_heap[i] << std::endl;
  }
};

template <class T> void max_heap(std::vector<T> &v, int begin, int end) {
  int parent = begin;
  int child = 2 * parent + 1;
  while (child < end) {
    // right
    if (child + 1 < end && v[child] < v[child + 1]) {
      child += 1;
    }
    if (v[parent] < v[child]) {
      std::swap(v[parent], v[child]);
      parent = child;
      child = 2 * parent + 1;
    } else {
      break;
    }
  }
}

template <class T> void heap_sort(std::vector<T> &v) {
  int size = v.size();
  int first = (size - 1);

  for (int i = first; i >= 0; i--) {
    max_heap(v, i, size);
  }
  for (int i = size - 1; i >= 0; i--) {
    std::swap(v[0], v[i]);
    max_heap(v, 0, i);
  }
}
// template <class T> void heap_sort(std::vector<T> &v) {
//   priority_queue<T> temp_heap(v);
//   v.clear();
//   while (!temp_heap.empty()) {
//     v.push_back(temp_heap.top());
//     temp_heap.pop();
//   }
// }

#endif
