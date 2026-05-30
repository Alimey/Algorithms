#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

// 1-ИНДЕКСАЦИЯ //

class FenwickTree {
 private:
  std::vector<std::vector<long long>> tree_;

 public:
  FenwickTree(size_t n, size_t m)
      : tree_(n + 1, std::vector<long long>(m + 1)) {}

  void Update(size_t posx, size_t posy, long long val) {
    long long lposx = static_cast<long long>(posx);
    long long n = static_cast<long long>(tree_.size());
    long long m = static_cast<long long>(tree_[0].size());
    for (; lposx < n; lposx += lposx & -lposx) {
      long long lposy = static_cast<long long>(posy);
      for (; lposy < m; lposy += lposy & -lposy) {
        tree_[lposx][lposy] += val;
      }
    }
  }

  long long PrefSum(size_t rx, size_t ry) {
    long long ans = 0;
    long long lrx = static_cast<long long>(rx);
    for (; lrx > 0; lrx -= lrx & -lrx) {
      long long lry = static_cast<long long>(ry);
      for (; lry > 0; lry -= lry & -lry) {
        ans += tree_[lrx][lry];
      }
    }
    return ans;
  }

  long long Sum(size_t x1, size_t y1, size_t x2, size_t y2) {
    size_t left = std::min(x1, x2);
    size_t right = std::max(x1, x2);
    size_t bottom = std::min(y1, y2);
    size_t top = std::max(y1, y2);
    long long total = PrefSum(right, top);
    if (left > 1) {
      total -= PrefSum(left - 1, top);
    }
    if (bottom > 1) {
      total -= PrefSum(right, bottom - 1);
    }
    if (left > 1 && bottom > 1) {
      total += PrefSum(left - 1, bottom - 1);
    }
    return total;
  }
};

int main() {
  freopen("input.txt", "r", stdin);

  size_t n;
  size_t q;
  std::cin >> n >> q;
  FenwickTree ft(n, n);
  std::vector<long long> answers;
  for (size_t i = 0; i < q; ++i) {
    std::string command;
    std::cin >> command;
    if (command == "ADD") {
      size_t x;
      size_t y;
      std::cin >> x >> y;
      ft.Update(x, y, 1);
      continue;
    }
    if (command == "GET") {
      size_t x1;
      size_t y1;
      size_t x2;
      size_t y2;
      std::cin >> x1 >> y1;
      std::cin >> x2 >> y2;
      answers.push_back(ft.Sum(x1, y1, x2, y2));
    }
  }
  for (size_t i = 0; i < answers.size(); ++i) {
    std::cout << answers[i] << "\n";
  }
}