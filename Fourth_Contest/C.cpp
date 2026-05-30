#include <climits>
#include <iostream>
#include <vector>

// 1-ИНДЕКСАЦИЯ //

class FenwickTree {
 private:
  std::vector<long long> tree_;

 public:
  FenwickTree(size_t n) : tree_(n + 1) {}

  FenwickTree(std::vector<long long>& base) : FenwickTree(base.size()) {
    for (size_t i = 1; i < base.size() + 1; ++i) {
      Update(i, base[i - 1]);
    }
  }

  void Update(size_t pos, long long val) {
    long long current_val = Sum(pos, pos);
    long long delta = val - current_val;
    if (pos % 2 == 0) {
      delta *= -1;
    }
    long long lpos = static_cast<long long>(pos);
    while (lpos < static_cast<long long>(tree_.size())) {
      tree_[lpos] += delta;
      lpos += lpos & -lpos;
    }
  }

  long long PrefSum(size_t r) {
    long long ans = 0;
    long long lr = static_cast<long long>(r);
    while (lr > 0) {
      ans += tree_[lr];
      lr -= lr & -lr;
    }
    return ans;
  }

  long long Sum(size_t l, size_t r) {
    long long ans = PrefSum(r) - PrefSum(l - 1);
    if (l % 2 == 0) {
      ans *= -1;
    }
    return ans;
  }
};

int main() {
  freopen("input.txt", "r", stdin);

  size_t n;
  std::cin >> n;
  std::vector<long long> a(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  size_t q;
  std::cin >> q;
  FenwickTree ftree(a);
  std::vector<long long> ans;
  for (size_t i = 0; i < q; ++i) {
    size_t quiery;
    std::cin >> quiery;
    if (quiery == 0) {
      size_t pos;
      long long val;
      std::cin >> pos >> val;
      ftree.Update(pos, val);
    } else if (quiery == 1) {
      size_t l;
      size_t r;
      std::cin >> l >> r;
      ans.push_back(ftree.Sum(l, r));
    }
  }

  for (size_t i = 0; i < ans.size(); ++i) {
    std::cout << ans[i] << "\n";
  }
}