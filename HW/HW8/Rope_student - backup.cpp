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
  root = p;
  size_ = p->weight;
  while (p->right) {
    size_ += p->right->weight;
    p = p->right;
  }
}

Rope::~Rope() {
  if (root != 0) {
    this->destroy_tree(root);
  }
}

Node *copy_tree(Node *old_root) {
  Node *new_root = new Node(old_root->weight);
  if (!old_root) {
    new_root = NULL;
  } else {
    copy_helper(old_root, new_root);
  }
  return new_root;
}

void copy_helper(Node *old_root, Node *curr) {
  if (!old_root) {
    old_root = NULL;
    return;
  }
  if (old_root->right) {
    Node *tmp = new Node(old_root->right->weight);
    tmp->value = old_root->right->value;
    curr->right = tmp;
    tmp->parent = curr;
    copy_helper(old_root->right, curr->right);
  }
  if (old_root->left) {
    Node *tmp = new Node(old_root->left->weight);
    tmp->value = old_root->left->value;
    curr->left = tmp;
    tmp->parent = curr;
    copy_helper(old_root->left, curr->left);
  }
  return;
}

Rope::Rope(const Rope &r) {
  size_ = r.size_;
  root = copy_tree(r.root);
}

Rope &Rope::operator=(const Rope &r) {
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
  if (i >= size_ || i < 0) {
    return false;
  }
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
  c = (tmp->value)[i];
  return true;
}

// Add the other rope (r)'s string to the end of my string
void Rope::concat(const Rope &r) {
  if (r.root == NULL) {
    return;
  }
  Node *new_root = new Node;
  new_root->left = root;
  new_root->right = copy_tree(r.root);
  root->parent = new_root;
  new_root->right->parent = new_root;
  new_root->weight = size_;
  Node *tmp = new_root->right;
  size_ += tmp->weight;
  while (tmp->right) {
    tmp = tmp->right;
    size_ += tmp->weight;
  }
  root = new_root;
}

// Get a substring from index i to index j.
// Includes both the characters at index i and at index j.
// String can be one character if i and j match
// Returns true if a string was returned, and false otherwise
// Function should be written with efficient running time.
bool Rope::report(int i, int j, std::string &s) const {
  if (j >= size_ || j < i || i < 0) {
    return false;
  }
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
  for (; i < tmp->weight && (int)s.size() < j - i + 1; i++) {
    s += (tmp->value)[i];
  }

  if ((int)s.size() < (j - start_loc + 1)) {
    rope_iterator itr = tmp;
    while ((int)s.size() < (j - start_loc + 1)) {
      itr++;
      if (!is_leaf(itr.ptr_)) {
        itr++;
      }
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
  if (i == 0 || i >= this->size_) {
    rhs.root = NULL;
    return *this;
  }
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
  if (i == 0) {
    rhs_left_leaf = tmp;
  }
  // Special case: index is either in the middle or at the end of a node, cut
  // the node, then split
  else if (i != 0) {
    Node *right_leaf = new Node(tmp->weight - i);
    Node *left_leaf = new Node(i);
    tmp->right = right_leaf;
    tmp->left = left_leaf;
    right_leaf->parent = tmp;
    left_leaf->parent = tmp;
    left_leaf->value = (tmp->value).substr(0, i);
    right_leaf->value = (tmp->value).substr(i, tmp->weight - i);
    tmp->weight = left_leaf->weight;
    tmp->value = "";
    tmp = tmp->right;
    rhs_left_leaf = tmp;
  }
  while (tmp != tmp->parent->left) {
    tmp = tmp->parent;
  }
  tmp->parent->weight -= rhs_left_leaf->weight;
  tmp = tmp->parent->right;
  Rope tmp_rhs(tmp);
  Node *rhs_new_root = new Node(rhs_left_leaf->weight);
  rhs_new_root->right = tmp_rhs.root;
  rhs_new_root->left = rhs_left_leaf;
  rhs_left_leaf->parent->right = NULL;
  tmp->parent->right = NULL;
  rhs_new_root->right->parent = rhs_new_root;
  rhs_new_root->left->parent = rhs_new_root;
  tmp_rhs.root = rhs_new_root;
  tmp_rhs.size_ += rhs_new_root->left->weight;
  rhs = tmp_rhs;
  size_ -= rhs_left_leaf->weight;
  tmp = rhs.root;
  while (tmp->right) {
    size_ -= tmp->right->weight;
    tmp = tmp->right;
  }
  root->weight = size_;
  return *this;
}
