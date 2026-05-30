#include <iostream>
#include <vector>

#define Graph std::vector<std::vector<int>>

bool DFS(int v, const Graph& graph, std::vector<int>& match,
         std::vector<int>& used) {
  if (used[v] != 0) {
    return false;
  }

  used[v] = 1;
  for (int neigh : graph[v]) {
    if (match[neigh] == -1 || DFS(match[neigh], graph, match, used)) {
      match[neigh] = v;
      return true;
    }
  }

  return false;
}

int main() {
  freopen("input.txt", "r", stdin);

  int n;
  int m;
  std::cin >> n >> m;

  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    int u;
    int v;
    std::cin >> u >> v;
    graph[--u].push_back(--v);
  }

  std::vector<int> match(n, -1);
  std::vector<int> used(n, -1);
  int count = 0;

  for (int i = 0; i < n; ++i) {
    used.assign(n, 0);

    if (DFS(i, graph, match, used)) {
      ++count;
    }
  }

  int ans = n - count;
  std::cout << ans;
}