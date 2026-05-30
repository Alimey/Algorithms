#include <algorithm>
#include <climits>
#include <iostream>
#include <optional>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Graph {
  std::vector<std::vector<std::pair<int, int>>> storage;
  std::vector<std::pair<int, int>> vertex_params;

  std::vector<int> colors;
  std::vector<int> ans;

  int x_global = INT_MAX;

  void DFS(int vertice, int parent = -1) {
    colors[vertice] = 1;

    if (x_global != INT_MAX) {
      return;
    }

    for (auto [neighbor, weight] : storage[vertice]) {
      if (neighbor == parent) {
        continue;
      }

      if (colors[neighbor] == 1 &&
          vertex_params[vertice].second == vertex_params[neighbor].second) {
        x_global = (weight - vertex_params[vertice].first -
                    vertex_params[neighbor].first) /
                  2 * vertex_params[vertice].second;
        return;
      }

      if (colors[neighbor] == 0) {
        auto [a_curr, b_curr] = vertex_params[vertice];
        int weight = weight;

        int a_neighbor = weight - a_curr;
        int b_neighbor = -b_curr;
        vertex_params[neighbor] = {a_neighbor, b_neighbor};

        DFS(neighbor, vertice);
      }
    }
    colors[vertice] = 2;
  }

  bool CheckValidation(int x_candidate, int n_size) {
    std::vector<int> used(n_size + 1);
    bool valid = true;
    for (int j = 0; j < n_size; ++j) {
      auto [aj, bj] = vertex_params[j];
      int value = aj + bj * x_candidate;
      if (value < 1 || value > n_size || used[value] == 1) {
        valid = false;
        break;
      }
      used[value] = 1;
    }
    return valid;
  }

  int CalculateX(int n_size) {
    int max_a_from_minus_b = INT_MIN;
    int x_minus = INT_MIN;

    int max_a_from_plus_b = INT_MIN;
    int x_plus = INT_MIN;
    for (int i = 0; i < n_size; ++i) {
      auto [a, b] = vertex_params[i];

      if (a > max_a_from_minus_b && b < 0) {
        max_a_from_minus_b = a;
        x_minus = (n_size - a) * b;
      }
      if (a > max_a_from_plus_b && b > 0) {
        max_a_from_plus_b = a;
        x_plus = (n_size - a) * b;
      }
    }

    return CheckValidation(x_plus, n_size) ? x_plus : x_minus;
  }

  void AssignValues(int n_size) {
    for (int i = 0; i < n_size; ++i) {
      auto [a, b] = vertex_params[i];
      ans[i] = a + b * x_global;
    }
  }

  void AssignValuesReady(int n_size, int vertice = 0) {
    static std::vector<int> visited(n_size);
    visited[vertice] = 1;
    for (auto [neighbour, weight] : storage[vertice]) {
      if (visited[neighbour] == 0) {
        ans[neighbour] = weight - ans[vertice];
        AssignValuesReady(n_size, neighbour);
      }
    }
  }

};

int main() {
  freopen("input.txt", "r", stdin);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n_size;
  int m_size;
  std::cin >> n_size >> m_size;

  Graph graph;

  graph.storage.resize(n_size);
  graph.vertex_params.resize(n_size);
  graph.colors.resize(n_size, 0);
  graph.ans.resize(n_size);

  for (int i = 0; i < m_size; ++i) {
    int first_vertice;
    int second_vertice;
    int weight;
    std::cin >> first_vertice >> second_vertice >> weight;
    first_vertice--;
    second_vertice--;
    graph.storage[first_vertice].push_back({second_vertice, weight});
    graph.storage[second_vertice].push_back({first_vertice, weight});
  }

  graph.vertex_params[0] = {0, 1};
  graph.DFS(0);

  if (graph.x_global != INT_MAX) {
    graph.ans[0] = graph.x_global;
    graph.AssignValuesReady(n_size);
  } else {
    graph.x_global = graph.CalculateX(n_size);

    graph.ans[0] = graph.x_global;
    graph.AssignValues(n_size);
  }

  for (int num : graph.ans) {
    std::cout << num << " ";
  }
}