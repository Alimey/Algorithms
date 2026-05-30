#include <iostream>
#include <vector>
#include <algorithm>

std::vector<long long> max_k;
std::vector<std::vector<long long>> sparse_table;

void fillMaxK(size_t n) {
  max_k.resize(n + 1);
  max_k[0] = LONG_LONG_MIN;
  if (n == 0) {
    return;
  }
  size_t pow = 0;
  max_k[1] = 0;
  for (size_t i = 2; i <= n; ++i) {
    if (!(i & (i - 1))) {
      ++pow;
    }
    max_k[i] = pow;
  }
}

void fillST(std::vector<long long>& segment, size_t n) {
  if (segment.empty()) {
    return;
  }
  std::vector<long long> first_row(n);
  for (size_t i = 0; i < n; ++i) {
    first_row[i] = segment[i];
  }
  sparse_table.push_back(first_row);
  for (size_t k = 1; k < max_k[n] + 1; ++k) {
    std::vector<long long> row(n);
    for (size_t i = 0; i < n; ++i) {
      row[i] = std::min(sparse_table[k - 1][i], sparse_table[k - 1][std::min(n - 1, i + (1 << (k - 1)))]);
    }
    sparse_table.push_back(row);
  }
}

long long findMin(size_t l, size_t r) {
  size_t len = r - l + 1;
  size_t k = max_k[len];
  long long ans = std::min(sparse_table[k][l], sparse_table[k][r - (1 << k)]);
  return ans;
}