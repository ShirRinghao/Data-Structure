/*
Write your Rope implementation in this file.
You do not have to keep any of the code that is already in this file.
Functions that are required that you have not implemented have an assert 0
meaning they will always crash. This should help you make sure you implement
everything.
*/

#include "Rope.h"
#include <cassert>

// Should advance to the next Node using in-order traversal
// It can point at any Node, not just leaves
// Function moves iterator to point to the next node in increasing order in the
// current rope
rope_iterator &rope_iterator::operator++() {
  // Find the leftmost child of the right node
  if (ptr_->right != NULL) {
    ptr_ = ptr_->right;
    while (ptr_->left != NULL) {
      ptr_ = ptr_->left;
    }
  }
  // go upwards along right branches... stop after the first left
  else {
    while (ptr_->parent != NULL && ptr_->parent->right == ptr_) {
      ptr_ = ptr_->parent;
    }
    ptr_ = ptr_->parent;
  }
  return *this;
}

// Point to the first Node for in-order traversal
rope_iterator Rope::begin() const {
  if (!root) {
    return NULL;
  }
  Node *p = root;
  // Using loop to find left most child in the rope
  while (p->left) {
    p = p->left;
  }
  return p;
}

// Default constructor
Rope::Rope() {
  root = NULL;
  size_ = 0;
}

// Should make the root = p and adjust any member variables
// This should not make a copy of the rope with root at p,
// it should just "steal" the Node*
Rope::Rope(Node *p) {
  // Making this node become new root
  root = p;
  // Using loop to add everything on the right hand side to root's weight.
  size_ = p->weight;
  while (p->right) {
    size_ += p->right->weight;
    p = p->right;
  }
}

// Default destructor
Rope::~Rope() {
  if (root != 0) {
    this->destroy_tree(root);
  }
}

// Void function that recursively delete a rope
void Rope::destroy_tree(Node *p) {
  // Nothing left on the rope, set it's size to 0, then return
  if (!p) {
    size_ = 0;
    return;
  }
  // First delete everything on the left hand side
  destroy_tree(p->left);
  // Then delete everything on the right hand side
  destroy_tree(p->right);
  // delete itself
  delete p;
  // set this pointer to NULL
  p = NULL;
}

// Function that takes in the old root and recursively copy that rope
Node *copy_tree(Node *old_root) {
  // Make a new root
  Node *new_root = new Node(old_root->weight);
  // If the rope is empty, then set it to NULL
  if (!old_root) {
    new_root = NULL;
  }
  // Copy the rope using helper function
  else {
    copy_helper(old_root, new_root);
  }
  // return the new new_root
  return new_root;
}

void copy_helper(Node *old_root, Node *curr) {
  // Basic case: have copied all the leaves in the current branch
  if (!old_root) {
    old_root = NULL;
    return;
  }
  // Copy all nodes on the right side, change their weight and parent pointer
  if (old_root->right) {
    Node *tmp = new Node(old_root->right->weight);
    tmp->value = old_root->right->value;
    curr->right = tmp;
    tmp->parent = curr;
    copy_helper(old_root->right, curr->right);
  }
  // Copy all nodes on the left side, change their weight and parent pointer.
  if (old_root->left) {
    Node *tmp = new Node(old_root->left->weight);
    tmp->value = old_root->left->value;
    curr->left = tmp;
    tmp->parent = curr;
    copy_helper(old_root->left, curr->left);
  }
  return;
}

// Decault copy constructor
Rope::Rope(const Rope &r) {
  // Copy the size and all nodes
  size_ = r.size_;
  root = copy_tree(r.root);
}

// Assignment operator
Rope &Rope::operator=(const Rope &r) {
  // special case: assigning an empty role
  if (r.root == NULL) {
    this->destroy_tree(root);
    size_ = 0;
    root = NULL;
    return *this;
  }
  // If two ropes are not the same, first destroy the tree, than copy new tree
  // using copy constructor
  if (&r != this) {
    if (root != NULL) {
      this->destroy_tree(root);
    }
    root = copy_tree(r.root);
    size_ = r.size_;
  }
  return *this;
}

// MUST BE ITERATIVE
// Get a single character at index i
bool Rope::index(int i, char &c) const {
  // Invalid index search, return false
  if (i >= size_) {
    return false;
  }
  Node *tmp = root;
  // using loop to find the correct node
  while (tmp != NULL) {
    if (tmp->left == NULL && tmp->right == NULL) {
      // At correct leaf, break the loop
      break;
    }
    // If i is smaller than current weight, then it must go left
    if (i < tmp->weight) {
      tmp = tmp->left;
    }
    // If i is bigger than current weight, then it must go right
    else if (i >= tmp->weight) {
      i -= tmp->weight;
      tmp = tmp->right;
    }
  }
  // Found the char, return true
  c = (tmp->value)[i];
  return true;
}

// Add the other rope (r)'s string to the end of my string
void Rope::concat(const Rope &r) {
  // If the rope is empty, return
  if (r.root == NULL) {
    return;
  }
  // Make a new root first, change its left and right pointer to two old roots
  Node *new_root = new Node;
  new_root->left = root;
  // Copy rope using copy function
  new_root->right = copy_tree(r.root);
  // Change root left and right pointer's parent pointer
  root->parent = new_root;
  new_root->right->parent = new_root;
  // Set its size
  new_root->weight = size_;
  // Using loop to add all weights on the right hand side to size_
  Node *tmp = new_root->right;
  size_ += tmp->weight;
  while (tmp->right) {
    tmp = tmp->right;
    size_ += tmp->weight;
  }
  // set new_root to root
  root = new_root;
}

// Get a substring from index i to index j.
// Includes both the characters at index i and at index j.
// String can be one character if i and j match
// Returns true if a string was returned, and false otherwise
// Function should be written with efficient running time.
bool Rope::report(int i, int j, std::string &s) const {
  // Invalid report, return false
  if (j >= size_ || j < i || i >= size_) {
    return false;
  }
  s = "";
  // Similiar to index, use the same code to find the first character we need
  Node *tmp = root;
  int start_loc = i;
  while (tmp != NULL) {
    if (tmp->left == NULL && tmp->right == NULL) {
      break;
    }
    if (i < tmp->weight) {
      tmp = tmp->left;
    } else if (i >= tmp->weight) {
      i -= tmp->weight;
      tmp = tmp->right;
    }
  }
  // First character is found
  // Using for loop to add any characters we need until we reach the end of
  // current node
  for (; i < tmp->weight && (int)s.size() < j - i + 1; i++) {
    s += (tmp->value)[i];
  }
  // then use operator++ on iterator to find the nodes that contain next few
  // characters we need until index j
  if ((int)s.size() < (j - start_loc + 1)) {
    rope_iterator itr = tmp;
    while ((int)s.size() < (j - start_loc + 1)) {
      itr++;
      if (!is_leaf(itr.ptr_)) {
        itr++;
      }
      // Using for loop to add any characters we need until we reach the end of
      // current node or task is completed
      for (int k = 0; k < itr.weight() && (int)s.size() < j - start_loc + 1;
           k++) {
        s += (itr.value())[k];
      }
    }
  }
  return true;
}

// The first i characters should stay in the current rope, while a new
// Rope (rhs) should contain the remaining size_-i characters.
// A valid split should always result in two ropes of non-zero length.
// If the split would not be valid, this rope should not be changed,
// and the rhs rope should be an empty rope.
// The return value should be this rope (the "left") part of the string
// This function should move the nodes to the rhs instead of making new
// copies.
Rope &Rope::split(int i, Rope &rhs) {
  // Invalid split, set rhs to null and size to 0, return
  if (i == 0 || i >= this->size_) {
    rhs.root = NULL;
    rhs.size_ = 0;
    return *this;
  }
  // First find the node we want to split
  Node *tmp = root;
  while (tmp != NULL) {
    if (tmp->left == NULL && tmp->right == NULL) {
      break;
    }
    if (i < tmp->weight) {
      tmp = tmp->left;
    } else if (i >= tmp->weight) {
      i -= tmp->weight;
      tmp = tmp->right;
    }
  }
  Node *rhs_left_leaf;
  // Case2: index is at the beginning of a node
  if (i == 0) {
    rhs_left_leaf = tmp;
  }
  // Case2: index is either in the middle or at the end of a node, cut
  // the node, then split
  else if (i != 0) {
    // Create a new right leaf and left leaf
    Node *right_leaf = new Node(tmp->weight - i);
    Node *left_leaf = new Node(i);
    // Set pointers point to the correct location
    tmp->right = right_leaf;
    tmp->left = left_leaf;
    right_leaf->parent = tmp;
    left_leaf->parent = tmp;
    // Use substr to split value in the node
    left_leaf->value = (tmp->value).substr(0, i);
    right_leaf->value = (tmp->value).substr(i, tmp->weight - i);
    // Change original node's weight and value
    tmp->weight = left_leaf->weight;
    tmp->value = "";
    rhs_left_leaf = tmp->right;
  }
  // Using loop to find all other nodes we need to split
  while (tmp != tmp->parent->left) {
    tmp = tmp->parent;
  }
  // Since we need to move the node from the rope, sutract its weight from its
  // parent pointers
  tmp->parent->weight -= rhs_left_leaf->weight;
  tmp = tmp->parent->right;
  // Using copy constructor to make rope that suppose to be on the right hand
  // side of the new rope
  Rope tmp_rhs(tmp);
  // Create a new root, and set its pointers to the correct place
  Node *rhs_new_root = new Node(rhs_left_leaf->weight);
  rhs_new_root->right = tmp_rhs.root;
  rhs_new_root->left = rhs_left_leaf;
  rhs_left_leaf->parent->right = NULL;
  tmp->parent->right = NULL;
  rhs_new_root->right->parent = rhs_new_root;
  rhs_new_root->left->parent = rhs_new_root;
  // Change the root to the correct place
  tmp_rhs.root = rhs_new_root;
  tmp_rhs.size_ += rhs_new_root->left->weight;
  // Now tmp_rhs is the correct rope from split function, give its value to rhs
  rhs = tmp_rhs;
  // Change the left rope size_ since we are moving a node away from it.
  // (subtract its weight)
  size_ -= rhs_left_leaf->weight;
  // Set the root correctly
  tmp = rhs.root;
  // Using loop to subtract all weights on the right hand side
  while (tmp->right) {
    size_ -= tmp->right->weight;
    tmp = tmp->right;
  }
  // Since size_ has been correctly changed and root holds all elements in the
  // rope, we just need to make weight equals size_ of this entire rope
  root->weight = size_;
  return *this;
}
