#include <iostream>
#include <vector>

std::vector<int> sequence;
std::vector<std::pair<int, int>> invertized_sequence;

struct OneZeroTree {
  std::vector<int> oztree;
  int n;

  OneZeroTree(int n);
  void Build(int v, int lb, int rb, int pos);
  void PlaceA(int v, int lb, int rb, int val, int k);
};

OneZeroTree::OneZeroTree(int n) : oztree(std::vector<int>(4 * n, 0)), n(n) {
  for (int i = 0; i < n; ++i) {
    Build(0, 0, n - 1, i);
  }
}

void OneZeroTree::Build(int v, int lb, int rb, int pos) {
  if (lb == rb) {
    oztree[v] = 1;
    return;
  }
  int mb = lb + (rb - lb) / 2;
  if (pos <= mb) {
    Build(2 * v + 1, lb, mb, pos);
  } else {
    Build(2 * v + 2, mb + 1, rb, pos);
  }
  oztree[v] = oztree[2 * v + 1] + oztree[2 * v + 2];
}

void OneZeroTree::PlaceA(int v, int lb, int rb, int val, int k) {
  if (lb == rb) {
    oztree[v] = 0;
    sequence[lb] = val;
    return;
  }
  int mb = lb + (rb - lb) / 2;
  if (oztree[2 * v + 1] > k) {
    PlaceA(2 * v + 1, lb, mb, val, k);
  } else {
    PlaceA(2 * v + 2, mb + 1, rb, val, k - oztree[2 * v + 1]);
  }
  oztree[v] = oztree[2 * v + 1] + oztree[2 * v + 2];
}

void MergeSort(int l, int r) {
  if (l == r) {
    return;
  }
  int m = l + (r - l) / 2;
  MergeSort(l, m);
  MergeSort(m + 1, r);

  std::vector<std::pair<int, int>> merged;
  int first = l;
  int second = m + 1;
  while (first <= m || second <= r) {
    if (second > r || (first <= m && invertized_sequence[first].first <
                                         invertized_sequence[second].first)) {
      merged.push_back(invertized_sequence[first++]);
      continue;
    }
    if (first <= m) {
      invertized_sequence[second].second += m - first + 1;
    }
    merged.push_back(invertized_sequence[second++]);
  }
  std::copy(merged.begin(), merged.end(), invertized_sequence.begin() + l);
}

int main() {
  freopen("input.txt", "r", stdin);

  int x;
  std::vector<int> invertized;
  while (std::cin >> x) {
    invertized.push_back(x);
  }
  int n = static_cast<int>(invertized.size());
  sequence.resize(n);
  invertized_sequence.resize(n);
  OneZeroTree oz(n);
  for (int i = 0; i < n; ++i) {
    oz.PlaceA(0, 0, n - 1, i + 1, invertized[i]);
  }
  for (int i = 0; i < n; ++i) {
    invertized_sequence[sequence[i] - 1] = {i + 1, 0};
  }
  MergeSort(0, n - 1);
  for (int i = 0; i < n; ++i) {
    std::cout << invertized_sequence[i].second << " ";
  }
}