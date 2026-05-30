#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Graph {
  std::vector<std::vector<std::pair<int, int>>> storage;
  std::string vertice_matches;
  std::vector<int> colors;
  std::vector<int> ans;
  std::vector<int> parsed_string;

  void Reset(int n, int m) {
    storage.clear();

    ans.resize(m);
    colors.resize(n);
    storage.resize(n);

    ans.assign(m, 0);
    colors.assign(n, 0);
  }

  bool Dfs(int v) {
    int flag = 0;
    colors[v] = 1;

    for (auto [neighbour, edge_number] : storage[v]) {
      if (colors[neighbour] == 0) {
        std::string edge = std::to_string(neighbour) + ',' + std::to_string(v);
        ans[edge_number] = static_cast<int>(Dfs(neighbour));
        flag = (flag + ans[edge_number]) % 2;
      }
    }

    return (2 + (vertice_matches[v] - '0') - flag) % 2 == 1;
  }

  void Fill(int m) {
    for (int j = 0; j < m; ++j) {
      int u;
      int v;
      std::cin >> u >> v;
      --u;
      --v;
      storage[u].push_back({v, j});
      storage[v].push_back({u, j});
    }
    std::cin >> vertice_matches;
  }

  void Parse() {
    parsed_string.resize(vertice_matches.size());
    for (size_t i = 0; i < vertice_matches.size(); ++i) {
      parsed_string[i] = vertice_matches[i] - '0';
    }
  }
};

int n;
int m;

int main() {
  freopen("input.txt", "r", stdin);
  std::ios::sync_with_stdio(false);

  int t;
  std::cin >> t;

  Graph graph;

  for (int i = 0; i < t; ++i) {
    std::cin >> n >> m;

    graph.Reset(n, m);
    graph.Fill(m);

    bool solution_exists = true;
    for (int i = 0; i < n; ++i) {
      if (graph.colors[i] == 0 && solution_exists) {
        solution_exists = !graph.Dfs(i);
      }
    }

    if (solution_exists) {
      for (int x : graph.ans) {
        std::cout << x;
      }
      std::cout << "\n";
      continue;
    }
    std::cout << "-1\n";
  }
}