#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::vector<int> timing;
std::vector<int> process;
std::vector<int> jump;
std::vector<int> component_id;
std::vector<std::pair<int, int>> ans;
std::unordered_map<int, std::unordered_set<int>> graph;
int local_time = 1;
int current_component = 0;

void FindBridges(int v, int p = -1) {
  timing[v] = local_time++;
  process[v] = 1;
  jump[v] = timing[v];
  for (int child : graph[v]) {
    if (child == p) {
      continue;
    }
    if (process[child] == 0) {
      FindBridges(child, v);
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

void ColorComponents(int v, int color) {
  component_id[v] = color;
  for (int child : graph[v]) {
    bool is_bridge = std::find(ans.begin(), ans.end(),
                               std::make_pair(v, child)) != ans.end() ||
                     std::find(ans.begin(), ans.end(),
                               std::make_pair(child, v)) != ans.end();
    if (!is_bridge && component_id[child] == -1) {
      ColorComponents(child, color);
    }
  }
}

int main() {
  freopen("input.txt", "r", stdin);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  int m;
  std::cin >> n >> m;

  timing.resize(n);
  process.resize(n);
  jump.resize(n);
  component_id.resize(n, -1);

  std::vector<std::pair<int, int>> edges;
  for (int i = 0; i < m; ++i) {
    int u;
    int v;
    std::cin >> u >> v;
    u--;
    v--;
    if (u != v) {
      graph[u].insert(v);
      graph[v].insert(u);
    }
    edges.emplace_back(u, v);
  }

  for (int i = 0; i < n; ++i) {
    if (process[i] == 0) {
      FindBridges(i);
    }
  }

  for (int i = 0; i < n; ++i) {
    if (component_id[i] == -1) {
      ColorComponents(i, current_component++);
    }
  }

  std::unordered_map<int, std::unordered_set<int>> component_tree;
  for (auto& bridge : ans) {
    int u = component_id[bridge.first];
    int v = component_id[bridge.second];
    component_tree[u].insert(v);
    component_tree[v].insert(u);
  }

  int leaves = 0;
  for (auto& node : component_tree) {
    if (node.second.size() == 1) {
      leaves++;
    }
  }

  if (current_component == 1) {
    std::cout << 0;
  } else {
    std::cout << (leaves + 1) / 2;
  }
}