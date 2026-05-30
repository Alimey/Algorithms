#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#define ll long long

int main() {
  freopen("input.txt", "r", stdin);

  ll n;
  std::cin >> n;

  std::vector<ll> vict(n);
  for (ll i = 0; i < n; ++i) {
    std::cin >> vict[i];
  }

  std::vector<ll> rest(n);
  for (ll i = 0; i < n; ++i) {
    std::cin >> rest[i];
  }

  std::vector<std::vector<ll>> group_games(n, std::vector<ll>(n));
  for (ll i = 0; i < n; ++i) {
    for (ll j = 0; j < n; ++j) {
      std::cin >> group_games[i][j];
    }
  }

  for (ll i = 0; i < n; ++i) {
    for (ll j = 0; j < n; ++j) {
      ll games = group_games[i][j];

      if (group_games[j][i] == -1) {
        group_games[i][j] = -1;
        continue;
      }

      rest[i] -= games;
      rest[j] -= games;

      if (i == 0 || j == 0) {
        vict[0] += games;
        group_games[i][j] = -1;
        continue;
      }

      ll delta = vict[i] - vict[j];

      if (delta > 0 && delta >= games) {
        vict[j] += games;
      }

      if (delta <= 0 && -delta >= games) {
        vict[i] += games;
      }

      if (delta > 0 && delta < games) {
        vict[j] += delta;
        games -= delta;
        vict[i] += games / 2 + games % 2;
        vict[j] += games / 2;
      }

      if (delta <= 0 && -delta < games) {
        vict[i] -= delta;
        games += delta;
        vict[i] += games / 2 + games % 2;
        vict[j] += games / 2;
      }

      group_games[i][j] = -1;
    }
  }

  vict[0] += rest[0];

  for (ll i = 1; i < n; ++i) {
    if (vict[i] > vict[0]) {
      std::cout << "NO";
      return 0;
    }
  }

  std::cout << "YES";
}