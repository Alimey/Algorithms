#include <climits>
#include <iostream>
#include <vector>

struct SegTree {
  size_t l;
  size_t r;
  SegTree* right = nullptr;
  SegTree* left = nullptr;
  long long max;

  SegTree(size_t lb, size_t rb);
  void Add(size_t pos, long long val);
  long long GetMax(size_t lb, size_t rb);
};

SegTree::SegTree(size_t lb, size_t rb): 
    l(lb), r(rb), max(LONG_LONG_MIN) {
  while (lb < rb) {
    size_t mb = lb + (rb - lb) / 2;
    left = new SegTree(lb, mb);
    right = new SegTree(mb + 1, rb);
  }
}

void SegTree::Add(size_t pos, long long val) {
  max = std::max(val, max);
  if (left != nullptr) {
    if (pos <= left->r) {
      left->Add(pos, val);
    } else {
      right->Add(pos, val);
    }
  }
}

long long SegTree::GetMax(size_t lb, size_t rb) {
  if (l <= lb && r >= rb) {
    return max;
  }
  if (lb > rb || r < lb) {
    return LONG_LONG_MIN;
  }
  return std::max(left->GetMax(lb, rb), right->GetMax(lb, rb));
}