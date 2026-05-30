#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  freopen("input.txt", "r", stdin);
  std::ios_base::sync_with_stdio(false);

  int n;
  int m;
  std::cin >> n >> m;
  std::vector<int> a(n);
  std::vector<int> b(m);

  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }

  for (int j = 0; j < m; ++j) {
    std::cin >> b[j];
  }

  std::vector<std::vector<int>> dp(n, std::vector<int>(m));
  for (int j = 0; j < m; ++j) {
    dp[0][j] = (a[0] == b[j]) ? 1 : 0;
  }

  for (int i = 1; i < n; ++i) {
    int val = 0;

    for (int j = 0; j < m; ++j) {
      dp[i][j] = dp[i - 1][j];

      if (val < dp[i - 1][j] && b[j] < a[i]) {
        val = dp[i - 1][j];
        continue;
      }

      if (a[i] == b[j] && dp[i - 1][j] < val + 1) {
        dp[i][j] = val + 1;
      }
    }
  }

  int ans = -1;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (ans < dp[i][j]) {
        ans = dp[i][j];
      }
    }
  }

  std::cout << ans;
}