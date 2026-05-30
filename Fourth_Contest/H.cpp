#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>

struct SegNode {
  long long covers = 0;
  long long union_len = 0;
};

struct Event {
  long long x;
  long long y1;
  long long y2;
  long long type;

  bool operator<(const Event& other) const {
    if (x == other.x) {
      return type > other.type;
    }
    return x < other.x;
  }
};

struct SegmentTree {
  std::vector<SegNode> tree;
  long long n;

  SegmentTree(long long n) : tree(std::vector<SegNode>(4 * n)), n(n - 1) {}

  void Update(long long v, long long lb, long long rb,
              std::pair<long long, long long> lr, long long type,
              std::unordered_map<long long, long long>& real_y) {
    long long l = lr.first;
    long long r = lr.second;
    if (l <= lb && rb <= r) {
      tree[v].covers += type;
      if (tree[v].covers > 0) {
        tree[v].union_len = real_y[rb + 1] - real_y[lb];
      } else if (lb == rb) {
        tree[v].union_len = 0;
      } else {
        tree[v].union_len = tree[2 * v].union_len + tree[2 * v + 1].union_len;
      }
      return;
    }
    long long mb = lb + (rb - lb) / 2;
    if (l <= mb) {
      Update(2 * v, lb, mb, {l, r}, type, real_y);
    }
    if (r > mb) {
      Update(2 * v + 1, mb + 1, rb, {l, r}, type, real_y);
    }
    if (tree[v].covers > 0) {
      tree[v].union_len = real_y[rb + 1] - real_y[lb];
    } else {
      tree[v].union_len = tree[2 * v].union_len + tree[2 * v + 1].union_len;
    }
  }

  void Add(long long y1, long long y2, long long type,
           std::unordered_map<long long, long long>& real_y) {
    Update(1, 1, n, {y1, y2 - 1}, type, real_y);
  }

  long long GetUnionLen() { return tree[1].union_len; }
};

int main() {
  freopen("input.txt", "r", stdin);
  std::ios_base::sync_with_stdio(false);

  long long n;
  std::cin >> n;
  std::vector<Event> events;
  std::vector<long long> unique_y;
  for (long long i = 0; i < n; ++i) {
    long long x1;
    long long x2;
    long long y1;
    long long y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    if (x1 == x2 || y1 == y2) {
      continue;
    }
    events.push_back({x1, y1, y2, 1});
    events.push_back({x2, y1, y2, -1});
    unique_y.push_back(y1);
    unique_y.push_back(y2);
  }
  std::sort(unique_y.begin(), unique_y.end());
  unique_y.erase(std::unique(unique_y.begin(), unique_y.end()), unique_y.end());
  std::unordered_map<long long, long long> indexes_y;
  long long id = 1;
  for (long long element : unique_y) {
    if (!indexes_y.contains(element)) {
      indexes_y[element] = id++;
    }
  }
  std::unordered_map<long long, long long> real_y;
  for (auto& [real, compressed] : indexes_y) {
    real_y[compressed] = real;
  }
  std::sort(events.begin(), events.end());
  SegmentTree stree(indexes_y.size());
  Event prev{LONG_LONG_MIN, LONG_LONG_MIN, LONG_LONG_MIN, LONG_LONG_MIN};
  long long ans = 0;
  for (auto& event : events) {
    if (prev.x != LONG_LONG_MIN) {
      ans += stree.GetUnionLen() * (event.x - prev.x);
    }
    stree.Add(indexes_y[event.y1], indexes_y[event.y2], event.type, real_y);
    prev = event;
  }
  std::cout << ans;
}