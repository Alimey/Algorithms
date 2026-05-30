#include <algorithm>
#include <climits>
#include <iostream>
#include <unordered_map>
#include <vector>

// Функция, проверяющая, является ли кликой множество вершин mask
// oldest_bit - старший бит для каждой маски (старшая вершина)
// neighbours_masks - множество соседей старшей вершины из исходного графа
bool IsClique(int mask, std::unordered_map<int, int>& oldest_bit, std::unordered_map<int, int>& neighbours_masks) {
  if (mask == 0) {
    return true;
  }

  int vertice = oldest_bit[mask];

  bool first_constrain = IsClique(mask ^ vertice, oldest_bit, neighbours_masks);
  bool second_constrain = ((mask ^ vertice) & neighbours_masks[vertice]) == (mask ^ vertice);

  return first_constrain && second_constrain;
}

// Функция, записывающая соседей для каждой вершины из графа matrix размера n
void FillNeighbours(const std::vector<std::vector<int>>& matrix, std::unordered_map<int, int>& neighbours_masks, int n) {
  for (int i = 0; i < n; ++i) {
    int neighbours_mask = 0;
    for (int j = 0; j < n; ++j) {
      if (matrix[i][j] == 1) {
        neighbours_mask += (1 << j);
      }
    }
    neighbours_masks[i] = neighbours_mask;
  }
}

// Функция, подсчитывающая старший бит всех масок до k
void CountOldests(int k, std::unordered_map<int, int>& oldest_bit) {
  int oldest = -1;
  for (int mask = 0; mask < (1 << k); ++mask) {
    if ((mask & (mask - 1)) == 0) {
      ++oldest;
    }
    oldest_bit[mask] = oldest >= 0 ? (1 << oldest) : -1;
  }
}

// Функция, подсчитывающая число клик в графе matrix
int CountSeparatesCliques(const std::vector<std::vector<int>>& matrix, int n) {
  std::unordered_map<int, int> neighbours_masks;
  std::unordered_map<int, int> oldest_bit;

  CountOldests(n, oldest_bit);
  FillNeighbours(matrix, neighbours_masks, n);

  int ans = 0;

  for (int mask = 0; mask < (1 << n); ++mask) {
    if (IsClique(mask, oldest_bit, neighbours_masks)) {
      ++ans;
    }
  }

  return ans;
}

// Функция, подсчитывающая подмножество вершин второго графа,
// соединенный со всеми вершинами подмножества первого графа
void FillCorr(std::unordered_map<int, int>& corr, const std::vector<std::vector<int>>& matrix, int n) {
  std::unordered_map<int, int> neighbours_masks;
  std::unordered_map<int, int> oldest_bit;

  CountOldests(n, oldest_bit);
  FillNeighbours(matrix, neighbours_masks, n);
  
  corr[0] = (1 << n) - 1;

  for (int mask = 1; mask < (1 << (n / 2)); mask <<= 1) {
    corr[mask] = (neighbours_masks[mask] & (((1 << n) - 1) & (1 << (n / 2))));
  }

  for (int mask = 1; mask < (1 << (n / 2)); ++mask) {
    corr[mask] = (corr[mask ^ oldest_bit[mask]] & neighbours_masks[oldest_bit[mask]]);
  }
}

int CountCliquesInMask(int mask, const std::vector<std::vector<int>>& matrix, int n) {
}

// Функция для подсчета клик между половинками графа matrix
int CountInterCliques(const std::vector<std::vector<int>>& matrix, int n) {
  std::unordered_map<int, int> corr;
  std::unordered_map<int, int> oldest_bit;
  std::unordered_map<int, int> neighbours_masks;

  FillNeighbours(matrix, neighbours_masks, n);
  CountOldests(n, oldest_bit);
  FillCorr(corr, matrix, n);

  int count = 0;
  for (int mask = 0; mask < (1 << (n / 2)); ++mask) {
    if (IsClique(mask, oldest_bit, neighbours_masks)) {
      count += 
    }
  }
}

int main() {
  freopen("input.txt", "r", stdin);
  std::ios_base::sync_with_stdio(false);

  int n;
  std::cin >> n;


}