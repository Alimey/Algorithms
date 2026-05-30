#include <algorithm>
#include <climits>
#include <iostream>
#include <set>
#include <vector>

#define ll long long
#define Graph std::vector<std::vector<std::pair<ll, ll>>>

ll vertices_number;
ll edge_number;
ll viruses_number;

const ll cInf = 1e13;

std::vector<ll> FillVirusesPath(const Graph& graph,
                                const std::vector<ll>& viruses) {
  std::vector<ll> distances(vertices_number, cInf);
  std::vector<ll> calculated(vertices_number);

  for (ll i = 0; i < viruses_number; ++i) {
    distances[viruses[i]] = 0;
  }

  auto cmp = [](const std::pair<ll, ll>& a, const std::pair<ll, ll>& b) {
    return (a.second < b.second) || (a.second == b.second && a.first < b.first);
  };

  // {vertice, min_dist_to_it}
  std::set<std::pair<ll, ll>, decltype(cmp)> ordering(cmp);

  for (ll i = 0; i < vertices_number; ++i) {
    ordering.insert({i, distances[i]});
  }

  while (!ordering.empty()) {
    auto [a, b] = *(ordering.begin());
    ll vertice = a;
    ll dist = b;
    ordering.erase(ordering.begin());

    calculated[vertice] = 1;

    for (auto [x, y] : graph[vertice]) {
      ll neighbour = x;
      ll weight = y;
      if (calculated[neighbour] != 0) {
        continue;
      }

      ll newdist = dist + weight;
      if (newdist < distances[neighbour]) {
        ordering.erase({neighbour, distances[neighbour]});
        distances[neighbour] = newdist;
        ordering.insert({neighbour, distances[neighbour]});
      }
    }
  }

  return distances;
}

std::vector<ll> FindPath(const Graph& graph, ll s,
                         const std::vector<ll>& viruses_track) {
  std::vector<ll> distances(vertices_number, cInf);
  std::vector<ll> calculated(vertices_number);

  distances[s] = 0;

  auto cmp = [](const std::pair<ll, ll>& a, const std::pair<ll, ll>& b) {
    return (a.second < b.second) || (a.second == b.second && a.first < b.first);
  };

  // {vertice, min_dist_to_it}
  std::set<std::pair<ll, ll>, decltype(cmp)> ordering(cmp);

  for (ll i = 0; i < vertices_number; ++i) {
    ordering.insert({i, distances[i]});
  }

  while (!ordering.empty()) {
    auto [a, b] = *(ordering.begin());
    ll vertice = a;
    ll dist = b;
    ordering.erase(ordering.begin());

    calculated[vertice] = 1;

    for (auto [x, y] : graph[vertice]) {
      ll neighbour = x;
      ll weight = y;
      if (calculated[neighbour] != 0) {
        continue;
      }

      ll newdist = dist + weight;
      if (newdist < distances[neighbour] &&
          newdist < viruses_track[neighbour]) {
        ordering.erase({neighbour, distances[neighbour]});
        distances[neighbour] = newdist;
        ordering.insert({neighbour, distances[neighbour]});
      }
    }
  }

  return distances;
}

int main() {
  freopen("input.txt", "r", stdin);
  std::ios_base::sync_with_stdio(false);

  std::cin >> vertices_number >> edge_number >> viruses_number;

  std::vector<ll> viruses(viruses_number);
  for (ll i = 0; i < viruses_number; ++i) {
    std::cin >> viruses[i];
    --viruses[i];
  }

  Graph graph(vertices_number);

  for (ll i = 0; i < edge_number; ++i) {
    ll first_vertice;
    ll second_vertice;
    ll weight;
    std::cin >> first_vertice >> second_vertice >> weight;
    --first_vertice;
    --second_vertice;

    graph[first_vertice].push_back({second_vertice, weight});
    graph[second_vertice].push_back({first_vertice, weight});
  }

  ll start;
  ll end;
  std::cin >> start >> end;
  --start;
  --end;

  std::vector<ll> times = FillVirusesPath(graph, viruses);
  std::vector<ll> ans = FindPath(graph, start, times);

  if (ans[end] == cInf) {
    std::cout << -1;
  } else {
    std::cout << ans[end];
  }
}