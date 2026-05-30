#include <iostream>
#include <memory>
#include <stack>
#include <vector>

#define lint long long

struct Node {
  lint key = 0;
  lint height = 0;
  std::shared_ptr<Node> right = nullptr;
  std::shared_ptr<Node> left = nullptr;

  Node() = default;

  Node(lint x) : key(x) {}

  void FixHeight() {
    if (left == nullptr && right == nullptr) {
      height = 1;
      return;
    }
    if (left == nullptr) {
      height = right->height + 1;
      return;
    }
    if (right == nullptr) {
      height = left->height + 1;
      return;
    }
    height = std::max(left->height, right->height) + 1;
  }

  lint GetDiff() {
    lint left_height = (left == nullptr) ? 0 : left->height;
    lint right_height = (right == nullptr) ? 0 : right->height;
    return right_height - left_height;
  }
};

struct Avl {
  std::shared_ptr<Node> root;

  static std::shared_ptr<Node> TurnRight(std::shared_ptr<Node> node) {
    std::shared_ptr<Node> child = node->left;
    node->left = child->right;
    child->right = node;
    node->FixHeight();
    child->FixHeight();
    return child;
  }

  static std::shared_ptr<Node> TurnLeft(std::shared_ptr<Node> node) {
    std::shared_ptr<Node> child = node->right;
    node->right = child->left;
    child->left = node;
    node->FixHeight();
    child->FixHeight();
    return child;
  }

  static std::shared_ptr<Node> Balance(std::shared_ptr<Node> node) {
    node->FixHeight();
    if (node->GetDiff() == 2) {
      if (node->right->GetDiff() < 0) {
        node->right = TurnRight(node->right);
      }
      return TurnLeft(node);
    }
    if (node->GetDiff() == -2) {
      if (node->left->GetDiff() > 0) {
        node->left = TurnLeft(node->left);
      }
      return TurnRight(node);
    }
    return node;
  }

  std::shared_ptr<Node> Insert(std::shared_ptr<Node> node, lint x) {
    if (node == nullptr) {
      return std::make_shared<Node>(x);
    }
    if (node->key == x) {
      return node;
    }
    if (node->key > x) {
      node->left = Insert(node->left, x);
    }
    if (node->key < x) {
      node->right = Insert(node->right, x);
    }
    node->FixHeight();
    return Balance(node);
  }

  lint LowerBound(std::shared_ptr<Node> node, lint x) {
    if (node == nullptr) {
      return -1;
    }
    if (node->key >= x) {
      lint left_result = LowerBound(node->left, x);
      return (left_result != -1) ? left_result : node->key;
    }
    return LowerBound(node->right, x);
  }
};

int main() {
  freopen("input.txt", "r", stdin);
  std::ios_base::sync_with_stdio(false);

  const lint cMod = 1e9;
  lint q;
  std::cin >> q;
  char previous_command = '-';
  lint previous_find_value = LONG_LONG_MIN;
  Avl avl;
  for (lint i = 0; i < q; ++i) {
    char command;
    lint value;
    std::cin >> command >> value;
    if (command == '?') {
      previous_find_value = avl.LowerBound(avl.root, value);
      std::cout << previous_find_value << "\n";
      previous_command = '?';
    }
    if (command == '+' && previous_command == '-') {
      avl.root = avl.Insert(avl.root, value);
    }
    if (command == '+' && previous_command != '-') {
      avl.root = avl.Insert(avl.root, (previous_find_value + value) % cMod);
      previous_command = '-';
    }
  }
}