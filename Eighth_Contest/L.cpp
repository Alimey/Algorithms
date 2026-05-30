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

struct Query {
  std::string command;
  ll u;
  ll v;
};

int main() {
  freopen("input.txt", "r", stdin);

  ll n;
  ll m;
  ll q;
  std::cin >> n >> m >> q;

  std::vector<std::vector<ll>> graph(n);
  for (ll i = 0; i < m; ++i) {
    ll u;
    ll v;
    std::cin >> u >> v;
    --u;
    --v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  std::vector<Query> queries;
  for (ll i = 0; i < q; ++i) {
    Query query;
    std::cin >> query.command >> query.u >> query.v;
    --query.u;
    --query.v;
    queries.push_back(query);
  }

  std::reverse(queries.begin(), queries.end());

  DSU dsu(n);
  std::vector<std::string> ans;

  for (ll i = 0; i < q; ++i) {
    if (queries[i].command == "cut") {
      dsu.InsertEdge(queries[i].u, queries[i].v);
      continue;
    }
    if (dsu.Leader(queries[i].u) == dsu.Leader(queries[i].v)) {
      ans.push_back("YES");
    } else {
      ans.push_back("NO");
    }
  }

  for (size_t i = 0; i < ans.size(); ++i) {
    std::cout << ans[ans.size() - i - 1] << "\n";
  }
}