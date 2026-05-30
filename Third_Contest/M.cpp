#include <iostream>
#include <queue>
#include <vector>

void Check(
    std::priority_queue<std::pair<size_t, size_t>,
                        std::vector<std::pair<size_t, size_t>>,
                        std::greater<std::pair<size_t, size_t>>>& pq,
    std::priority_queue<std::pair<size_t, size_t>,
                        std::vector<std::pair<size_t, size_t>>,
                        std::greater<std::pair<size_t, size_t>>>& to_delete) {
  while (!pq.empty() && pq.top() == to_delete.top()) {
    pq.pop();
    to_delete.pop();
  }
}

std::pair<size_t, size_t> IsFirstWin(std::vector<size_t> circle, size_t n) {
  if (n == 0) {
    return {0, 0};
  }
  size_t window_size = n / 2 + n % 2;
  std::vector<size_t> left_borders;
  size_t window_sum = 0;
  for (size_t i = 0; i < window_size; ++i) {
    window_sum += circle[i];
  }
  for (size_t i = 0; i < n; i++) {
    left_borders.push_back(window_sum);
    window_sum -= circle[i];
    window_sum += circle[(i + window_size) % n];
  }
  std::vector<std::pair<size_t, size_t>> minimums_for_first;
  std::priority_queue<std::pair<size_t, size_t>,
                      std::vector<std::pair<size_t, size_t>>,
                      std::greater<std::pair<size_t, size_t>>>
      pq;
  std::priority_queue<std::pair<size_t, size_t>,
                      std::vector<std::pair<size_t, size_t>>,
                      std::greater<std::pair<size_t, size_t>>>
      to_delete;
  for (size_t i = window_size + 1 - n % 2; i < n; ++i) {
    pq.push({left_borders[i], i});
  }
  for (size_t i = 0; i < n; ++i) {
    pq.push({left_borders[i], i});
    minimums_for_first.push_back(pq.top());
    to_delete.push(
        {left_borders[(window_size + i + 1 - n % 2) % n], (window_size + i + 1 - n % 2) % n});
    Check(pq, to_delete);
  }
  std::pair<size_t, size_t> max_min = minimums_for_first[0];
  for (size_t i = 1; i < n; ++i) {
    if (max_min.first < minimums_for_first[i].first) {
      max_min = minimums_for_first[i];
    }
  }
  size_t second_sum = left_borders[(max_min.second + window_size) % n];
  if (n % 2 != 0) {
    second_sum -= circle[max_min.second];
  }
  return {max_min.first, second_sum};
}

int main() {
  freopen("C:/Users/Alimey/Desktop/programming/Algorithms_Problems/Third_Contest/input.txt", "r", stdin);
  size_t n;
  std::cin >> n;
  std::vector<size_t> circle(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> circle[i];
  }
  std::pair<size_t, size_t> ans = IsFirstWin(circle, n);
  std::cout << ans.first << " " << ans.second;
}