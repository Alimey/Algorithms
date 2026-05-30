#include <iostream>
#include <stack>
#include <vector>

size_t MaxSquare(std::vector<size_t>& h, size_t n) {
  size_t it = 0;
  size_t max_square = 0;
  std::stack<std::pair<size_t, size_t>> high_and_nearest_lower;
  while (it <= n) {
    if (it < n && (high_and_nearest_lower.empty() ||
                   high_and_nearest_lower.top().first < h[it])) {
      high_and_nearest_lower.push({h[it], it});
      ++it;
      continue;
    }
    if (it < n && (high_and_nearest_lower.top().first == h[it])) {
      ++it;
      continue;
    }
    size_t high = high_and_nearest_lower.top().first;
    size_t left_lower = high_and_nearest_lower.top().second;
    while (!high_and_nearest_lower.empty() &&
           (it == n || high_and_nearest_lower.top().first > h[it])) {
      high = high_and_nearest_lower.top().first;
      left_lower = high_and_nearest_lower.top().second;
      high_and_nearest_lower.pop();
      size_t curr_square = high * (it - left_lower);
      if (curr_square > max_square) {
        max_square = curr_square;
      }
      if (n == it && high_and_nearest_lower.empty()) {
        return max_square;
      }
    }
    high_and_nearest_lower.push({h[it], left_lower});
    it++;
  }
  return max_square;
}

int main() {
  freopen("C:/Users/Alimey/Desktop/programming/Algorithms_Problems/Third_Contest/input.txt", "r", stdin);

  size_t n;
  std::cin >> n;
  std::vector<size_t> h(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> h[i];
  }
  std::cout << MaxSquare(h, n);
}