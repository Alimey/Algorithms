#include<algorithm>
#include <iostream>
#include <vector>

bool Covers(std::vector<int>& points, int n, int k, int l) {
  int border = points[0] + l;
  int j = 0;
  k--;
  while (k >= 0) {
    while (j < n && points[j] <= border) {
      j++;
    }
    if (j >= n) {
      return true;
    }
    border = points[j] + l;
    k--;
  }
  return false;
}

int main() {
  int n;
  int k;
  std::cin >> n >> k;
  std::vector<int> points(n);
  for (int i = 0; i < n; i++) {
    std::cin >> points[i];
  }
  std::sort(points.begin(), points.end());

  int ans;
  int min = -1;
  int max = points[n - 1] - points[0];
  while (max > min + 1) {
    int mid = (max + min) / 2;
    if (Covers(points, n, k, mid)) {
      max = mid;
    } else {
      min = mid;
    }
  }
  std::cout << max;
}