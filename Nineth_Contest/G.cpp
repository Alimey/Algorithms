#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

#define ll long long

const ll cInf = 1e13;

struct Edge {
  ll end;
  ll cap;
  ll rev;
};

struct Graph {
  std::vector<std::vector<Edge>> storage;

  void AddEdge(ll start, ll end, ll cap) {
    ll save_start = storage[start].size();
    ll save_end = storage[end].size();

    storage[start].push_back(Edge{end, cap, save_end});
    storage[end].push_back(Edge{start, 0, save_start});
  }
};

std::vector<ll> level;
std::vector<ll> ptr;

bool BFS(ll start, ll end, const Graph& graph) {
  std::fill(level.begin(), level.end(), -1);
  std::queue<ll> queue;

  level[start] = 0;
  queue.push(start);

  while (!queue.empty()) {
    ll vert = queue.front();
    queue.pop();

    for (const Edge& edge: graph.storage[vert]) {
      if (edge.cap > 0 && level[edge.end] == -1) {
        level[edge.end] = level[vert] + 1;
        queue.push(edge.end);
      }
    }
  }

  return level[end] != -1;
}

ll DFS(ll start, ll end, ll flow, Graph& graph) {
  if (start == end) {
    return flow;
  }

  for (ll& i_ptr = ptr[start]; i_ptr < static_cast<ll>(graph.storage[start].size()); ++i_ptr) {
    Edge& edge = graph.storage[start][i_ptr];

    if (edge.cap > 0 && level[edge.end] == level[start] + 1) {
      ll pushed = DFS(edge.end, end, std::min(flow, edge.cap), graph);

      if (pushed > 0) {
        edge.cap -= pushed;
        graph.storage[edge.end][edge.rev].cap += pushed;
        return pushed;
      }
    }
  }
  
  return 0;
}



int main() {
  freopen("input.txt", "r", stdin);

  ll height;
  ll width;
  std::cin >> height >> width;

  ll blocked_numb;
  ll probable_numb;
  std::cin >> blocked_numb >> probable_numb;

  std::set<std::pair<ll, ll>> blocked;
  std::set<std::pair<ll, ll>> probable;

  for (ll i = 0; i < blocked_numb; ++i) {
    ll x;
    ll y;
    std::cin >> x >> y;
    blocked.insert({x, y});
  }

  for (ll i = 0; i < probable_numb; ++i) {
    ll x;
    ll y;
    std::cin >> x >> y;
    probable.insert({x, y});
  }

  ll x_start;
  ll y_start;
  ll x_end;
  ll y_end;
  std::cin >> x_start >> y_start >> x_end >> y_end;

  if (blocked.contains({x_start, y_start}) || blocked.contains({x_end, y_end})) {
    std::cout << 0;
    return 0;
  }

  std::vector<std::vector<bool>> grid()
}