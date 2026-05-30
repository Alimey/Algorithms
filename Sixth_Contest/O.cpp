#include <iostream>
#include <unordered_map>
#include <vector>

const int cMod = 1e9 + 7;

int main() {
  freopen("input.txt", "r", stdin);
  std::ios_base::sync_with_stdio(false);

  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }

  std::vector<long long> dp(n + 1);
  std::unordered_map<int, int> last;
  dp[0] = 1;

  for (int i = 1; i <= n; ++i) {
    int num = a[i - 1];
    dp[i] = (2 * dp[i - 1]) % cMod;

    if (last.contains(num)) {
      int prev_index = last[num];
      dp[i] = (dp[i] - dp[prev_index - 1] + cMod) % cMod;
    }

    last[num] = i;
  }

  std::cout << (dp[n] - 1 + cMod) % cMod;
}