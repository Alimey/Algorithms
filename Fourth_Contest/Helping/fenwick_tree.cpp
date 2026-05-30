#include <climits>
#include <iostream>
#include <vector>

// 1-ИНДЕКСАЦИЯ //

class FenwickTree {
 private:
  std::vector<long long> tree_;

 public:
  FenwickTree(size_t n): tree_(n + 1) {
    tree_[0] = LONG_LONG_MIN;
  }

  void Update(size_t pos, long long val) {
    long long lpos = static_cast<long long>(pos);
    while (lpos < static_cast<long long>(tree_.size())) {
      tree_[lpos] += val;
      lpos += lpos & -lpos;
    }
  }

  long long PrefSum (size_t r) {
    long long ans = 0;
    long long lr = static_cast<long long>(r);
    while (lr > 0) {
      ans += tree_[lr];
      lr -= lr & -lr;
    }
    return ans;
  }

  long long Sum(size_t l, size_t r) {
    return PrefSum(r) - PrefSum(l - 1);
  }
};