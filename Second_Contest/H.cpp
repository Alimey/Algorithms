#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <vector>

std::deque<std::deque<int>> ans;

int CountingSheeps(std::deque<std::pair<int, int>>& sheeps, std::deque<std::pair<int, int>>& dogs) {
  std::sort(sheeps.begin(), sheeps.end());
  std::sort(dogs.begin(), dogs.end());
  size_t fd = 0;
  size_t sd = dogs.size() / 2;
  int k = 0;
  for (size_t i = 0; i < sheeps.size() && sd < dogs.size(); i++) {
    if (sheeps[i].first <= dogs[fd].first) {
      continue;
    }
    while (sd < dogs.size() && sheeps[i].first >= dogs[sd].first) {
      sd++;
    }
    if (sd == dogs.size()) {
      break;
    }
    std::deque<int> dsd{sheeps[i].second, dogs[fd].second, dogs[sd].second};
    ans.push_back(dsd);
    fd++;
    sd++;
    k++;
  }
  return k;
}

int main() {
  std::ifstream fin;
  fin.open("input.txt");

  int n;
  int m;
  fin >> n >> m;
  std::deque<std::pair<int, int>> sheeps(n);
  std::deque<std::pair<int, int>> dogs(m);
  for (int i = 0; i < n; i++) {
    fin >> sheeps[i].first;
    sheeps[i].second = i;
  }
  for (int i = 0; i < m; i++) {
    fin >> dogs[i].first;
    dogs[i].second = i;
  }

  int k = CountingSheeps(sheeps, dogs);
  std::cout << k << "\n";
  for (int i = 0; i < k; i++) {
    std::cout << ans[i][0] + 1 << " " << ans[i][1] + 1 << " " << ans[i][2] + 1 << "\n";
  }
}