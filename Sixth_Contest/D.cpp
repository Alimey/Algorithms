#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  freopen("input.txt", "r", stdin);
  std::ios_base::sync_with_stdio(false);

  std::string s;
  std::string t;
  std::cin >> s >> t;

  int n = static_cast<int>(s.size());
  int m = static_cast<int>(t.size());

  std::vector<std::vector<int>> dp;
  std::vector<std::vector<int>> prev;
  // 1 - получено из dp[i-1][j]
  // 2 - получено из dp[i][j-1]
  // 3 - получено из dp[i-1][j-1]
  for (int i = 0; i < n + 1; ++i) {
    dp.push_back(std::vector<int>(m + 1));
    prev.push_back(std::vector<int>(m + 1));
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (s[i - 1] != t[j - 1] && dp[i - 1][j] > dp[i][j - 1]) {
        dp[i][j] = dp[i - 1][j];
        prev[i][j] = 1;
        continue;
      }
      if (s[i - 1] != t[j - 1] && dp[i - 1][j] <= dp[i][j - 1]) {
        dp[i][j] = dp[i][j - 1];
        prev[i][j] = 2;
        continue;
      }
      dp[i][j] = dp[i - 1][j - 1] + 1;
      prev[i][j] = 3;
    }
  }

  std::cout << dp[n][m] << "\n";

  int i = n;
  int j = m;
  std::vector<int> ans_s;
  std::vector<int> ans_t;
  while (dp[i][j] > 0) {
    if (prev[i][j] == 1) {
      --i;
      continue;
    }
    if (prev[i][j] == 2) {
      --j;
      continue;
    }
    ans_s.push_back(i);
    ans_t.push_back(j);
    --i;
    --j;
  }
  std::reverse(ans_s.begin(), ans_s.end());
  std::reverse(ans_t.begin(), ans_t.end());
  for (int x : ans_s) {
    std::cout << x << " ";
  }
  std::cout << "\n";
  for (int x : ans_t) {
    std::cout << x << " ";
  }
}