#include <iostream>
#include <queue>
#include <vector>

std::vector<std::vector<long long>> ans;

void Check(std::priority_queue<long long, std::vector<long long>,
                               std::greater<long long>>& window,
           std::priority_queue<long long, std::vector<long long>,
                               std::greater<long long>>& to_delete) {
  while (!to_delete.empty() && to_delete.top() == window.top()) {
    window.pop();
    to_delete.pop();
  }
}

void CountMatrix(std::vector<std::vector<long long>>& matrix, long long n,
                 long long k) {
  std::vector<std::vector<long long>> min_rows(
      n, std::vector<long long>(n - k + 1));
  std::priority_queue<long long, std::vector<long long>,
                      std::greater<long long>>
      window;
  std::priority_queue<long long, std::vector<long long>,
                      std::greater<long long>>
      to_delete;
  // Заполняем минимумы по строкам
  for (long long row = 0; row < n; ++row) {
    // Заполняем окно начальными значениями
    for (long long i = 0; i < k; ++i) {
      window.push(matrix[row][i]);
    }
    // Передвигаем окно, а результат записываем в min_rows
    for (long long col = 0; col < n - k + 1; ++col) {
      min_rows[row][col] = window.top();
      to_delete.push(matrix[row][col]);
      if (col == n - k) {
        continue;
      }
      window.push(matrix[row][col + k]);
      Check(window, to_delete);
    }
    // Опустошаем окно
    while (!window.empty()) {
      window.pop();
    }
    while (!to_delete.empty()) {
      to_delete.pop();
    }
  }
  // Заполняем массив ответов массивами n - k
  for (long long i = 0; i < n - k + 1; ++i) {
    ans.push_back(std::vector<long long>(n - k + 1));
  }
  // Проходимся по min_rows новым окном
  for (long long col = 0; col < n - k + 1; ++col) {
    for (long long i = 0; i < k; ++i) {
      window.push(min_rows[i][col]);
    }
    for (long long row = 0; row < n - k + 1; ++row) {
      ans[row][col] = window.top();
      to_delete.push(min_rows[row][col]);
      if (row == n - k) {
        continue;
      }
      window.push(min_rows[row + k][col]);
      Check(window, to_delete);
    }
    // Опустошаем окно
    while (!window.empty()) {
      window.pop();
    }
    while (!to_delete.empty()) {
      to_delete.pop();
    }
  }
}

int main() {
  freopen("input.txt", "r", stdin);

  long long n;
  long long k;
  std::cin >> n >> k;
  std::vector<std::vector<long long>> matrix(n, std::vector<long long>(n));
  for (long long i = 0; i < n; ++i) {
    for (long long j = 0; j < n; ++j) {
      std::cin >> matrix[i][j];
    }
  }
  CountMatrix(matrix, n, k);
  for (long long i = 0; i < n - k + 1; ++i) {
    for (long long j = 0; j < n - k + 1; ++j) {
      std::cout << ans[i][j] << " ";
    }
    std::cout << "\n";
  }
}