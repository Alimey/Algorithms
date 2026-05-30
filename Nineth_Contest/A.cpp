#include <iostream>
#include <vector>

#define graph std::vector<std::vector<int>>

const int cInf = 251;

std::vector<int> used(cInf);

bool DFS(int v, std::vector<int>& mtch, const graph& edges) {
  if (used[v] != 0) {
    return false;
  }

  used[v] = 1;

  for (int neigh : edges[v]) {
    if (mtch[neigh] == -1 || DFS(mtch[neigh], mtch, edges)) {
      mtch[neigh] = v;
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

  graph edges(cInf);
  std::vector<int> mtch(cInf, -1);

  for (int i = 0; i < n; ++i) {
    int t;
    while (std::cin >> t, t != 0) {
      edges[i].push_back(--t);
    }
  }

  int count = 0;
  for (int i = 0; i < n; ++i) {
    std::fill(used.begin(), used.end(), 0);
    if (DFS(i, mtch, edges)) {
      ++count;
    }
  }

  std::cout << count << "\n";
  for (int i = 0; i < m; ++i) {
    if (mtch[i] != -1) {
      std::cout << mtch[i] + 1 << " " << i + 1 << "\n";
    }
  }
}