#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);

  int n;
  std::cin >> n;
  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1));

  dp[0][0] = 1;

  for (int k = 1; k < n + 1; ++k) {
    for (int s = k; s < n + 1; ++s) {
      for (int i = 0; i <= k / 2; ++i) {
        dp[k][s] += dp[i][s - k];
      }
    }
  }

  int sum = 0;
  for (int i = 0; i < n + 1; ++i) {
    sum += dp[i][n];
  }
  std::cout << sum;
}