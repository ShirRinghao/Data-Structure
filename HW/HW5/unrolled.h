#ifndef unrolled_h_
#define unrolled_h_
#include <cassert>

const int NUM_ELEMENTS_PER_NODE = 6;

// -------------------------------------------------------------------------
// NODE CLASS
template <class T> class Node {
public:
  // Default constructor
  Node() : prev(NULL), num_elements(0), next(NULL) {}
  // Copy constructor
  Node(const Node<T> &old)
      : prev(NULL), num_elements(old.num_elements), next(NULL) {
    for (int i = 0; i < old.num_elements; i++) {
      elements[i] = old.elements[i];
    }
  }
  Node<T> *prev;
  int num_elements;
  T elements[NUM_ELEMENTS_PER_NODE];
  Node<T> *next;
};

template <class T> class UnrolledLL;
// -------------------------------------------------------------------------
// UnrolledLL ITERATOR CLASS

template <class T> class list_iterator {
public:
  // CONSTRUCTORS AND DECONSTRUCTOR
  list_iterator() : ptr(NULL), offset(-1) {}
  list_iterator(Node<T> *p) {
    if (p) {
      ptr = p;
      offset = 0;
    } else {
      // If it is at the end, change offset to -1 so the program could
      // recognize
      ptr = NULL;
      offset = -1;
    }
  }
  // Copy constructor
  list_iterator(const list_iterator<T> &old)
      : ptr(old.ptr), offset(old.offset) {}

  list_iterator<T> &operator=(const list_iterator<T> &old) {
    ptr = old.ptr;
    offset = old.offset;
    return *this;
  }
  ~list_iterator() {}

  T &operator*() { return ptr->elements[offset]; }

  list_iterator<T> &operator++() {
    // case 1: offset == -1, cerr
    if (offset == -1) {
      std::cerr << "ERROR: OUT OF BOUNDS!" << std::endl;
      exit(1);
    }

    // case 2: offset++, same node
    if (offset < ptr->num_elements - 1) {
      offset++;
    } else {
      // case 3: reach end of node, to next node and offset = 0
      // 	Note: if next node is NULL, then offset = -1
      ptr = ptr->next;
      if (ptr) {
        offset = 0;
      } else {
        // If it is the last node, reach the end, set offset to -1
        offset = -1;
      }
    }
    return *this;
  }

  list_iterator<T> &operator++(int) {
    // case 1: offset == -1, cerr
    if (offset == -1) {
      std::cerr << "ERROR: OUT OF BOUNDS!" << std::endl;
      exit(1);
    }
    list_iterator<T> temp(*this);
    // case 2: offset++, same node
    if (offset < ptr->num_elements - 1) {
      offset++;
    } else {
      // case 3: reach end of node, to next node and offset = 0
      // 	Note: if next node is NULL, then offset = -1
      ptr = ptr->next;
      if (ptr) {
        offset = 0;
      } else {
        // If it is the last node, reach the end, set offset to -1
        offset = -1;
      }
    }
    return temp;
  }

  list_iterator<T> &operator--() {
    // Case 1: one before first position, which should be invalid
    if (offset == -1) {
      std::cerr << "ERROR: ITERATOR FAILED AT DECREMENTS" << std::endl;
      exit(1);
    }
    // Case 2: at first position of the entire list
    if (offset == 0) {
      ptr = ptr->prev;
      if (ptr) {
        offset = ptr->num_elements - 1;
      } else {
        // If it is the last node, reach the end, set offset to -1
        offset = -1;
      }
    }
    // Case 3: in the middle of current array
    else {
      offset--;
    }
    return *this;
  }

  list_iterator<T> &operator--(int) {
    // Case 1: one before first position, which should be invalid
    if (offset == -1) {
      std::cerr << "ERROR: ITERATOR FAILED AT DECREMENTS" << std::endl;
      exit(1);
    }
    list_iterator<T> temp(*this);
    // Case 2: at first position of the entire list
    if (offset == 0) {
      ptr = ptr->prev;
      if (ptr) {
        offset = ptr->num_elements - 1;
      } else {
        // If it is the last node, reach the end, set offset to -1
        offset = -1;
      }
    }
    // Case 3: in the middle of current array
    else {
      offset--;
    }
    return temp;
  }

  // Unrolled ckass needs access to the private ptr member function
  friend class UnrolledLL<T>;

  // Comparison operators
  bool operator==(const list_iterator<T> &r) const {
    if ((!ptr || offset == -1) && (!r.ptr || r.offset == -1))
      return true;
    return ptr == r.ptr && offset == r.offset;
  }
  bool operator!=(const list_iterator<T> &r) const { return !operator==(r); }

private:
  Node<T> *ptr;
  int offset;
};

// -------------------------------------------------------------------------
// UnrolledLL CLASS
template <class T> class UnrolledLL {
public:
  // default constructor, copy constructor, assignment operator, destructor.
  UnrolledLL() : head(NULL), tail(NULL), size_(0) {}
  UnrolledLL(const UnrolledLL<T> &old) { this->copy_list(old); }
  UnrolledLL &operator=(const UnrolledLL<T> &old);
  ~UnrolledLL() { this->destroy_list(); }

  // simple accessors & modifiers
  unsigned int size() const { return size_; }
  bool empty() const { return head == NULL; }
  void clear() { return this->destroy_list(); }
  void print(std::ostream &out) const;

  // read/write access to contents
  const T &front() const { return head->elements[0]; }
  T &front() { return head->elements[0]; }
  const T &back() const { return tail->elements[tail->num_elements - 1]; }
  T &back() { return tail->elements[tail->num_elements - 1]; }

  // modify the linked list structure
  void push_front(const T &v);
  void pop_front();
  void push_back(const T &v);
  void pop_back();

  typedef list_iterator<T> iterator;
  iterator erase(iterator itr);
  iterator insert(iterator itr, const T &v);
  iterator begin() { return iterator(head); }
  iterator end() { return iterator(); }

private:
  // private helper functions
  void copy_list(const UnrolledLL<T> &old);
  void destroy_list();

  // representation
  Node<T> *head;
  Node<T> *tail;
  unsigned int size_;
};

// -------------------------------------------------------------------------
// List class implementation
template <class T>
UnrolledLL<T> &UnrolledLL<T>::operator=(const UnrolledLL<T> &old) {
  // check for self-assignment
  if (&old != this) {
    this->destroy_list();
    this->copy_list(old);
  }
  return *this;
}

template <class T> void UnrolledLL<T>::push_front(const T &v) {
  // Case 0: empty list
  if (head == NULL) {
    head = new Node<T>;
    tail = head;
  }
  // Case 1: current node is full, have to create a new node
  if (head->num_elements == NUM_ELEMENTS_PER_NODE) {
    Node<T> *tmp = head;
    head = new Node<T>;
    head->next = tmp;
    tmp->prev = head;
  }
  // normal case
  // for loop to shift all elements into next position, store v into first
  // position
  for (int i = head->num_elements; i > 0; i--) {
    head->elements[i] = head->elements[i - 1];
  }
  head->elements[0] = v;
  // increase size and num_elements
  head->num_elements++;
  size_++;
}

template <class T> void UnrolledLL<T>::push_back(const T &v) {
  // Case 1: UnrolledLL is empty
  if (head == NULL) {
    head = new Node<T>;
    tail = head;
  }
  // Case 2: UnrolledLL only has one node class and it is full
  else if (tail->num_elements == NUM_ELEMENTS_PER_NODE && head == tail) {
    Node<T> *tmp = new Node<T>;
    head->next = tmp;
    tmp->prev = head;
    tail = tmp;
  }
  // Case 3: Last Node size is full
  else if (tail->num_elements == NUM_ELEMENTS_PER_NODE) {
    Node<T> *tmp = new Node<T>;
    tail->next = tmp;
    tmp->prev = tail;
    tail = tmp;
  }
  tail->elements[tail->num_elements] = v;
  // increase size and num_elements
  tail->num_elements += 1;
  size_ += 1;
}

template <class T> void UnrolledLL<T>::pop_front() {
  if (head == NULL) {
    std::cerr << "ERROR! Trying to pop_front an empty list." << std::endl;
    exit(1);
  }
  // Case 1: only one element in the first node
  if (head->num_elements == 1) {
    // Case 1a: there is only one node and one element in the entire lists
    if (head->next == NULL) {
      delete head;
      head = NULL;
      tail = head;
    }
    // Case 1b: more than node node, but there is only one element in the
    // first node
    else {
      Node<T> *tmp = head;
      head = head->next;
      head->prev = NULL;
      delete tmp;
    }
  }
  // regular condition
  else {
    for (int i = 0; i < head->num_elements; i++) {
      head->elements[i] = head->elements[i + 1];
    }
    head->num_elements--;
  }
  size_--;
}

template <class T> void UnrolledLL<T>::pop_back() {
  if (head == NULL) {
    std::cerr << "ERROR! Trying to pop_front an empty list." << std::endl;
    exit(1);
  }
  if (tail->num_elements == 1) {
    // Case 1a: there is only one node and one element in the entire lists
    if (tail->prev == NULL) {
      delete tail;
      tail = NULL;
      head = tail;
    }
    // Case 1b: more than node node, but there is only one element in the
    // last node
    else {
      Node<T> *tmp = tail;
      tail = tail->prev;
      tail->next = NULL;
      delete tmp;
    }
  }
  // regular condition
  else {
    tail->num_elements--;
  }
  size_--;
}

// do these lists look the same (length & contents)?
template <class T> bool operator==(UnrolledLL<T> &left, UnrolledLL<T> &right) {
  // Check if they are the same size
  if (left.size() != right.size())
    return false;
  typename UnrolledLL<T>::iterator left_itr = left.begin();
  typename UnrolledLL<T>::iterator right_itr = right.begin();
  // walk over both lists, looking for a mismatched value
  while (left_itr != left.end()) {
    if (*left_itr != *right_itr)
      return false;
    left_itr++;
    right_itr++;
  }
  return true;
}
template <class T> bool operator!=(UnrolledLL<T> &left, UnrolledLL<T> &right) {
  return !(left == right);
}

template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::erase(iterator itr) {
  // Case 0: ERROR, when list is empty, or at the wrong location
  if (size_ == 0 && itr == end()) {
    std::cerr << "ERROR! Invalid location." << std::endl;
    exit(1);
  }

  // Case 1: erase the only element in list (size_ == 1)
  // 				Note: Node is deleted in this case
  if (size_ == 1) {
    delete head;
    head = tail = NULL;
    size_ = 0;
    return end();
  }
  // Case 2: erase the only element in node (num_elements == 1)
  // 				Note: Node is deleted in this case
  if (itr.ptr->num_elements == 1) {
    // Case 2a: erase the first node
    if (itr.ptr == head) {
      pop_front();
      itr = begin();
    }
    // Case 2b: erase the last node
    else if (itr.ptr == tail) {
      pop_back();
      itr = end();
    }
    // Case 2c: erase node in middle
    else {
      Node<T> *tmp = itr.ptr->next;
      tmp->prev = itr.ptr->prev;
      itr.ptr->prev->next = tmp;
      delete itr.ptr;
      itr.ptr = tmp;
      size_--;
    }
  }
  // Case 3: erase the last element in one node, switching itr to next node
  else if (itr.offset == itr.ptr->num_elements - 1) {
    itr.ptr->num_elements--;
    itr = iterator(itr.ptr->next);
    size_--;
  }
  // Case 4: normal case, erase in middle of node
  else {
    for (int i = itr.offset; i < itr.ptr->num_elements - 1; i++) {
      itr.ptr->elements[i] = itr.ptr->elements[i + 1];
    }
    itr.ptr->num_elements--;
    size_--;
  }
  return itr;
}

template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::insert(iterator itr,
                                                       const T &v) {
  // Special case when the list is intially empty
  if (head == NULL) {
    Node<T> *tmp = new Node<T>;
    head = tail = tmp;
    tmp->elements[0] = v;
    itr = begin();
  }
  // Case 0: ERROR, invalid location
  if (!itr.ptr) {
    std::cerr << "Invalid location to insert" << std::endl;
  }
  size_++;
  // Case 1: current node is full, create a new node
  if (itr.ptr->num_elements == NUM_ELEMENTS_PER_NODE) {
    // Case 1a: create a new node at the end
    if (itr.ptr == tail) {
      Node<T> *tmp = new Node<T>;
      itr.ptr->next = tmp;
      tmp->prev = tail;
      tail = tmp;
      tail->elements[0] = v;
    }
    // Case 1b: create a new node in the middle or before second node
    else {
      Node<T> *tmp = new Node<T>;
      itr.ptr->next->prev = tmp;
      tmp->prev = itr.ptr;
      tmp->next = itr.ptr->next;
      itr.ptr->next = tmp;
    }
    // 1c: current node is full, create a new node, shift all elements after
    // this location into the new array. change num_elements and
    // size_
    int move_element = NUM_ELEMENTS_PER_NODE - itr.offset;
    itr.ptr->next->num_elements = move_element;
    for (int i = 0; i < move_element; i++) {
      itr.ptr->next->elements[i] = itr.ptr->elements[itr.offset + i];
    }
    itr.ptr->num_elements -= move_element - 1;
    itr.ptr->elements[itr.offset] = v;
  }

  // normal case, shift each element forward by one.
  else {
    itr.ptr->num_elements++;
    for (int i = itr.ptr->num_elements - 1; i >= itr.offset; i--) {
      itr.ptr->elements[i] = itr.ptr->elements[i - 1];
    }
    itr.ptr->elements[itr.offset] = v;
  }
  return itr;
}

template <class T> void UnrolledLL<T>::copy_list(const UnrolledLL<T> &old) {
  size_ = old.size_;
  // Case1: list is empty
  if (old.empty()) {
    head = tail = NULL;
  } else {
    // Normal case, using loop to copy node in the list one by one
    head = new Node<T>(*(old.head));
    tail = head;
    Node<T> *temp = old.head->next;
    while (temp) {
      tail->next = new Node<T>(*temp);
      tail->next->prev = tail;
      tail = tail->next;
      temp = temp->next;
    }
  }
}

template <class T> void UnrolledLL<T>::destroy_list() {
  // Using while loop to delete node one by one in the list
  Node<T> *tmp = head;
  while (tmp) {
    tmp = tmp->next;
    delete head;
    head = tmp;
  }
  head = tail = NULL;
  size_ = 0;
}

template <class T> void UnrolledLL<T>::print(std::ostream &out) const {
  out << "UnrolledLL, size: " << this->size() << '\n';
  // For loop prints out all elements in each node in the list one by one
  for (Node<T> *curr = head; curr != NULL; curr = curr->next) {
    out << "node:[" << curr->num_elements << "]";
    for (int i = 0; i < curr->num_elements; i++) {
      out << " " << (curr->elements)[i];
    }
    out << '\n';
  }
  out << '\n';
}

#endif
