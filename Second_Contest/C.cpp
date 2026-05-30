#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

const int cTen = 10;
const int cNineteen = 19;

void CountSort(std::vector<uint64_t>& a, int n, int rank) {
  std::vector<int> digits(cTen);
  uint64_t divide = std::pow(cTen, rank);
  for (uint64_t x : a) {
    digits[(x / divide) % cTen]++;
  }
  for (int i = 1; i < cTen; i++) {
    digits[i] += digits[i - 1];
  }
  std::vector<uint64_t> sorted(n);
  for (int i = n - 1; i >= 0; i--) {
    int digit = (a[i] / divide) % cTen;
    int amount_of_less_or_equal = digits[digit];
    sorted[amount_of_less_or_equal - 1] = a[i];
    digits[digit]--;
  }
  a = sorted;
}

void LSD(std::vector<uint64_t>& a, int n) {
  for (int i = 0; i <= cNineteen; i++) {
    CountSort(a, n, i);
  }
}

int main() {
  std::ifstream fin;
  fin.open("input.txt");

  int n;
  fin >> n;
  std::vector<uint64_t> a(n);
  for (int i = 0; i < n; i++) {
    fin >> a[i];
  }
  LSD(a, n);
  for (uint64_t x : a) {
    std::cout << x << " ";
  }
}