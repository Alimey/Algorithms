#include <algorithm>
#include <iostream>
#include <vector>

#define Graph std::vector<std::vector<Edge>>
#define ll long long

const ll cInf = 1e9;

struct Edge {
  ll to;
  ll cap;
  ll rev;
  ll edge_numb;
};

ll node_count;
ll edge_count;
Graph graph;

ll DFS(ll v, std::vector<ll>& visited, ll flow) {
  if (v == node_count - 1) {
    return flow;
  }

  visited[v] = 1;

  for (ll i = 0; i < static_cast<ll>(graph[v].size()); ++i) {
    Edge& e = graph[v][i];

    if (visited[e.to] == 0 && e.cap > 0) {
      ll min_flow = std::min(flow, e.cap);
      ll pushed = DFS(e.to, visited, min_flow);

      if (pushed > 0) {
        e.cap -= pushed;
        graph[e.to][e.rev].cap += pushed;
        return pushed;
      }
    }
  }

  return 0;
}

void AddEdge(ll from, ll to, int cap, Graph& graph, int i) {
  ll save_from = graph[from].size();
  ll save_to = graph[to].size();

  graph[from].push_back(Edge{to, cap, save_to, i + 1});
  graph[to].push_back(Edge{from, 0, save_from, -1});
}

int main() {
  freopen("input.txt", "r", stdin);

  std::cin >> node_count;
  std::cin >> edge_count;

  graph.resize(node_count);

  for (ll i = 0; i < edge_count; ++i) {
    ll from;
    ll to;
    ll cap;

    std::cin >> from;
    std::cin >> to;
    std::cin >> cap;

    --from;
    --to;

    AddEdge(from, to, cap, graph, i);
    AddEdge(to, from, cap, graph, i);
  }

  ll total_flow = 0;
  std::vector<int> ans;

  while (true) {
    std::vector<ll> visited(node_count);
    ll pushed = DFS(0, visited, cInf);

    if (pushed == 0) {
      for (ll i = 0; i < node_count; ++i) {
        if (visited[i] == 1) {
          for (auto& e : graph[i]) {
            if (visited[e.to] == 1) {
              continue;
            }
            if (e.edge_numb > 0) {
              ans.push_back(e.edge_numb);
            }
          }
        }
      }
      break;
    }

    total_flow += pushed;
  }

  std::sort(ans.begin(), ans.end());
  std::cout << ans.size() << " " << total_flow << "\n";
  for (auto x : ans) {
    std::cout << x << " ";
  }
}
