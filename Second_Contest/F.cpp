#include <algorithm>
#include <climits>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

uint64_t CountDistance(std::vector<uint32_t>& points, uint32_t y) {
  uint64_t s = 0;
  for (uint32_t x : points) {
    s += y > x ? y - x : x - y;
  }
  return s;
}

uint32_t cur = 0;
uint32_t NextRand24(int a, int b) {
  cur = cur * a + b;
  const int cEight = 8;
  return cur >> cEight;
}
uint32_t NextRand32(int a, int b) {
  int x = NextRand24(a, b);
  int y = NextRand24(a, b);
  const int cEight = 8;
  return (x << cEight) ^ y;
}

int main() {
  std::ifstream fin;
  fin.open("input.txt");

  int n;
  fin >> n;
  int a;
  int b;
  fin >> a >> b;
  std::vector<uint32_t> points(n);
  for (int i = 0; i < n; i++) {
    points[i] = NextRand32(a, b);
  }
  std::nth_element(points.begin(), points.begin() + (n - 1) / 2, points.end());
  std::cout << CountDistance(points, points[(n - 1) / 2]);
}
