#include <climits>
#include <iostream>
#include <vector>

// 1-ИНДЕКСАЦИЯ //

class FenwickTree {
 private:
  std::vector<long long> tree_;

 public:
  FenwickTree(size_t n) : tree_(n + 1) { tree_[0] = LONG_LONG_MIN; }

  void Update(size_t pos, long long val) {
    long long lpos = static_cast<long long>(pos);
    while (lpos < static_cast<long long>(tree_.size())) {
      tree_[lpos] += val;
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

  long long Sum(size_t l, size_t r) { return PrefSum(r) - PrefSum(l - 1); }
};

int main() {
  freopen("input.txt", "r", stdin);

  const size_t cDistance = 42'195;
  const size_t cRunners = 1e5;
  size_t n = cRunners;
  size_t q;
  std::cin >> q;

  std::vector<double> ans;
  FenwickTree track(cDistance);
  std::vector<size_t> where_is_sportsman(n);
  for (size_t i = 0; i < q; ++i) {
    std::string query;
    std::cin >> query;
    if (query == "RUN") {
      size_t sportsman;
      size_t control_point;
      std::cin >> sportsman >> control_point;
      size_t where_he_was = where_is_sportsman[sportsman - 1];
      where_is_sportsman[sportsman - 1] = control_point;
      if (!(where_he_was == 0)) {
        track.Update(where_he_was, -1);
      }
      track.Update(control_point, 1);
    }
    if (query == "CHEER") {
      size_t sportsman;
      std::cin >> sportsman;
      size_t where_he_is = where_is_sportsman[sportsman - 1];
      if (where_he_is == 0) {
        ans.push_back(0);
        continue;
      }
      long long how_many_running = track.PrefSum(cDistance - 1);
      if (how_many_running == 1) {
        ans.push_back(1);
        continue;
      }
      long long how_many_behind = track.PrefSum(where_he_is - 1);
      double percent = how_many_behind * 1.0 / (how_many_running - 1);
      ans.push_back(percent);
    }
  }

  for (size_t i = 0; i < ans.size(); ++i) {
    std::cout << ans[i] << "\n";
  }
}