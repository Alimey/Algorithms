#include <fstream>
#include <iostream>
#include <vector>

long long inversions = 0;

void Merge(std::vector<int>& a, int first, int second, int end) {
  if (first == second) {
    return;
  }
  int i = first;
  int j = second;
  int k = 0;
  std::vector<int> merged(end - first + 1);
  while(i < second || j <= end) {
    if (j > end || i < second && a[i] <= a[j]) {
      merged[k] = a[i];
      i++;
    } else {
      merged[k] = a[j];
      j++;
      inversions += second - i;
    }
      k++;
  }
  for (int t = first, i = 0; t <= end; t++, i++) {
    a[t] = merged[i];
  }
}

void MergeSort(std::vector<int>& a, int start, int end) {
  if (start >= end) {
    return;
  }
  int mid = start + (end - start) / 2;
  MergeSort(a, start, mid);
  MergeSort(a, mid + 1, end);
  Merge(a, start, mid + 1, end);
}

int main() {
  std::ifstream fin;
  fin.open("input.txt");

  int n;
  fin >> n;
  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    fin >> a[i];
  }
  MergeSort(a, 0, n - 1);
  for (int x : a) {
    std::cout << x << " ";
  }
  std::cout << "\n";
  std::cout << inversions;
}