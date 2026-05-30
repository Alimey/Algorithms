#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int IsThereCycle(int n, int v, std::vector<int>& colors,
                 std::vector<int>& parents,
                 std::unordered_map<int, std::unordered_set<int>>& graph) {
  colors[v] = 1;

  if (!graph.contains(v)) {
    colors[v] = 2;
    return -1;
  }

  for (auto child : graph[v]) {
    parents[child] = v;
    if (colors[child] == 1) {
      return child;
    }
    if (colors[child] == 0) {
      int result = IsThereCycle(n, child, colors, parents, graph);
      if (result != -1) {
        return result;
      }
    }
  }

  colors[v] = 2;
  return -1;
}

int main() {
  freopen("input.txt", "r", stdin);

  int n;
  int m;
  std::cin >> n >> m;

  std::unordered_map<int, std::unordered_set<int>> graph;
  std::vector<int> parents(n);
  std::vector<int> colors(n);

  for (int i = 0; i < m; ++i) {
    int u;
    int v;
    std::cin >> u >> v;
    graph[u - 1].insert(v - 1);
  }

  int stop = -1;
  for (int i = 0; i < n; ++i) {
    if (colors[i] == 0) {
      stop = IsThereCycle(n, i, colors, parents, graph);
      if (stop != -1) {
        break;
      }
    }
  }

  if (stop != -1) {
    std::cout << "YES\n";
    std::vector<int> cycle;
    int current = stop;
    do {
      cycle.push_back(current + 1);
      current = parents[current];
    } while (current != stop);
    cycle.push_back(stop + 1);
    for (int i = cycle.size() - 1; i > 0; --i) {
      std::cout << cycle[i] << " ";
    }
  } else {
    std::cout << "NO";
  }
}
