#include <algorithm>
#include <iostream>
#include <vector>

int Count(const std::vector<int>& a, int n, std::vector<int>& seq) {
  int up = 1;
  int down = 1;
  seq.push_back(a[0]);
  for (int i = 1; i < n; ++i) {
    if (a[i] > a[i - 1]) {
      if (up != down + 1) {
        seq.push_back(a[i]);
      } else {
        seq.back() = a[i];
      }
      up = down + 1;
    } else if (a[i] < a[i - 1]) {
      if (down != up + 1) {
        seq.push_back(a[i]);
      } else {
        seq.back() = a[i];
      }
      down = up + 1;
    }
  }
  return std::max(up, down);
}

int main() {
  freopen("input.txt", "r", stdin);
  std::ios_base::sync_with_stdio(false);

  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }

  std::vector<int> seq;

  int ans = Count(a, n, seq);
  std::cout << ans << "\n";
  for (auto x : seq) {
    std::cout << x << " ";
  }
}