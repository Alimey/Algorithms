#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <vector>

#define ll long long
const ll cInf = 1e14;

struct Edge {
  ll to;
  ll length;
  ll price;
};

struct Graph {
  ll n;
  std::vector<std::vector<Edge>> adj;

  Graph(ll n) : n(n) { adj.resize(n); }

  void AddEdge(ll u, ll v, ll length, ll price) {
    u--;
    v--;
    adj[u].push_back({v, length, price});
    adj[v].push_back({u, length, price});
  }
};

struct State {
  ll cost;
  ll time;
  ll vertex;
};

struct CompareState {
  bool operator()(const State& a, const State& b) const {
    return std::tie(a.cost, a.time, a.vertex) >
           std::tie(b.cost, b.time, b.vertex);
  }
};

int main() {
  freopen("input.txt", "r", stdin);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  ll n;
  ll m;
  ll limit;
  std::cin >> n >> m >> limit;
  Graph graph(n);
  for (ll i = 0; i < m; i++) {
    ll u;
    ll v;
    ll edge_price;
    ll edge_length;
    std::cin >> u >> v >> edge_price >> edge_length;
    graph.AddEdge(u, v, edge_length, edge_price);
  }

  std::vector<std::vector<ll>> dp(n, std::vector<ll>(limit + 1, cInf));
  std::vector<std::vector<std::pair<ll, ll>>> pred(
      n, std::vector<std::pair<ll, ll>>(limit + 1, {-1, -1}));

  dp[0][0] = 0;

  std::priority_queue<State, std::vector<State>, CompareState> pq;
  pq.push({0, 0, 0});

  while (!pq.empty()) {
    State cur = pq.top();
    pq.pop();

    if (cur.cost != dp[cur.vertex][cur.time]) {
      continue;
    }

    for (auto& edge : graph.adj[cur.vertex]) {
      ll new_time = cur.time + edge.length;
      if (new_time > limit) {
        continue;
      }
      ll new_cost = cur.cost + edge.price;
      if (new_cost < dp[edge.to][new_time]) {
        dp[edge.to][new_time] = new_cost;
        pred[edge.to][new_time] = {cur.vertex, cur.time};
        pq.push({new_cost, new_time, edge.to});
      }
    }
  }

  ll best_cost = cInf;
  ll best_time = -1;
  for (ll t = 0; t <= limit; t++) {
    if (dp[n - 1][t] < best_cost) {
      best_cost = dp[n - 1][t];
      best_time = t;
    }
  }

  if (best_cost == cInf) {
    std::cout << -1;
    return 0;
  }

  std::vector<ll> path;
  ll cur_vertex = n - 1;
  ll cur_time = best_time;
  while (cur_vertex != -1) {
    path.push_back(cur_vertex);
    auto [prev_vertex, prev_time] = pred[cur_vertex][cur_time];
    cur_vertex = prev_vertex;
    cur_time = prev_time;
  }

  std::cout << best_cost << "\n";
  std::cout << path.size() << "\n";
  for (size_t v = path.size() - 1; v > 0; --v) {
    std::cout << path[v] + 1 << " ";
  }
  std::cout << path.front() + 1;
}
