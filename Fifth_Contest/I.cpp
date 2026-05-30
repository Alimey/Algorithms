#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

#define shared_t std::shared_ptr<Avl::Node>

namespace Avl {
struct Node {
  int key = 0;
  int count = 1;
  int subtree_deep = 1;
  int subtree_size = 1;
  shared_t right = nullptr;
  shared_t left = nullptr;

  Node() = default;

  Node(int key) : key(key) {}

  int GetDiff() {
    int left_subtree_deep = (left == nullptr) ? 0 : left->subtree_deep;
    int right_subtree_deep = (right == nullptr) ? 0 : right->subtree_deep;
    return right_subtree_deep - left_subtree_deep;
  }

  void Fix() {
    int left_deep = (left == nullptr) ? 0 : left->subtree_deep;
    int right_deep = (right == nullptr) ? 0 : right->subtree_deep;
    subtree_deep = std::max(left_deep, right_deep) + 1;

    int left_size = (left == nullptr) ? 0 : left->subtree_size;
    int right_size = (right == nullptr) ? 0 : right->subtree_size;
    subtree_size = left_size + right_size + count;
  }
};

shared_t TurnRight(shared_t root) {
  shared_t left_son = root->left;
  root->left = left_son->right;
  left_son->right = root;
  root->Fix();
  left_son->Fix();
  return left_son;
}

shared_t TurnLeft(shared_t root) {
  shared_t right_son = root->right;
  root->right = right_son->left;
  right_son->left = root;
  root->Fix();
  right_son->Fix();
  return right_son;
}

shared_t Balance(shared_t root) {
  if (root == nullptr) {
    return nullptr;
  }
  root->Fix();
  if (root->GetDiff() == 2) {
    if (root->right->GetDiff() < 0) {
      root->right = TurnRight(root->right);
    }
    return TurnLeft(root);
  }
  if (root->GetDiff() == -2) {
    if (root->left->GetDiff() > 0) {
      root->left = TurnLeft(root->left);
    }
    return TurnRight(root);
  }
  return root;
}

shared_t Add(shared_t root, int key) {
  if (root == nullptr) {
    return std::make_shared<Node>(key);
  }
  if (root->key == key) {
    ++root->count;
    ++root->subtree_size;
    return root;
  }
  if (key < root->key) {
    root->left = Add(root->left, key);
  }
  if (key > root->key) {
    root->right = Add(root->right, key);
  }
  return Balance(root);
}

shared_t FindRightMin(shared_t root) {
  if (root->left == nullptr) {
    return root;
  }
  return FindRightMin(root->left);
}

shared_t Remove(shared_t root, int key) {
  if (root == nullptr) {
    return nullptr;
  }
  if (key < root->key) {
    root->left = Remove(root->left, key);
    return Balance(root);
  }
  if (key > root->key) {
    root->right = Remove(root->right, key);
    return Balance(root);
  }
  --root->count;
  --root->subtree_size;
  if (root->count > 0) {
    return root;
  }
  if (root->left == nullptr && root->right == nullptr) {
    return nullptr;
  }
  if (root->right == nullptr || root->left == nullptr) {
    return (root->left == nullptr) ? root->right : root->left;
  }
  shared_t most_left_from_right = FindRightMin(root->right);
  root->key = most_left_from_right->key;
  root->count = most_left_from_right->count;
  most_left_from_right->count = 1;
  root->right = Remove(root->right, most_left_from_right->key);
  return Balance(root);
}

int CountPref(shared_t root, int border) {
  if (root == nullptr) {
    return 0;
  }
  if (border < root->key) {
    return CountPref(root->left, border);
  }
  int ans = root->count;
  ans += (root->left == nullptr) ? 0 : root->left->subtree_size;
  ans += CountPref(root->right, border);
  return ans;
}

int Count(shared_t root, int min, int max) {
  return CountPref(root, max) - CountPref(root, min - 1);
}
}  // namespace Avl

struct Fenwick {
 private:
  std::vector<shared_t> tree_;
  int n_;

 public:
  Fenwick(int n) : tree_(n + 1), n_(n) {}

  Fenwick(std::vector<int>& a) : Fenwick(static_cast<int>(a.size())) {
    Build(a);
  }

 private:
  void Build(std::vector<int>& a) {
    for (size_t i = 0; i < a.size(); ++i) {
      Insert(i + 1, a[i]);
    }
  }

  void Insert(int pos, int val) {
    while (pos <= n_) {
      tree_[pos] = Avl::Add(tree_[pos], val);
      pos += pos & -pos;
    }
  }

 public:
  void Update(int pos, int old_val, int new_val) {
    while (pos <= n_) {
      tree_[pos] = Avl::Remove(tree_[pos], old_val);
      tree_[pos] = Avl::Add(tree_[pos], new_val);
      pos += pos & -pos;
    }
  }

 private:
  int CountPref(int border, int min, int max) {
    int ans = 0;
    while (border > 0) {
      ans += Avl::Count(tree_[border], min, max);
      border -= border & -border;
    }
    return ans;
  }

 public:
  int Count(int left, int right, int min, int max) {
    return CountPref(right, min, max) - CountPref(left - 1, min, max);
  }
};

int main() {
  freopen("input.txt", "r", stdin);
  std::ios_base::sync_with_stdio(false);

  int n;
  int q;
  std::cin >> n >> q;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  Fenwick fenwick(a);
  for (int i = 0; i < q; ++i) {
    std::string command;
    std::cin >> command;
    if (command == "SET") {
      int i;
      int x;
      std::cin >> i >> x;
      fenwick.Update(i, a[i - 1], x);
      a[i - 1] = x;
    }
    if (command == "GET") {
      int l;
      int r;
      int x;
      int y;
      std::cin >> l >> r >> x >> y;
      std::cout << fenwick.Count(l, r, x, y) << "\n";
    }
  }
}