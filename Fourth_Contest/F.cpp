#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <set>
#include <vector>

struct Segment {
  long long lb;
  long long rb;

  bool operator<(const Segment& other) const {
    if (lb != other.lb) {
      return lb < other.lb;
    }
    return rb > other.rb;
  }

  bool operator==(const Segment& other) const {
    return lb == other.lb && rb == other.rb;
  }

  bool operator!=(const Segment& other) const {
    return lb != other.lb || rb != other.rb;
  }
};

struct FenwickTree {
  std::vector<long long> tree;
  long long n;

  FenwickTree(long long n);
  void Add(long long pos, long long val);
  long long GetPrefSum(long long rb);
  long long GetSum(long long lb, long long rb);
};

FenwickTree::FenwickTree(long long n)
    : tree(std::vector<long long>(n + 1)), n(n) {}

void FenwickTree::Add(long long pos, long long val) {
  while (pos <= n) {
    tree[pos] += val;
    pos += pos & -pos;
  }
}

long long FenwickTree::GetPrefSum(long long rb) {
  long long sum = 0;
  while (rb > 0) {
    sum += tree[rb];
    rb -= rb & -rb;
  }
  return sum;
}

long long FenwickTree::GetSum(long long lb, long long rb) {
  return GetPrefSum(rb) - GetPrefSum(lb - 1);
}

int main() {
  freopen("input.txt", "r", stdin);
  std::ios_base::sync_with_stdio(false);
  long long n;
  std::cin >> n;
  std::vector<Segment> segments;
  for (long long i = 0; i < n; ++i) {
    Segment seg;
    std::cin >> seg.lb >> seg.rb;
    segments.push_back(seg);
  }
  std::sort(segments.begin(), segments.end());
  std::map<Segment, long long> freq;
  std::set<long long> unique_rbs;
  for (const auto& seg : segments) {
    unique_rbs.insert(seg.rb);
  }
  std::map<long long, long long> compress_map;
  long long idx = 1;
  for (long long rb : unique_rbs) {
    compress_map[rb] = idx++;
  }
  FenwickTree ft(compress_map.size());
  long long count = 0;
  Segment prev;
  prev.lb = LONG_LONG_MIN;
  prev.rb = LONG_LONG_MAX;
  for (const auto& seg : segments) {
    count += ft.GetSum(compress_map[seg.rb], compress_map.size());
    if (seg == prev) {
      count -= freq[seg];
    }
    if (!freq.contains(seg)) {
      freq[seg] = 1;
    } else {
      ++freq[seg];
    }
    ft.Add(compress_map[seg.rb], 1);
    prev = seg;
  }
  std::cout << count << '\n';
}