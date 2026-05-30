#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int Dfs(int v, int i, std::vector<int>& colors,
        std::vector<std::vector<int>>& ans,
        std::unordered_map<int, std::unordered_set<int>>& graph) {
  if (colors[v] == 1) {
    return -1;
  }

  ans[i].push_back(v);

  colors[v] = 1;

  if (!graph.contains(v)) {
    return 1;
  }

  int count = 1;
  for (auto child : graph[v]) {
    if (colors[child] == 0) {
      count += Dfs(child, i, colors, ans, graph);
    }
  }

  return count;
}

int main() {
  freopen("input.txt", "r", stdin);

  int n;
  int m;
  std::cin >> n >> m;

  std::unordered_map<int, std::unordered_set<int>> graph;

  for (int i = 0; i < m; ++i) {
    int u;
    int v;
    std::cin >> u >> v;
    graph[u - 1].insert(v - 1);
    graph[v - 1].insert(u - 1);
  }

  std::vector<int> colors(n);
  std::vector<int> parents(n, -1);

  std::vector<std::vector<int>> ans(n);
  std::vector<int> len_ans;
  int count = 0;
  for (int i = 0; i < n; ++i) {
    if (colors[i] == 0) {
      len_ans.push_back(Dfs(i, count, colors, ans, graph));
      ++count;
    }
  }

  std::cout << count << "\n";
  for (int i = 0; i < count; ++i) {
    std::cout << len_ans[i] << "\n";
    for (size_t j = 0; j < ans[i].size(); ++j) {
      std::cout << ans[i][j] + 1 << " ";
    }
    std::cout << "\n";
  }
}