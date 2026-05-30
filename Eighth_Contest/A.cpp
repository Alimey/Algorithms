#include <climits>
#include <iostream>
#include <set>
#include <vector>

#define ll long long

struct Graph {
  ll n_size;
  ll m_size;

  std::vector<std::vector<std::pair<ll, ll>>> storage;
};


const ll cInf = 2009000999;

std::vector<ll> Dijkstra(
    ll start, const Graph& graph) {
  std::vector<ll> counted(graph.n_size, 0);
  std::vector<ll> distances(graph.n_size, cInf);

  auto cmp = [](const std::pair<ll, ll>& x, const std::pair<ll, ll>& y) {
    return (x.second < y.second) || (x.second == y.second && x.first < y.first);
  };

  std::set<std::pair<ll, ll>, decltype(cmp)> ordering(cmp);

  distances[start] = 0;
  ordering.insert({start, 0});

  for (ll i = 0; i < graph.n_size; ++i) {
    if (i != start) {
      ordering.insert({i, cInf});
    }
  }

  while (!ordering.empty()) {
    auto nearest = *ordering.begin();
    ordering.erase(ordering.begin());

    ll u_vert = nearest.first;
    ll d = nearest.second;

    if (counted[u_vert] != 0 || d > distances[u_vert]) {
      continue;
    }

    counted[u_vert] = 1;

    for (auto [v_vert, weight] : graph.storage[u_vert]) {
      if (counted[v_vert] == 0) {
        ll new_dist = distances[u_vert] + weight;
        if (new_dist < distances[v_vert]) {
          ordering.erase({v_vert, distances[v_vert]});
          distances[v_vert] = new_dist;
          ordering.insert({v_vert, distances[v_vert]});
        }
      }
    }
  }

  return distances;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  freopen("input.txt", "r", stdin);

  ll num_of_tests;
  std::cin >> num_of_tests;

  for (ll i = 0; i < num_of_tests; ++i) {
    Graph graph;
    std::cin >> graph.n_size >> graph.m_size;

    for (ll j = 0; j < graph.m_size; ++j) {
      ll u_vert;
      ll v_vert;
      ll cost;
      std::cin >> u_vert >> v_vert >> cost;
      graph.storage[u_vert].emplace_back(v_vert, cost);
      graph.storage[v_vert].emplace_back(u_vert, cost);
    }

    ll start;
    std::cin >> start;

    std::vector<ll> ans = Dijkstra(start, graph);

    for (ll dist : ans) {
      std::cout << dist << " ";
    }
    std::cout << "\n";
  }
}