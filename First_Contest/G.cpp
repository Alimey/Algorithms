#include <iostream>

int Count(int n, int k) {
  if (n <= k) {
    return 1;
  }
  int first = n / 2;
  int second = n - n / 2;
  return Count(first, k) + Count(second, k);
}

int main() {
  int n;
  int k;
  std::cin >> n >> k;
  std::cout << Count(n, k);
}