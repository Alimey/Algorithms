#include <iostream>
#include <memory>
#include <stack>
#include <vector>

struct Avl {
  std::string key;
  std::string value;
  std::shared_ptr<Avl> left = nullptr;
  std::shared_ptr<Avl> right = nullptr;
  int height = 0;

  Avl() = default;

  Avl(std::string key, std::string value) : key(key), value(value) {}

  int GetDiff() {
    int left_height = (left == nullptr) ? 0 : left->height;
    int right_height = (right == nullptr) ? 0 : right->height;
    return right_height - left_height;
  }

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

  static std::shared_ptr<Avl> TurnLeft(std::shared_ptr<Avl> node) {
    std::shared_ptr<Avl> child = node->right;
    node->right = child->left;
    child->left = node;
    node->FixHeight();
    child->FixHeight();
    return child;
  }

  static std::shared_ptr<Avl> TurnRight(std::shared_ptr<Avl> node) {
    std::shared_ptr<Avl> child = node->left;
    node->left = child->right;
    child->right = node;
    node->FixHeight();
    child->FixHeight();
    return child;
  }

  static std::shared_ptr<Avl> Balance(std::shared_ptr<Avl> node) {
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

  std::shared_ptr<Avl> Insert(std::shared_ptr<Avl> node, std::string key,
                              std::string value) {
    if (node == nullptr) {
      return std::make_shared<Avl>(key, value);
    }
    if (key < node->key) {
      node->left = Insert(node->left, key, value);
    } else {
      node->right = Insert(node->right, key, value);
    }
    node->FixHeight();
    return Balance(node);
  }

  static std::shared_ptr<Avl> Find(std::shared_ptr<Avl> node, std::string key) {
    if (node == nullptr || node->key == key) {
      return node;
    }
    if (key < node->key) {
      return Find(node->left, key);
    }
    return Find(node->right, key);
  }
};

int main() {
  freopen("input.txt", "r", stdin);
  std::ios_base::sync_with_stdio(false);

  int n;
  std::cin >> n;
  std::shared_ptr<Avl> avl_passwords;
  std::shared_ptr<Avl> avl_usernames;
  for (int i = 0; i < n; ++i) {
    std::string username;
    std::string password;
    std::cin >> username >> password;
    bool first_continue = false;
    bool second_continue = false;
    if (avl_passwords == nullptr) {
      avl_passwords = std::make_shared<Avl>(password, username);
      first_continue = true;
    }
    if (avl_usernames == nullptr) {
      avl_usernames = std::make_shared<Avl>(username, password);
      second_continue = true;
    }
    if (first_continue && second_continue) {
      continue;
    }
    avl_passwords = avl_passwords->Insert(avl_passwords, password, username);
    avl_usernames = avl_usernames->Insert(avl_usernames, username, password);
  }
  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    std::string word;
    std::cin >> word;
    std::shared_ptr<Avl> found_username =
        avl_passwords->Find(avl_passwords, word);
    if (found_username != nullptr) {
      std::cout << found_username->value << "\n";
      continue;
    }
    std::shared_ptr<Avl> found_password =
        avl_usernames->Find(avl_usernames, word);
    std::cout << found_password->value << "\n";
  }
}