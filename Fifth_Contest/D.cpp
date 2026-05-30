#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

enum class Color {
  cRed,
  cBlack
};

namespace RedBlackTree {
  struct Node {
    int key = 0;
    Color color = Color::cBlack;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent;

    Node() = default;

    Node(int key, Color color): key(key), color(color) {}
  };

  /// В поворотах все нужные связи обновятся, а вернется тот, кто встал на наше место ///

  Node* TurnLeft(Node* root) {
    Node* right_son = root->right;
    // про деда
    right_son->parent = root->parent;
    if (root->parent != nullptr && root->parent->left == root) {
      root->parent->left = right_son;
    } else if (root->parent != nullptr) {
      root->parent->right = right_son;
    }
    root->parent = right_son;
    // про сына сына
    if (right_son->left != nullptr) {
      right_son->left->parent = root;
    }
    root->right = right_son->left;
    right_son->left = root;
    return right_son;
  }

  Node* TurnRight(Node* root) {
    Node* left_son = root->left;
    // про деда
    left_son->parent = root->parent;
    if (root->parent != nullptr && root->parent->right == root) {
      root->parent->right = left_son;
    } else if (root->parent != nullptr) {
      root->parent->left = left_son;
    }
    root->parent = left_son;
    // про сына сына
    if (left_son->right != nullptr) {
      left_son->right->parent = root;
    }
    root->left = left_son->right;
    left_son->right = root;
    return left_son;
  }

  Node* FixInsert(Node* root) {
    // если мы в корне
    if (root->parent == nullptr) {
      root->color = Color::cBlack;
      return root;
    }
    // если родитель черный
    if (root->parent->color == Color::cBlack) {
      return root;
    }
    // иначе есть дед и дядя
    Node* parent = root->parent;
    Node* grandpa = parent->parent;
    Node* uncle = (grandpa->left == parent) ? grandpa->right : grandpa->left;
    // Если дядя красный 
    if (uncle->color == Color::cRed) {
      parent->color = Color::cBlack;
      uncle->color = Color::cBlack;
      return FixInsert(grandpa);
    }
    // Если дядя черный
    if (root == parent->left && parent == grandpa->right) {
      parent = TurnRight(parent);
      root = parent->right;
    } else if (root == parent->right && parent == grandpa->left) {
      parent = TurnLeft(parent);
      root = parent->left;
    }
    parent->color = Color::cBlack;
    grandpa->color = Color::cRed;
    if (root == parent->left) {
      root = TurnRight(grandpa);
    } else {
      root = TurnLeft(grandpa);
    }
    return FixInsert(root);
  }

  bool IsLeaf(Node* root) {
    return root->right == nullptr && root->left == nullptr;
  }

  Node* MakeLeaf() {
    return new Node();
  }

  Node* MostRight(Node* root) {
    if (root == nullptr || root->right == nullptr || IsLeaf(root->right)) {
      return root;
    }
    return MostRight(root->right);
  }

  bool HasRedChild(Node* root) {
    return (root->left->color == Color::cRed || root->right->color == Color::cRed);
  }

  bool FromLeft(Node* root) {
    return root == root->parent->left;
  }

  Node* FixDelete(Node* root) {
    if (root->parent == nullptr) {
      return root;
    }
    Node* parent = root->parent;
    Node* brother = (FromLeft(root)) ? root->parent->right : root->parent->left;
    if (parent->color == Color::cRed) {
      if (HasRedChild(brother)) {
        if (brother->right->color == Color::cRed) {
          TurnLeft(brother); ////////// ????????????
        }
        brother->color = Color::cRed;
        brother->left->color = Color::cBlack;
        parent->color = Color::cBlack;
        return TurnRight(parent);
      }
      brother->color = Color::cRed;
      parent->color = Color::cBlack;
      return parent;
    }
    if (brother->color == Color::cRed) {
      if (HasRedChild(brother->right)) {
        Node* niece = brother->right;

      }
    }
  }

  Node* Insert(Node* root, int key) {
    if (IsLeaf(root)) {
      Node* vertice = new Node(key, Color::cRed);
      vertice->right = MakeLeaf();
      vertice->left = MakeLeaf();
      vertice->parent = root->parent;
      if (root->parent != nullptr && root == root->parent->right) {
        root->parent->right = vertice;
      } else if (root->parent != nullptr) {
        root->parent->left = vertice;
      }
      return FixInsert(vertice);
    }
    if (key < root->key) {
      return Insert(root->left, key);
    }
    if (key > root->key) {
      return Insert(root->right, key);
    }
    return root;
  }

  Node* Delete(Node* root, int key) {
    if (IsLeaf(root)) {
      return root;
    }
    if (key < root->key) {
      return Delete(root->left, key);
    }
    if (key > root->key) {
      return Delete(root->right, key);
    }
    if (!IsLeaf(root->left) && !IsLeaf(root->right)) {
      Node* most_right = MostRight(root->left);
      std::swap(root->key, most_right->key);
      return Delete(most_right, key);
    }
    if (IsLeaf(root->left) && IsLeaf(root->right) && root->color == Color::cRed) {
      Node* leaf = MakeLeaf();
      if (root->parent != nullptr && root == root->parent->left) {
        root->parent->left = leaf;
      } else if (root->parent != nullptr) {
        root->parent->right = leaf;
      }
      return leaf;
    }
    if (!IsLeaf(root->left)) {
      root->left->color = Color::cBlack;
      if (root->parent != nullptr && root == root->parent->left) {
        root->parent->left = root->left;
      } else if (root->parent != nullptr) {
        root->parent->right = root->left;
      }
      root->left->parent = root->parent;
      return root->left;
    }
    if (!IsLeaf(root->right)) {
      root->right->color = Color::cBlack;
      if (root->parent != nullptr && root == root->parent->left) {
        root->parent->left = root->right;
      } else if (root->parent != nullptr) {
        root->parent->right = root->right;
      }
      root->right->parent = root->parent;
      return root->right;
    }
    Node* leaf = MakeLeaf();
    if (root->parent != nullptr && root == root->parent->left) {
      root->parent->left = leaf;
    } else if (root->parent != nullptr) {
      root->parent->right = leaf;
    }
    return FixDelete(leaf);
  }
};