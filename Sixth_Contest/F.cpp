#include <algorithm>
#include <climits>
#include <iostream>
#include <unordered_map>
#include <vector>

struct Object {
  int weight;
  int price;
  int color;
};

int main() {
  freopen("input.txt", "r", stdin);
  std::ios_base::sync_with_stdio(false);

  int n;
  int g;
  int m;

  std::cin >> n >> g >> m;

  std::vector<Object> objects;

  for (int i = 0; i < n; ++i) {
    Object obj;
    std::cin >> obj.weight >> obj.price >> obj.color;
    objects.push_back(obj);
  }

  std::unordered_map<int, std::vector<int>> mp;
  for (int i = 0; i < n; ++i) {
    mp[objects[i].color].push_back(i);
  }

  std::vector<std::vector<int>> dp(g + 1, std::vector<int>(m + 1));

  for (int i = 1; i <= g; ++i) {
    for (int j = 1; j <= m; ++j) {
      std::vector<int>& indecies = mp[i];
      dp[i][j] = dp[i - 1][j];
      for (auto k : indecies) {
        if (j - objects[k].weight >= 0 &&
            dp[i - 1][j - objects[k].weight] + objects[k].price > dp[i][j]) {
          dp[i][j] = dp[i - 1][j - objects[k].weight] + objects[k].price;
        }
      }
    }
  }

  std::cout << dp[g][m];
}