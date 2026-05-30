#include <iostream>
#include <vector>

#define Graph std::vector<std::vector<int>>

void DFS(int v, std::vector<bool> &left_visited,
         std::vector<bool> &right_visited, const Graph &graph,
         const std::vector<int> &left_matching,
         const std::vector<int> &right_matching) {
  if (v == -1) {
    return;
  }

  if (left_visited[v]) {
    return;
  }

  left_visited[v] = true;

  for (int neighbour : graph[v]) {
    if (neighbour == left_matching[v]) {
      continue;
    }

    if (!right_visited[neighbour]) {
      right_visited[neighbour] = true;
      DFS(right_matching[neighbour], left_visited, right_visited, graph,
          left_matching, right_matching);
    }
  }
}

int main() {
  freopen("input.txt", "r", stdin);

  int left_sz;
  int right_sz;
  std::cin >> left_sz >> right_sz;

  Graph graph(left_sz);

  for (int i = 0; i < left_sz; ++i) {
    int bind_count;
    std::cin >> bind_count;

    for (int j = 0; j < bind_count; ++j) {
      int neighbour;
      std::cin >> neighbour;
      graph[i].push_back(--neighbour);
    }
  }

  std::vector<int> max_matching_right(right_sz, -1);
  std::vector<int> max_matching_left(left_sz, -1);

  for (int i = 0; i < left_sz; ++i) {
    int matching;
    std::cin >> matching;
    max_matching_left[i] = --matching;
    if (matching != -1) {
      max_matching_right[matching] = i;
    }
  }

  std::vector<bool> left_visited(left_sz);
  std::vector<bool> right_visited(right_sz);

  for (int i = 0; i < left_sz; ++i) {
    if (max_matching_left[i] == -1) {
      DFS(i, left_visited, right_visited, graph, max_matching_left,
          max_matching_right);
    }
  }

  int left_ans = 0;
  int right_ans = 0;

  for (int i = 0; i < left_sz; ++i) {
    if (!left_visited[i]) {
      ++left_ans;
    }
  }

  for (int i = 0; i < right_sz; ++i) {
    if (right_visited[i]) {
      ++right_ans;
    }
  }

  std::cout << left_ans + right_ans << "\n";
  std::cout << left_ans << " ";

  for (int i = 0; i < left_sz; ++i) {
    if (!left_visited[i]) {
      std::cout << i + 1 << " ";
    }
  }

  std::cout << "\n" << right_ans << " ";

  for (int i = 0; i < right_sz; ++i) {
    if (right_visited[i]) {
      std::cout << i + 1 << " ";
    }
  }
}