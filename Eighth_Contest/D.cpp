#include <iostream>
#include <vector>

int n;
int m;

const int cInf = 30000;

std::vector<int>
FordBellman(const std::vector<std::vector<std::pair<int, int>>> &graph) {
  std::vector<int> distances(n, cInf);

  std::vector<std::vector<int>> dp(n, std::vector<int>(n, cInf));
  dp[0][0] = 0;

  for (int k = 1; k < n; ++k) {
    for (int u = 0; u < n; ++u) {
      if (dp[k - 1][u] == cInf) {
        continue;
      }
      for (auto [neighbour, weight] : graph[u]) {
        dp[k][neighbour] = std::min(dp[k][neighbour], dp[k - 1][u] + weight);
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int k = 0; k < n; ++k) {
      distances[i] = std::min(distances[i], dp[k][i]);
    }
  }

  return distances;
}

int main() {
  freopen("input.txt", "r", stdin);

  std::cin >> n >> m;

  std::vector<std::vector<std::pair<int, int>>> graph(n);

  for (int i = 0; i < m; ++i) {
    int u;
    int v;
    int c;
    std::cin >> u >> v >> c;
    --u;
    --v;

    graph[u].push_back({v, c});
  }

  std::vector<int> ans = FordBellman(graph);

  for (int x : ans) {
    std::cout << x << " ";
  }
}