#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#define ll long long

const ll cInf = 1e13;

struct Triplet {
  ll to;
  ll cap;
  ll flow;
  ll rev_edge;
  ll edge_number;
};

struct Graph {
  std::vector<std::vector<Triplet>> storage;
  ll vert_num;
  ll edge_num;
};

bool BFS(std::vector<ll>& dist, const Graph& graph) {
  dist[0] = 0;
  std::queue<ll> queue;
  queue.push(0);

  while (!queue.empty()) {
    ll curr = queue.front();
    queue.pop();

    for (auto [neigh, cap, flow, rev_edge, skip] : graph.storage[curr]) {
      if (dist[neigh] != cInf || cap <= flow) {
        continue;
      }

      dist[neigh] = dist[curr] + 1;
      queue.push(neigh);
    }
  }

  return dist[graph.vert_num - 1] == cInf;
}

ll DFS(ll min_cap, Graph& graph, const std::vector<ll>& dist,
       std::vector<ll>& first, ll start = 0) {
  if (start == graph.vert_num - 1 || min_cap == 0) {
    return min_cap;
  }

  for (; first[start] < static_cast<ll>(graph.storage[start].size());
       ++first[start]) {
    auto& edge = graph.storage[start][first[start]];
    if (dist[edge.to] == dist[start] + 1 && edge.cap > edge.flow) {
      ll delta = DFS(std::min(min_cap, edge.cap - edge.flow), graph, dist,
                     first, edge.to);
      if (delta > 0) {
        edge.flow += delta;
        graph.storage[edge.to][edge.rev_edge].flow -= delta;
        return delta;
      }
    }
  }

  return 0;
}

ll FindMaxFlow(Graph& graph) {
  ll ans = 0;
  bool finished = false;

  while (!finished) {
    std::vector<ll> dist(graph.vert_num, cInf);
    finished = BFS(dist, graph);

    if (finished) {
      break;
    }

    std::vector<ll> first(graph.vert_num);
    ll block_flow = DFS(cInf, graph, dist, first);

    while (block_flow != 0) {
      ans += block_flow;
      block_flow = DFS(cInf, graph, dist, first);
    }
  }

  return ans;
}

void FillAnsVec(std::vector<ll>& edge_flow, const Graph& graph) {
  for (ll vert = 0; vert < graph.vert_num; ++vert) {
    for (const auto& edge_from_vert : graph.storage[vert]) {
      if (edge_from_vert.edge_number == -1) {
        continue;
      }

      edge_flow[edge_from_vert.edge_number] = edge_from_vert.flow;
    }
  }
}

int main() {
  freopen("input.txt", "r", stdin);

  Graph graph;
  std::cin >> graph.vert_num >> graph.edge_num;

  graph.storage.resize(graph.vert_num);

  std::vector<ll> egde_flow(graph.edge_num);

  for (ll i = 0; i < graph.edge_num; ++i) {
    ll from;
    ll to;
    ll cap;
    std::cin >> from >> to >> cap;

    --from;
    --to;

    ll sz_from = static_cast<ll>(graph.storage[from].size());
    ll sz_to = static_cast<ll>(graph.storage[to].size());

    graph.storage[from].push_back({to, cap, 0, sz_to, i});
    graph.storage[to].push_back({from, 0, 0, sz_from, -1});
  }

  ll ans = FindMaxFlow(graph);
  FillAnsVec(egde_flow, graph);

  std::cout << ans << "\n";

  for (ll flow : egde_flow) {
    std::cout << flow << "\n";
  }
}