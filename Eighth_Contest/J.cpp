#include <climits>
#include <iostream>
#include <set>
#include <vector>

#define ll long long

ll n;
ll u;
ll d;
ll i;
ll o;
ll k;

const ll cInf = 1e14;
constexpr ll cFloors = 1e6;

ll Dijkstra(const std::vector<std::vector<std::pair<ll, ll>>>& graph) {
  std::vector<ll> counted(cFloors + k, 0);
  std::vector<ll> distances(cFloors + k, cInf);

  auto cmp = [](const std::pair<ll, ll>& x, const std::pair<ll, ll>& y) {
    return (x.second < y.second) || (x.second == y.second && x.first < y.first);
  };

  std::set<std::pair<ll, ll>, decltype(cmp)> ordering(cmp);

  distances[0] = 0;
  ordering.insert({0, 0});

  for (ll i = 0; i < n + k; ++i) {
    if (i != 0) {
      ordering.insert({i, cInf});
    }
  }

  while (!ordering.empty()) {
    auto nearest = *ordering.begin();
    ordering.erase(ordering.begin());

    ll u = nearest.first;
    ll d = nearest.second;

    if (counted[u] != 0 || d > distances[u]) {
      continue;
    }

    counted[u] = 1;

    for (auto [v, weight] : graph[u]) {
      if (counted[v] == 0 && !ordering.empty()) {
        ll new_dist = distances[u] + weight;
        if (new_dist < distances[v]) {
          ordering.erase({v, distances[v]});
          distances[v] = new_dist;
          ordering.insert({v, distances[v]});
        }
      }
    }
  }

  return distances[n - 1];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  freopen("input.txt", "r", stdin);

  std::cin >> n >> u >> d >> i >> o >> k;

  std::vector<std::vector<std::pair<ll, ll>>> graph(cFloors + k);

  for (ll e = 0; e < k; ++e) {
    ll t;
    std::cin >> t;
    for (ll q = 0; q < t; ++q) {
      ll x;
      std::cin >> x;
      --x;
      graph[x].push_back({cFloors + e, i});
      graph[cFloors + e].push_back({x, o});
    }
  }

  for (ll e = 0; e < cFloors - 1; ++e) {
    graph[e].push_back({e + 1, u});
    graph[e + 1].push_back({e, d});
  }

  std::cout << Dijkstra(graph);
}