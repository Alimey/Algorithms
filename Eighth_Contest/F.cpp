#include <algorithm>
#include <iostream>
#include <vector>

#define ll long long

const ll cInf = 1e14;

void AddPath(std::vector<ll>& output, ll start, ll end,
             const std::vector<std::vector<ll>>& next,
             const std::vector<std::vector<std::pair<ll, ll>>>& graph) {
  if (start == -1 || next[start][end] == -1) {
    return;
  }

  while (start != end) {
    ll next_vertex = next[start][end];
    output.push_back(graph[start][next_vertex].second);
    start = next_vertex;
  }
}

std::pair<bool, std::vector<ll>> Floyd(
    const std::vector<std::vector<std::pair<ll, ll>>>& graph,
    const std::vector<ll>& goals, ll vertice_numb) {
  // dp[u][v][k] - min price for path from u to v using first k vertice
  std::vector<std::vector<ll>> dp(vertice_numb,
                                  std::vector<ll>(vertice_numb, cInf));
  std::vector<std::vector<ll>> next(vertice_numb,
                                    std::vector<ll>(vertice_numb, -1));
  bool negative_cycle = false;

  for (ll i = 0; i < vertice_numb; ++i) {
    for (ll j = 0; j < vertice_numb; ++j) {
      dp[i][j] = graph[i][j].first;
      next[i][j] = dp[i][j] == cInf ? -1 : j;
    }
  }

  for (ll i = 0; i < vertice_numb; ++i) {
    dp[i][i] = 0;
    next[i][i] = i;
  }

  for (ll count = 0; count < vertice_numb; ++count) {
    for (ll v_vert = 0; v_vert < vertice_numb; ++v_vert) {
      for (ll u_vert = 0; u_vert < vertice_numb; ++u_vert) {
        if (dp[v_vert][count] == cInf || dp[count][u_vert] == cInf) {
          continue;
        }

        if (dp[v_vert][u_vert] > dp[v_vert][count] + dp[count][u_vert]) {
          dp[v_vert][u_vert] = dp[v_vert][count] + dp[count][u_vert];
          next[v_vert][u_vert] = next[v_vert][count];
        }
      }
    }
  }

  for (ll i = 0; i < vertice_numb; ++i) {
    if (dp[i][i] < 0 && next[goals[0]][i] != -1 && next[i][goals[0]] != -1) {
      negative_cycle = true;
    }
  }

  if (negative_cycle) {
    return {true, {}};
  }

  std::vector<ll> optimal_path;

  for (size_t i = 0; i < goals.size() - 1; ++i) {
    size_t start_ind = goals.size() - i - 1;
    size_t end_ind = goals.size() - i - 2;
    AddPath(optimal_path, goals[start_ind], goals[end_ind], next, graph);
  }

  return {false, optimal_path};
}

int main() {
  freopen("input.txt", "r", stdin);

  ll vertice_numb;
  ll edge_numb;
  ll goal_numb;
  std::cin >> vertice_numb >> edge_numb >> goal_numb;

  std::vector<std::vector<std::pair<ll, ll>>> graph(
      vertice_numb, std::vector<std::pair<ll, ll>>(vertice_numb, {cInf, cInf}));

  for (ll i = 0; i < edge_numb; ++i) {
    ll start_vertice;
    ll end_vertice;
    ll mood_influence;
    std::cin >> start_vertice >> end_vertice >> mood_influence;
    --start_vertice;
    --end_vertice;

    // inverting results
    graph[end_vertice][start_vertice] = {-mood_influence, i};
  }

  std::vector<ll> goals(goal_numb);
  for (ll i = 0; i < goal_numb; ++i) {
    std::cin >> goals[i];
    --goals[i];
  }

  auto [negative_cycle, ans] = Floyd(graph, goals, vertice_numb);

  if (negative_cycle) {
    std::cout << "infinitely kind";
  } else {
    std::cout << ans.size() << "\n";
    for (size_t i = 0; i < ans.size(); ++i) {
      std::cout << ans[ans.size() - i - 1] + 1 << " ";
    }
  }
}
