#include <iostream>
#include <memory>
#include <stack>
#include <vector>

struct Node {
  int key;
  int priority;
  std::shared_ptr<Node> left = nullptr;
  std::shared_ptr<Node> right = nullptr;
  std::weak_ptr<Node> parent;
};

void Dfs(std::shared_ptr<Node> root,
         std::vector<std::tuple<int, int, int>>& result) {
  if (root == nullptr) {
    return;
  }
  Dfs(root->left, result);
  int p = root->parent.lock() ? root->parent.lock()->key + 1 : 0;
  int l = root->left ? root->left->key + 1 : 0;
  int r = root->right ? root->right->key + 1 : 0;
  result.emplace_back(p, l, r);
  Dfs(root->right, result);
}

int main() {
  freopen("input.txt", "r", stdin);
  std::ios_base::sync_with_stdio(false);
  int n;
  std::cin >> n;
  std::vector<std::pair<int, int>> points(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> points[i].first >> points[i].second;
  }
  std::stack<std::shared_ptr<Node>> stk;
  std::shared_ptr<Node> root = nullptr;
  for (int i = 0; i < n; ++i) {
    auto current = std::make_shared<Node>();
    current->key = i;
    current->priority = points[i].second;
    std::shared_ptr<Node> last = nullptr;
    while (!stk.empty() && stk.top()->priority > current->priority) {
      last = stk.top();
      stk.pop();
    }
    if (stk.empty()) {
      current->left = root;
      if (root != nullptr) {
        root->parent = current;
      }
      root = current;
    } else {
      stk.top()->right = current;
      current->parent = stk.top();
      current->left = last;
      if (last != nullptr) {
        last->parent = current;
      }
    }
    stk.push(current);
  }
  std::cout << "YES\n";
  std::vector<std::tuple<int, int, int>> result;
  Dfs(root, result);
  for (int i = 0; i < n; ++i) {
    auto [p, l, r] = result[i];
    std::cout << p << " " << l << " " << r << "\n";
  }
}
