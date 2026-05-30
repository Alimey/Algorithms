#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <memory>
#include <vector>

#define ll long long

struct Node {
  ll max_diff = 0;
  ll last_station = 0;
  ll push = -1;
  ll push_last = -1;
  ll max_push_diff = 0;
};

struct SegTree {
  std::vector<Node> tree;
  ll h;

  SegTree(ll h) : tree(std::vector<Node>(4 * h)), h(h) {}

  void Push(ll v) {
    if (2 * v + 1 >= 4 * h) {
      tree[v].push = -1;
      tree[v].push_last = -1;
      tree[v].max_push_diff = 0;
      return;
    }
    if (tree[2 * v + 1].push == -1) {
      tree[2 * v + 1].push = tree[v].push;
      tree[2 * v + 1].push_last = tree[v].push_last;
      tree[2 * v + 1].max_diff =
          std::max(tree[2 * v + 1].max_diff, tree[v].max_push_diff);
      tree[2 * v + 1].max_diff =
          std::max(tree[2 * v + 1].max_diff,
                   tree[v].push - tree[2 * v + 1].last_station);
      tree[2 * v + 1].last_station = std::max(tree[v].push, tree[v].push_last);
      tree[2 * v + 1].max_push_diff = tree[v].max_push_diff;
    } else {
      tree[2 * v + 1].max_diff =
          std::max(tree[2 * v + 1].max_diff,
                   tree[v].push - tree[2 * v + 1].last_station);
      tree[2 * v + 1].max_diff =
          std::max(tree[2 * v + 1].max_diff, tree[v].max_push_diff);
      tree[2 * v + 1].push_last = std::max(tree[v].push_last, tree[v].push);
      tree[2 * v + 1].max_push_diff =
          std::max(tree[2 * v + 1].max_push_diff, tree[v].max_push_diff);
      tree[2 * v + 1].max_push_diff =
          std::max(tree[2 * v + 1].max_push_diff,
                   tree[v].push - tree[2 * v + 1].last_station);
      tree[2 * v + 1].last_station = std::max(tree[v].push_last, tree[v].push);
    }
    if (2 * v + 2 >= 4 * h) {
      tree[v].push = -1;
      return;
    }
    if (tree[2 * v + 2].push == -1) {
      tree[2 * v + 2].push = tree[v].push;
      tree[2 * v + 2].push_last = tree[v].push_last;
      tree[2 * v + 2].max_diff =
          std::max(tree[2 * v + 2].max_diff, tree[v].max_push_diff);
      tree[2 * v + 2].max_diff =
          std::max(tree[2 * v + 2].max_diff,
                   tree[v].push - tree[2 * v + 2].last_station);
      tree[2 * v + 2].last_station = std::max(tree[v].push, tree[v].push_last);
      tree[2 * v + 2].max_push_diff = tree[v].max_push_diff;
    } else {
      tree[2 * v + 2].max_diff =
          std::max(tree[2 * v + 2].max_diff,
                   tree[v].push - tree[2 * v + 2].last_station);
      tree[2 * v + 2].max_diff =
          std::max(tree[2 * v + 2].max_diff, tree[v].max_push_diff);
      tree[2 * v + 2].push_last = std::max(tree[v].push_last, tree[v].push);
      tree[2 * v + 2].max_push_diff =
          std::max(tree[2 * v + 2].max_push_diff, tree[v].max_push_diff);
      tree[2 * v + 2].max_push_diff =
          std::max(tree[2 * v + 2].max_push_diff,
                   tree[v].push - tree[2 * v + 2].last_station);
      tree[2 * v + 2].last_station = std::max(tree[v].push_last, tree[v].push);
    }
    tree[v].push = -1;
    tree[v].push_last = -1;
    tree[v].max_push_diff = 0;
  }

  void Add(ll v, ll lb, ll rb, ll station, ll l, ll r) {
    if (lb == rb) {
      ll curr_diff = station - tree[v].last_station;
      tree[v].max_diff = std::max(tree[v].max_diff, curr_diff);
      tree[v].last_station = station;
      return;
    }
    if (tree[v].push != -1) {
      Push(v);
    }
    if (l == lb && r == rb) {
      ll curr_diff = station - tree[v].last_station;
      tree[v].max_diff = std::max(tree[v].max_diff, curr_diff);
      if (tree[v].push == -1) {
        tree[v].push = station;
        tree[v].last_station = station;
        return;
      }
      if (tree[v].push_last == -1) {
        tree[v].push_last = station;
        tree[v].max_push_diff = station - tree[v].push;
        tree[v].last_station = station;
        return;
      }
      tree[v].max_push_diff =
          std::max(tree[v].max_push_diff, station - tree[v].push_last);
      tree[v].push_last = station;
      tree[v].last_station = station;
      return;
    }
    ll mb = lb + (rb - lb) / 2;
    if (r <= mb) {
      Add(2 * v + 1, lb, mb, station, l, r);
    } else if (l > mb) {
      Add(2 * v + 2, mb + 1, rb, station, l, r);
    } else {
      Add(2 * v + 1, lb, mb, station, l, mb);
      Add(2 * v + 2, mb + 1, rb, station, mb + 1, r);
    }
    tree[v].max_diff =
        std::max(tree[2 * v + 1].max_diff, tree[2 * v + 2].max_diff);
    tree[v].last_station = station;
  }

  ll Find(ll v, ll lb, ll rb, ll index) {
    if (lb == rb) {
      tree[v].push = -1;
      return tree[v].max_diff;
    }
    if (tree[v].push != -1) {
      Push(v);
    }
    ll mb = lb + (rb - lb) / 2;
    if (index <= mb) {
      return Find(2 * v + 1, lb, mb, index);
    }
    return Find(2 * v + 2, mb + 1, rb, index);
  }

  void CoveringAdd(ll station, ll l, ll r) { Add(0, 0, h, station, l, r); }

  ll CoveringFind(ll index) { return Find(0, 0, h, index); }
};

struct Station {
  ll x;
  ll l;
  ll r;

  bool operator<(const Station& other) const { return x < other.x; }
};

int main() {
  freopen("input.txt", "r", stdin);
  std::ios_base::sync_with_stdio(false);

  ll n;
  ll h;
  ll w;
  std::cin >> n >> h >> w;
  SegTree stree(h);
  std::vector<Station> stations;
  for (ll i = 0; i < n; ++i) {
    Station station;
    std::cin >> station.x >> station.l >> station.r;
    stations.push_back(station);
  }
  std::sort(stations.begin(), stations.end());
  for (ll i = 0; i < n; ++i) {
    stree.CoveringAdd(stations[i].x, stations[i].l, stations[i].r);
  }
  stree.CoveringAdd(w, 0, h);
  for (ll i = 0; i < h + 1; ++i) {
    std::cout << stree.CoveringFind(i) << "\n";
  }
}