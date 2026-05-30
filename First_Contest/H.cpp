#include <algorithm>
#include <climits>
#include <deque>
#include <fstream>
#include <iostream>
#include <vector>

std::deque<std::deque<int>> ans;

int FindDays(std::vector<std::vector<int>>& trucks,
             std::vector<std::vector<int>>& weights, int k, int n,
             int traceback_code = 0) {
  int i = 0;
  int j = 0;
  std::vector<int> carries(n);
  std::deque<int> day;
  while (i < n && j < k) {
    if (trucks[i][0] - carries[i] >= weights[j][0]) {
      carries[i] += weights[j][0];
      day.push_back(weights[j][1] + 1);
      day.push_back(trucks[i][1] + 1);
      j++;
    } else {
      i++;
    }
  }
  day.push_front(j);
  if (traceback_code == 1) {
    ans.push_back(day);
  }
  if (j == k) {
    return 1;
  }

  std::vector<std::vector<int>> new_weights;
  for (int t = j; t < k; t++) {
    new_weights.push_back(weights[t]);
  }

  return 1 + FindDays(trucks, new_weights, k - j, n, traceback_code);
}

int FindMinDays(std::vector<std::vector<int>>& trucks,
                std::vector<std::vector<int>>& weights, int k, int n) {
  int min_days = INT_MAX;

  std::sort(weights.begin(), weights.end());
  std::sort(trucks.begin(), trucks.end());
  std::vector<std::vector<int>> permulation = weights;
  if (trucks[n - 1][0] < weights[k - 1][0]) {
    return -1;
  }
  do {
    int days = FindDays(trucks, weights, k, n);
    if (days < min_days) {
      min_days = days;
      permulation = weights;
    }
  } while (std::next_permutation(weights.begin(), weights.end()));

  FindDays(trucks, permulation, k, n, 1);
  return min_days;
}

int main() {
  std::ifstream fin;
  fin.open("input.txt");

  int n;
  int k;
  while (fin >> n >> k) {
    ans.clear();

    std::vector<int> tr(n);
    for (int i = 0; i < n; i++) {
      fin >> tr[i];
    }
    std::vector<int> w(k);
    for (int i = 0; i < k; i++) {
      fin >> w[i];
    }

    std::vector<std::vector<int>> trucks;
    for (int i = 0; i < n; i++) {
      std::vector<int> pair{tr[i], i};
      trucks.push_back(pair);
    }
    std::vector<std::vector<int>> weights;
    for (int i = 0; i < k; i++) {
      std::vector<int> pair{w[i], i};
      weights.push_back(pair);
    }

    int days = FindMinDays(trucks, weights, k, n);
    std::cout << days << "\n";
    for (int i = 0; i < days; i++) {
      for (int j = 0; j < (int)ans[i].size(); j++) {
        std::cout << ans[i][j] << " ";
      }
      std::cout << "\n";
    }
  }
}