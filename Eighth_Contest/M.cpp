#include <algorithm>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

#define ll long long

struct DSU {
  std::vector<ll> parents;

  DSU(ll n) : parents(std::vector<ll>(n)) {
    for (ll i = 0; i < n; i++) {
      parents[i] = i;
    }
  }

  ll Leader(ll v) {
    if (parents[v] == v) {
      return v;
    }

    parents[v] = Leader(parents[v]);

    return parents[v];
  }

  void InsertEdge(ll v, ll u) {
    if (Leader(u) == Leader(v)) {
      return;
    }

    parents[Leader(u)] = v;
  }
};

struct Edge {
  ll u;
  ll v;
  ll w;

  bool operator<(const Edge& another) const { return w < another.w; }
};

int main() {
  freopen("input.txt", "r", stdin);

  ll n;
  ll m;
  std::cin >> n >> m;

  DSU dsu(n);

  std::vector<Edge> edges;

  for (ll i = 0; i < m; ++i) {
    ll u;
    ll v;
    ll cost;
    std::cin >> u >> v >> cost;
    --u;
    --v;
    edges.push_back({u, v, cost});
  }

  ll ans = 0;
  std::sort(edges.begin(), edges.end());

  for (ll i = 0; i < static_cast<ll>(edges.size()); ++i) {
    ll u = edges[i].u;
    ll v = edges[i].v;
    if (dsu.Leader(u) != dsu.Leader(v)) {
      ans += edges[i].w;
      dsu.InsertEdge(u, v);
    }
  }

  std::cout << ans;
}