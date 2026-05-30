#include <fstream>
#include <iostream>
#include <vector>

int FidK(std::vector<int>& ai, std::vector<int>& bj, int l) {
  int right = l - 1;
  int left = 0;
  while (right > left + 1) {
    int median = left + (right - left) / 2;
    if (ai[median] >= bj[median]) {
      right = median;
    } else {
      left = median;
    }
  }
  int lk = std::max(ai[left], bj[left]);
  int rk = std::max(ai[right], bj[right]);
  return lk > rk ? right + 1 : left + 1;
}

int main() {
  std::ifstream fin;
  fin.open("input.txt");

  int n;
  int m;
  int l;
  fin >> n >> m >> l;
  std::vector<std::vector<int>> a(n, std::vector<int>(l));
  std::vector<std::vector<int>> b(m, std::vector<int>(l));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < l; j++) {
      fin >> a[i][j];
    }
  }
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < l; j++) {
      fin >> b[i][j];
    }
  }

  int q;
  fin >> q;
  std::vector<int> ans;
  for (int t = 0; t < q; t++) {
    int i;
    int j;
    fin >> i >> j;
    ans.push_back(FidK(a[i - 1], b[j - 1], l));
  }

  for (int x : ans) {
    std::cout << x << "\n";
  }
}