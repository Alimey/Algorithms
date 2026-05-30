#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::vector<int> tin;
std::vector<int> up;
std::vector<bool> visited;
std::unordered_set<int> ans;
int timer;

void Dfs(int v, int parent,
         const std::unordered_map<int, std::unordered_set<int>>& graph) {
  visited[v] = true;
  tin[v] = up[v] = timer++;
  int children = 0;

  for (int neighbor : graph.at(v)) {
    if (neighbor == parent) {
      continue;
    }

    if (visited[neighbor]) {
      up[v] = std::min(up[v], tin[neighbor]);
    } else {
      Dfs(neighbor, v, graph);
      up[v] = std::min(up[v], up[neighbor]);

      if (up[neighbor] >= tin[v] && parent != -1) {
        ans.insert(v);
      }
      children++;
    }
  }

  if (parent == -1 && children > 1) {
    ans.insert(v);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n;
  int m;
  std::cin >> n >> m;

  std::unordered_map<int, std::unordered_set<int>> graph;
  for (int i = 0; i < m; ++i) {
    int u;
    int v;
    std::cin >> u >> v;
    u--;
    v--;
    graph[u].insert(v);
    graph[v].insert(u);
  }

  for (int i = 0; i < n; ++i) {
    if (graph.find(i) == graph.end()) {
      graph[i] = std::unordered_set<int>();
    }
  }

  timer = 0;
  tin.resize(n);
  up.resize(n);
  visited.assign(n, false);

  for (int i = 0; i < n; ++i) {
    if (!visited[i]) {
      Dfs(i, -1, graph);
    }
  }

  std::vector<int> vec_ans;
  for (int point : ans) {
    vec_ans.push_back(point);
  }

  std::sort(vec_ans.begin(), vec_ans.end());
  std::cout << vec_ans.size() << "\n";
  for (int point : vec_ans) {
    std::cout << point + 1 << " ";
  }
}
