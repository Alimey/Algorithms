#include <iostream>
#include <vector>

int main() {
  freopen("input.txt", "r", stdin);

  int n;
  std::cin >> n;

  std::vector<std::vector<int>> graph(n, std::vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> graph[i][j];
    }
  }

  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        graph[i][j] = (graph[i][j] | (graph[i][k] & graph[k][j]));
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cout << graph[i][j] << " ";
    }
    std::cout << "\n";
  }
}