#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Pair {
  int vertice;
  int time;

  bool operator<(const Pair& another) const { return time > another.time; }
};

const int cInf = 1e5;

void Dfs(int v, std::vector<int>& visited,
         std::unordered_map<int, std::unordered_set<int>>& graph,
         std::vector<Pair>& ids) {
  visited[v] = 1;
  static int id = 0;
  for (int u : graph[v]) {
    if (visited[u] == 0) {
      Dfs(u, visited, graph, ids);
    }
  }
  ids[v] = {v, id++};
}

void TopologicalSort(int n,
                     std::unordered_map<int, std::unordered_set<int>>& graph,
                     std::vector<Pair>& ids) {
  std::vector<int> visited(n);
  for (int i = 0; i < n; ++i) {
    if (visited[i] == 0) {
      Dfs(i, visited, graph, ids);
    }
  }
}

bool IsCyclicFrom(int v,
                  std::unordered_map<int, std::unordered_set<int>>& graph,
                  std::vector<int>& colors) {
  colors[v] = 1;
  bool is_cyclic = false;
  for (int u : graph[v]) {
    if (colors[u] == 1) {
      return true;
    }
    if (colors[u] == 0) {
      is_cyclic = IsCyclicFrom(u, graph, colors) || is_cyclic;
    }
  }
  colors[v] = 2;
  return is_cyclic;
}

bool IsCyclic(int n, std::unordered_map<int, std::unordered_set<int>>& graph) {
  std::vector<int> colors(cInf);
  for (int i = 0; i < n; ++i) {
    if (colors[i] == 0 && IsCyclicFrom(i, graph, colors)) {
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

  std::unordered_map<int, std::unordered_set<int>> graph;

  for (int i = 0; i < m; ++i) {
    int u;
    int v;
    std::cin >> u >> v;
    graph[u - 1].insert(v - 1);
  }

  if (IsCyclic(n, graph)) {
    std::cout << -1;
    return 0;
  }

  std::vector<Pair> ids(n);
  TopologicalSort(n, graph, ids);

  std::sort(ids.begin(), ids.end());
  for (int i = 0; i < n; ++i) {
    std::cout << ids[i].vertice + 1 << " ";
  }
}