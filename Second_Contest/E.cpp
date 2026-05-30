#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <vector>

std::vector<long long> triplet{INT_MAX, INT_MAX, INT_MAX};

bool Triplet(std::vector<std::pair<long long, long long>>& a,
             std::vector<std::pair<long long, long long>>& b,
             std::vector<std::pair<long long, long long>>& c, long long s) {
  std::sort(b.begin(), b.end());
  for (size_t i = 0; i < c.size(); i++) {
    c[i].first = s - c[i].first;
  }
  std::sort(c.begin(), c.end());
  for (size_t i = 0; i < a.size(); i++) {
    size_t j = 0;
    size_t k = 0;
    bool is_updated = false;
    while (j < b.size() && k < c.size()) {
      if (a[i].first + b[j].first < c[k].first) {
        j++;
        continue;
      }
      if (a[i].first + b[j].first > c[k].first) {
        k++;
        continue;
      }
      std::vector<long long> new_triplet{a[i].second, b[j].second, c[k].second};
      if (new_triplet < triplet) {
        triplet = new_triplet;
        is_updated = true;
      }
      j++;
    }
    if (is_updated) {
      break;
    }
  }
  return triplet[0] < INT_MAX;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);

  size_t s;
  std::cin >> s;

  size_t n;
  std::cin >> n;
  std::vector<std::pair<long long, long long>> a;
  for (size_t i = 0; i < n; i++) {
    long long x;
    std::cin >> x;
    std::pair<long long, long long> ai{x, i};
    a.push_back(ai);
  }
  size_t m;
  std::cin >> m;
  std::vector<std::pair<long long, long long>> b;
  for (size_t i = 0; i < m; i++) {
    long long x;
    std::cin >> x;
    std::pair<long long, long long> bi{x, i};
    b.push_back(bi);
  }
  size_t l;
  std::cin >> l;
  std::vector<std::pair<long long, long long>> c;
  for (size_t i = 0; i < l; i++) {
    long long x;
    std::cin >> x;
    std::pair<long long, long long> ci{x, i};
    c.push_back(ci);
  }

  if (Triplet(a, b, c, s)) {
    std::cout << triplet[0] << " " << triplet[1] << " " << triplet[2];
  } else {
    std::cout << -1;
  }
}