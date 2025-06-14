// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <string>
#include <vector>
#include <utility>

template <typename T>
class BST {
 public:
  struct Node {
    T value;
    int count;
    Node* left;
    Node* right;

    explicit Node(const T& val) : value(val), count(1), left(nullptr), right(nullptr) {}
  };

  explicit BST() : root(nullptr) {}
  ~BST() { clearTree(root); }

  void add(T value) { root = addNode(root, value); }
  int search(T value) const { return searchNode(root, value); }
  int depth() const { return depthTree(root); }
  void collectAll(std::vector<std::pair<T, int>>& out) const {
    collectHelper(root, out);
  }

 private:
  Node* root;

  Node* addNode(Node* node, T value) {
    if (!node) {
      return new Node(value);
    }
    if (value < node->value) {
      node->left = addNode(node->left, value);
    } else if (value > node->value) {
      node->right = addNode(node->right, value);
    } else {
      node->count++;
    }
    return node;
  }

  int searchNode(Node* node, T value) const {
    if (!node) {
      return 0;
    }
    if (value < node->value) {
      return searchNode(node->left, value);
    } else if (value > node->value) {
      return searchNode(node->right, value);
    } else {
      return node->count;
    }
  }

  int depthTree(Node* node) const {
    if (!node) {
      return -1;
    }
    int leftDepth = depthTree(node->left);
    int rightDepth = depthTree(node->right);
    return 1 + std::max(leftDepth, rightDepth);
  }

  void clearTree(Node* node) {
    if (node) {
      clearTree(node->left);
      clearTree(node->right);
      delete node;
    }
  }

  void collectHelper(Node* node, std::vector<std::pair<T, int>>& out) const {
    if (!node) return;
    collectHelper(node->left, out);
    out.emplace_back(node->value, node->count);
    collectHelper(node->right, out);
  }
};

#endif  // INCLUDE_BST_H_
