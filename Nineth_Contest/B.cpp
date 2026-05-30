#include <iostream>
#include <string>
#include <vector>

int n;
int m;
int a;
int b;

bool DFS(int u, const std::vector<std::vector<int>>& graph,
         std::vector<bool>& used, std::vector<int>& matches) {
  used[u] = true;

  for (int v : graph[u]) {
    if (matches[v] < 0 ||
        (!used[matches[v]] && DFS(matches[v], graph, used, matches))) {
      matches[v] = u;
      return true;
    }
  }

  return false;
}

int main() {
  freopen("input.txt", "r", stdin);

  std::cin >> n;
  std::cin >> m;
  std::cin >> a;
  std::cin >> b;

  std::vector<std::string> field(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> field[i];
  }

  int count_free = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (field[i][j] == '*') {
        ++count_free;
      }
    }
  }

  if (a >= 2 * b) {
    std::cout << (count_free * b);
    return 0;
  }

  std::vector<std::vector<int>> left_id(n, std::vector<int>(m, -1));
  std::vector<std::vector<int>> right_id(n, std::vector<int>(m, -1));

  int left_count = 0;
  int right_count = 0;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (field[i][j] == '*') {
        if (((i + j) % 2) == 0) {
          left_id[i][j] = left_count;
          ++left_count;
        } else {
          right_id[i][j] = right_count;
          ++right_count;
        }
      }
    }
  }

  std::vector<std::vector<int>> graph(left_count);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (field[i][j] == '*' && ((i + j) % 2) == 0) {
        int u = left_id[i][j];
        int ni;
        int nj;

        ni = i - 1;
        nj = j;

        if (ni >= 0 && field[ni][nj] == '*') {
          graph[u].push_back(right_id[ni][nj]);
        }

        ni = i + 1;
        nj = j;

        if (ni < n && field[ni][nj] == '*') {
          graph[u].push_back(right_id[ni][nj]);
        }

        ni = i;
        nj = j - 1;

        if (nj >= 0 && field[ni][nj] == '*') {
          graph[u].push_back(right_id[ni][nj]);
        }

        ni = i;
        nj = j + 1;

        if (nj < m && field[ni][nj] == '*') {
          graph[u].push_back(right_id[ni][nj]);
        }
      }
    }
  }

  std::vector<int> matches(right_count, -1);
  int matching = 0;

  for (int u = 0; u < left_count; ++u) {
    std::vector<bool> used(left_count);

    if (DFS(u, graph, used, matches)) {
      ++matching;
    }
  }

  int result = matching * a + (count_free - 2 * matching) * b;
  std::cout << result;
}
