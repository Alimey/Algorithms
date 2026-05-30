#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::vector<int> timing, process, jump;
std::vector<std::pair<int, int>> ans;
std::unordered_map<int, std::unordered_set<int>> graph;
int local_time = 1;

void Dfs(int v, int p = -1) {
  timing[v] = local_time++;
  process[v] = 1;
  jump[v] = timing[v];
  for (int child : graph[v]) {
    if (child == p) {
      continue;
    }
    if (process[child] == 0) {
      Dfs(child, v);
      jump[v] = std::min(jump[v], jump[child]);
      if (jump[child] > timing[v]) {
        ans.emplace_back(v, child);
      }
    } else if (process[child] == 1) {
      jump[v] = std::min(jump[v], timing[child]);
    }
  }
  process[v] = 2;
}

int main() {
  freopen("input.txt", "r", stdin);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  int m;
  std::cin >> n >> m;

  std::vector<bool> need(m, true);
  std::unordered_map<std::string, int> edge_id_map;

  for (int i = 0; i < m; ++i) {
    int u;
    int v;
    std::cin >> u >> v;
    if (u == v) {
      need[i] = false;
      continue;
    }
    u--;
    v--;
    std::string key1 = std::to_string(u) + "," + std::to_string(v);
    std::string key2 = std::to_string(v) + "," + std::to_string(u);

    if (edge_id_map.contains(key1) || edge_id_map.contains(key2)) {
      need[i] = false;
      if (edge_id_map.contains(key1)) {
        int existing_id = edge_id_map[key1];
        need[existing_id] = false;
      } else if (edge_id_map.contains(key2)) {
        int existing_id = edge_id_map[key2];
        need[existing_id] = false;
      }
    } else {
      graph[u].insert(v);
      graph[v].insert(u);
      edge_id_map[key1] = i;
      edge_id_map[key2] = i;
    }
  }

  timing.resize(n);
  process.resize(n);
  jump.resize(n);

  for (int i = 0; i < n; ++i) {
    if (process[i] == 0) {
      Dfs(i);
    }
  }

  std::vector<int> bridges;
  for (auto &p : ans) {
    std::string key = std::to_string(p.first) + "," + std::to_string(p.second);
    int id = edge_id_map[key];
    if (need[id]) {
      bridges.push_back(id + 1);
    }
  }

  std::sort(bridges.begin(), bridges.end());
  std::cout << bridges.size() << "\n";
  for (int id : bridges) {
    std::cout << id << " ";
  }
  std::cout << std::endl;

  return 0;
}