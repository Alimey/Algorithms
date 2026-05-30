#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct PersikTree {
  int lb = 1;
  int rb = 1;
  std::shared_ptr<PersikTree> left = nullptr;
  std::shared_ptr<PersikTree> right = nullptr;
  int x = 0;

  PersikTree(int lb, int rb, std::vector<int>& a) : lb(lb), rb(rb) {
    if (lb != rb) {
      int mb = (lb + rb) / 2;
      left = std::make_shared<PersikTree>(lb, mb, a);
      right = std::make_shared<PersikTree>(mb + 1, rb, a);
    } else {
      x = a[lb - 1];
    }
  }

  PersikTree(const PersikTree& other)
      : lb(other.lb),
        rb(other.rb),
        left(other.left),
        right(other.right),
        x(other.x) {}

  void Add(int pos, int val) {
    if (lb == rb) {
      x = val;
      return;
    }
    int mb = (lb + rb) / 2;
    if (pos <= mb) {
      left = std::make_shared<PersikTree>(*left);
      left->Add(pos, val);
    } else {
      right = std::make_shared<PersikTree>(*right);
      right->Add(pos, val);
    }
  }

  int Get(int pos) const {
    if (lb == rb) {
      return x;
    }
    int mb = (lb + rb) / 2;
    if (pos <= mb) {
      return left->Get(pos);
    }
    return right->Get(pos);
  }
};

int main() {
  freopen("input.txt", "r", stdin);
  std::ios_base::sync_with_stdio(false);
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  int q;
  std::cin >> q;

  // Вектор для хранения версий деревьев
  std::vector<std::shared_ptr<PersikTree>> versions;

  // Создаём первую версию дерева
  auto ptree = std::make_shared<PersikTree>(1, n, a);
  versions.push_back(ptree);
  versions.push_back(ptree);

  std::vector<int> ans;

  for (int t = 0; t < q; ++t) {
    std::string command;
    std::cin >> command;
    if (command == "create") {
      int i;
      int j;
      int x;
      std::cin >> i >> j >> x;

      // Создаём новую версию из указанной
      auto ith_version = versions[i];
      auto new_version = std::make_shared<PersikTree>(*ith_version);

      // Обновляем новую версию
      new_version->Add(j, x);
      versions.push_back(new_version);
    } else if (command == "get") {
      int i;
      int j;
      std::cin >> i >> j;

      // Получаем значение из указанной версии
      auto ith_version = versions[i];
      ans.push_back(ith_version->Get(j));
    }
  }

  for (int value : ans) {
    std::cout << value << "\n";
  }

  return 0;
}
