#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

std::vector<size_t> max_k;
std::vector<std::vector<std::vector<std::pair<long long, long long>>>>
    sparse_table;

void FillK(size_t n) {
  max_k.resize(n + 1);
  max_k[0] = 0;
  if (n == 0) {
    return;
  }
  size_t pow = 0;
  max_k[1] = 0;
  for (size_t i = 2; i <= n; ++i) {
    if ((i & (i - 1)) == 0) {
      ++pow;
    }
    max_k[i] = pow;
  }
}

void FillSparse(std::vector<long long>& segment, size_t n) {
  if (segment.empty()) {
    return;
  }
  std::vector<std::vector<std::pair<long long, long long>>> first_row(n);
  for (size_t i = 0; i < n; ++i) {
    first_row[i] = {{segment[i], i}, {LONG_LONG_MAX, -1}};
  }
  sparse_table.push_back(first_row);
  for (size_t k = 1; k < max_k[n] + 1; ++k) {
    std::vector<std::vector<std::pair<long long, long long>>> row(n);
    for (size_t i = 0; i < n; ++i) {
      std::vector<std::pair<long long, long long>> temp;
      temp.push_back(sparse_table[k - 1][i][0]);
      temp.push_back(sparse_table[k - 1][i][1]);
      temp.push_back(
          sparse_table[k - 1][std::min(n - 1, i + (1 << (k - 1)))][0]);
      temp.push_back(
          sparse_table[k - 1][std::min(n - 1, i + (1 << (k - 1)))][1]);
      std::sort(temp.begin(), temp.end());
      row[i] = {temp[0], temp[1]};
    }
    sparse_table.push_back(row);
  }
}

long long FindMin(size_t l, size_t r) {
  size_t len = r - l + 1;
  size_t k = max_k[len];
  std::vector<std::pair<long long, long long>> temp;
  temp.push_back(sparse_table[k][l][0]);
  temp.push_back(sparse_table[k][l][1]);
  temp.push_back(sparse_table[k][r + 1 - (1 << k)][0]);
  temp.push_back(sparse_table[k][r + 1 - (1 << k)][1]);
  std::sort(temp.begin(), temp.end());
  std::unique(temp.begin(), temp.end());
  long long ans = temp[1].first;
  return ans;
}

int main() {
  freopen("input.txt", "r", stdin);

  size_t n;
  size_t q;
  std::cin >> n >> q;
  std::vector<long long> a(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  std::vector<std::pair<size_t, size_t>> queries(q);
  for (size_t i = 0; i < q; ++i) {
    std::cin >> queries[i].first >> queries[i].second;
  }

  FillK(n);
  FillSparse(a, n);

  std::vector<long long> answers(q);
  for (size_t i = 0; i < q; ++i) {
    answers[i] = FindMin(queries[i].first - 1, queries[i].second - 1);
  }
  for (size_t i = 0; i < q; ++i) {
    std::cout << answers[i] << "\n";
  }
}