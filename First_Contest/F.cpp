#include<iostream>
#include<vector>
#include<fstream>

int FidK(std::vector<int>& Ai, std::vector<int>& Bj, int l) {
  int right = l - 1;
  int left = 0;
  while (right > left + 1) {
    int median = left + (right - left) / 2;
    if (Ai[median] >= Bj[median]) {
      right = median;
    } else {
      left = median;
    }
  }
  int lk = std::max(Ai[left], Bj[left]);
  int rk = std::max(Ai[right], Bj[right]);
  return lk > rk ? right + 1 : left + 1;
}

int main() {
  std::ifstream fin;
  fin.open("input.txt");

  int n;
  int m;
  int l;
  fin >> n >> m >> l;
  std::vector<std::vector<int>> A(n, std::vector<int>(l));
  std::vector<std::vector<int>> B(m, std::vector<int>(l));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < l; j++) {
      fin >> A[i][j];
    }
  }
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < l; j++) {
      fin >> B[i][j];
    }
  }

  int q;
  fin >> q;
  std::vector<int> ans;
  for (int t = 0; t < q; t++) {
    int i;
    int j;
    fin >> i >> j;
    i--; 
    j--;
    ans.push_back(FidK(A[i], B[j], l));
  }

  for (int x : ans) {
    std::cout << x << "\n";
  }
}