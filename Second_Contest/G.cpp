#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <queue>

std::deque<long long> ans;

long long Machine(std::deque<std::pair<long long, long long>>& a,
                  std::deque<std::pair<long long, long long>>& b, int n) {
  std::deque<std::deque<long long>> first_group;
  std::deque<std::deque<long long>> second_group;
  for (int i = 0; i < n; i++) {
    if (a[i].first <= b[i].first) {
      std::deque<long long> dq = {a[i].first, b[i].first, i};
      first_group.push_back(dq);
    } else {
      std::deque<long long> dq = {b[i].first, a[i].first, i};
      second_group.push_back(dq);
    }
  }
  std::sort(first_group.begin(), first_group.end());
  std::sort(second_group.begin(), second_group.end());
  // Заполняем ответ для станков
  while (!first_group.empty()) {
    ans.push_back(first_group.front()[2]);
    first_group.pop_front();
  }
  while (!second_group.empty()) {
    ans.push_back(second_group.back()[2]);
    second_group.pop_back();
  }
  // Считаем общее время работы
  std::deque<long long> sa(n);
  std::deque<long long> fa(n);
  std::deque<long long> sb(n);
  std::deque<long long> fb(n);
  sa[0] = 0;
  fa[0] = sa[0] + a[ans[0]].first;
  sb[0] = fa[0];
  fb[0] = sb[0] + b[ans[0]].first;
  for (int i = 1; i < n; i++) {
    sa[i] = fa[i - 1];
    fa[i] = sa[i] + a[ans[i]].first;
    sb[i] = std::max(fa[i], fb[i - 1]);
    fb[i] = sb[i] + b[ans[i]].first;
  }

  return fb[n - 1];
}

int main() {
  std::ifstream fin;
  fin.open("input.txt");

  int n;
  fin >> n;
  std::deque<std::pair<long long, long long>> a;
  std::deque<std::pair<long long, long long>> b;
  for (int i = 0; i < n; i++) {
    long long ai;
    fin >> ai;
    a.push_back({ai, i});
  }
  for (int i = 0; i < n; i++) {
    long long bi;
    fin >> bi;
    b.push_back({bi, i});
  }

  long long timing = Machine(a, b, n);

  std::cout << timing << "\n";
  for (int i = 0; i < n; i++) {
    std::cout << ans[i] + 1 << " ";
  }
  std::cout << "\n";
  for (int i = 0; i < n; i++) {
    std::cout << ans[i] + 1 << " ";
  }
}