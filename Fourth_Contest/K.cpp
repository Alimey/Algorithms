#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <set>
#include <vector>

class Fenwick {
 private:
  std::vector<long long> tree_;

 public:
  Fenwick() = default;

  Fenwick(size_t n) : tree_(n + 1) {}

  void Update(size_t pos, long long val) {
    long long lpos = static_cast<long long>(pos);
    lpos = static_cast<long long>(pos);
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

class FenwickFenwick {
 private:
  std::vector<Fenwick> tree_;

 public:
  FenwickFenwick(size_t n, std::vector<std::map<size_t, size_t>>& ys) : tree_(n + 1) {
    for (size_t i = 1; i < n + 1; ++i) {
      tree_[i] = Fenwick(ys[i].size());
    }
  }

  void Update(size_t x, size_t y, long long val) {
    long long ly = static_cast<long long>(y);
    while (ly < static_cast<long long>(tree_.size())) {
      tree_[ly].Update(x, val);
      ly += ly & -ly;
    }
  }

  long long PrefSum(size_t a, size_t b) {
    long long ans = 0;
    long long lb = static_cast<long long>(b);
    while (lb > 0) {
      ans += tree_[lb].PrefSum(a);
      lb -= lb & -lb;
    }
    return ans;
  }
};

struct Point {
  size_t x;
  size_t y;
  long long val;

  bool operator<(const Point& other) {
    return x < other.x;
  }
};

int main() {
  freopen("input.txt", "r", stdin);
  std::ios_base::sync_with_stdio(false);
  size_t n;
  std::cin >> n;
  std::vector<Point> points;
  std::vector<size_t> ys;
  std::vector<size_t> xs;
  for (size_t i = 0; i < n; ++i) {
    Point p;
    std::cin >> p.x >> p.y >> p.val;
    points.push_back(p);
    ys.push_back(p.y);
    xs.push_back(p.x);
  }
  std::sort(ys.begin(), ys.end());
  ys.erase(std::unique(ys.begin(), ys.end()), ys.end());
  std::sort(xs.begin(), xs.end());
  xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
  size_t q;
  std::cin >> q;
  std::map<size_t, size_t> compressed_x;
  size_t idx = 1;
  for (size_t x : xs) {
    compressed_x[x] = idx++;
  }
  std::vector<Point> copy = points;
  std::sort(copy.begin(), copy.end());
  std::vector<std::map<size_t, size_t>> compressed_columns_y;
  std::map<size_t, size_t> column;
  Point last{SIZE_MAX, SIZE_MAX, LONG_LONG_MIN};
  size_t idy = 1;
  for (Point& p : copy) {
    if (p.x != last.x) {
      compressed_columns_y.push_back(column);
      column = std::map<size_t, size_t>();
      idy = 1;
      column[p.y] = idy++;
    } else {
      column[p.y] = idy++;
    }
    last = p;
  }
  compressed_columns_y.push_back(column);
  FenwickFenwick fefe(idx - 1, compressed_columns_y);
  for (Point& p : points) {
    size_t cx = compressed_x[p.x];
    fefe.Update(compressed_columns_y[cx][p.y], cx, p.val);
  }
  std::vector<long long> ans;
  for (size_t i = 0; i < q; ++i) {
    std::string command;
    std::cin >> command;
    if (command == "get") {
      size_t a;
      size_t b;
      std::cin >> a >> b;
      auto it_nearest_a = compressed_x.upper_bound(a);
      if (it_nearest_a == compressed_x.begin()) {
        ans.push_back(0);
        continue;
      }
      --it_nearest_a;
      auto it_nearest_b = compressed_columns_y[it_nearest_a->second].upper_bound(b);
      if (it_nearest_b == compressed_columns_y[it_nearest_a->second].begin()) {
        ans.push_back(0);
        continue;
      }
      --it_nearest_b;
      ans.push_back(fefe.PrefSum(it_nearest_b->second, it_nearest_a->second));
    }
    if (command == "change") {
      size_t i;
      long long w;
      std::cin >> i >> w;
      Point& p = points[i - 1];
      fefe.Update(compressed_columns_y[compressed_x[p.x]][p.y], compressed_x[p.x], -p.val);
      fefe.Update(compressed_columns_y[compressed_x[p.x]][p.y], compressed_x[p.x], w);
      p.val = w;
    }
  }
  for (size_t i = 0; i < ans.size(); ++i) {
    std::cout << ans[i] << "\n";
  }
}