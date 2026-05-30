#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

int ReversedLowerBound(const std::vector<int>& array, int value) {
  int left = 0;
  int right = static_cast<int>(array.size()) - 1;
  int ans = -1;

  while (left <= right) {
    int middle = left + (right - left) / 2;
    if (array[middle] <= value) {
      ans = middle;
      right = middle - 1;
    } else {
      left = middle + 1;
    }
  }

  return ans;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  freopen("input.txt", "r", stdin);

  const int cPositiveInf = INT_MAX;
  const int cNegativeInf = INT_MIN;

  int n_size;
  std::cin >> n_size;
  std::vector<int> array(n_size);
  for (int i = 0; i < n_size; ++i) {
    std::cin >> array[i];
  }

  std::vector<int> dp(n_size + 1, cNegativeInf);
  std::vector<int> prev(n_size, -1);
  std::vector<int> pos(n_size + 1, -1);
  dp[0] = cPositiveInf;

  int len = 0;

  for (int i = 0; i < n_size; ++i) {
    int ind = ReversedLowerBound(dp, array[i]);
    dp[ind] = array[i];
    pos[ind] = i;
    prev[i] = pos[ind - 1];
    len = std::max(len, ind);
  }

  // восстанавливаем ответ
  std::vector<int> ans;
  for (int i = pos[len]; i >= 0;) {
    ans.push_back(i + 1);
    i = prev[i];
  }
  std::reverse(ans.begin(), ans.end());
  std::cout << len << "\n";
  for (int i = 0; i < len; ++i) {
    std::cout << ans[i] << " ";
  }
}