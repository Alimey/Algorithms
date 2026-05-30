#include <iostream>
#include <vector>

int FindMin(std::vector<int>& lmins, std::vector<int>& rmins, int l, int r) {
  return std::min(lmins[l], rmins[r]);
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> arr(n);
  for (int i = 0; i < n; i++) {
    std::cin >> arr[i];
  }

  std::vector<int> lmins(n);
  std::vector<int> rmins(n);
  lmins[0] = arr[0];
  rmins[n - 1] = arr[n - 1];
  for (int i = 1; i < n; i++) {
    lmins[i] = std::min(lmins[i - 1], arr[i]);
    rmins[n - i - 1] = std::min(rmins[n - i], arr[n - i - 1]);
  }

  int q;
  std::cin >> q;
  std::vector<int> ans;
  for (int i = 0; i < q; i++) {
    int l;
    int r;
    std::cin >> l >> r;
    ans.push_back(FindMin(lmins, rmins, l - 1, r - 1));
  }

  for (int x : ans) {
    std::cout << x << "\n";
  }
}