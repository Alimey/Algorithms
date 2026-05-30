#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

const size_t cTwo = 1'073'741'824;

int main() {
  std::ifstream fin;
  fin.open("input.txt");
  int n;
  int k;
  fin >> n >> k;
  int a0;
  int x;
  int y;
  fin >> a0 >> x >> y;
  std::priority_queue<size_t, std::vector<size_t>, std::greater<size_t>> spq;
  std::priority_queue<size_t> gpq;
  size_t a_last = a0;
  for (size_t i = 0; i < n; i++) {
    size_t ai = (x * a_last + y) % cTwo;
    if (gpq.size() < k) {
      gpq.push(ai);
      a_last = ai;
      continue;
    }
    if (ai < gpq.top()) {
      gpq.pop();
      gpq.push(ai);
    }
    a_last = ai;
  }
  for (size_t i = 0; i < k; i++) {
    spq.push(gpq.top());
    gpq.pop();
  }
  for (size_t i = 0; i < k; i++) {
    std::cout << spq.top() << " ";
    spq.pop();
  }
}