#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

const int cInf = INT_MAX;

struct Well {
  int cabin_pos = -1;
  int paths_len = 0;
};

struct Placement {
  int opt_len = 0;
  int right_border = -1;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  freopen("input.txt", "r", stdin);

  int n;
  int m;
  std::cin >> n >> m;

  std::vector<int> x(n + 1);
  for (int i = 0; i < n; ++i) {
    std::cin >> x[i + 1];
  }

  std::vector<std::vector<Placement>> dp(m + 1, std::vector<Placement>(n + 1));

  std::vector<std::vector<Well>> precount(n + 1, std::vector<Well>(n + 1));

  for (int len = 0; len < n; ++len) {
    for (int i = 1; i <= n - len; ++i) {
      Well well;
      well.cabin_pos = i + len / 2;
      for (int j = i; j <= i + len; ++j) {
        well.paths_len += std::abs(x[j] - x[well.cabin_pos]);
      }
      precount[i][i + len] = well;
    }
  }

  for (int i = 1; i <= n; ++i) {
    dp[1][i].opt_len = precount[1][i].paths_len;
    dp[1][i].right_border = 0;
  }

  for (int i = 2; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      int opt_right = 0;
      int opt_len = cInf;
      for (int k = 1; k < j; ++k) {
        if (dp[i - 1][k].opt_len + precount[k + 1][j].paths_len < opt_len) {
          opt_len = dp[i - 1][k].opt_len + precount[k + 1][j].paths_len;
          opt_right = k;
        }
      }

      if (opt_len != cInf) {
        dp[i][j].opt_len = opt_len;
        dp[i][j].right_border = opt_right;
      }
    }
  }

  std::cout << dp[m][n].opt_len << "\n";

  // восстанавливаем ответ

  int count = m;
  int houses_prefix = n;
  std::vector<int> ans;
  while (count > 0) {
    int right_for_count_minus_one = dp[count][houses_prefix].right_border;
    int pos_count_well =
        precount[right_for_count_minus_one + 1][houses_prefix].cabin_pos;
    ans.push_back(x[pos_count_well]);
    --count;
    houses_prefix = right_for_count_minus_one;
  }
  std::reverse(ans.begin(), ans.end());
  for (int x : ans) {
    std::cout << x << " ";
  }
}