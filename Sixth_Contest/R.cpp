#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

const int cInf = INT_MAX;

int main() {
  std::ios_base::sync_with_stdio(false);
  freopen("input.txt", "r", stdin);

  int n;
  std::cin >> n;
  std::vector<std::vector<int>> a(n, std::vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> a[i][j];
    }
  }

  std::vector<std::vector<std::pair<int, int>>> dp(
      1 << n, std::vector<std::pair<int, int>>(n, {cInf, -1}));
  for (int i = 0; i < n; ++i) {
    dp[1 << i][i].first = 0;
  }

  for (int mask = 1; mask < (1 << n); ++mask) {
    for (int j = 0; j < n; ++j) {
      if ((mask & (1 << j)) == 0) {
        continue;
      }

      for (int k = 0; k < n; ++k) {
        if ((mask & (1 << k)) == (1 << k) && j != k &&
            dp[mask][j].first > dp[mask ^ (1 << j)][k].first + a[j][k]) {
          dp[mask][j] = {dp[mask ^ (1 << j)][k].first + a[j][k], k};
        }
      }
    }
  }

  int ans_index = 0;
  for (int i = 0; i < n; ++i) {
    ans_index = dp[(1 << n) - 1][ans_index].first > dp[(1 << n) - 1][i].first
                    ? i
                    : ans_index;
  }

  int ans_len = dp[(1 << n) - 1][ans_index].first;
  std::vector<int> ans_seq;

  int mask = (1 << n) - 1;
  for (; ans_index >= 0;) {
    ans_seq.push_back(ans_index);
    mask -= (1 << ans_index);
    ans_index = dp[mask + (1 << ans_index)][ans_index].second;
  }

  std::cout << ans_len << "\n";
  for (int i = 0; i < n; ++i) {
    std::cout << ans_seq[i] + 1 << " ";
  }
}