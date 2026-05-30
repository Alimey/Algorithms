#include <iostream>
#include <queue>
#include <vector>

void Check(std::priority_queue<std::vector<long long>>& window,
           std::priority_queue<std::vector<long long>>& to_delete) {
  while (!to_delete.empty() && to_delete.top() == window.top()) {
    window.pop();
    to_delete.pop();
  }
}

std::vector<std::vector<std::vector<long long>>> Count2D(
    std::vector<std::vector<long long>>& matrix, long long n, long long m,
    long long a, long long b) {
  std::vector<std::vector<std::vector<long long>>> ans;
  std::vector<std::vector<std::vector<long long>>> min_rows(
      n, std::vector<std::vector<long long>>(n - a + 1,
                                             std::vector<long long>(3)));
  std::priority_queue<std::vector<long long>> window;
  std::priority_queue<std::vector<long long>> to_delete;
  // Заполняем минимумы по строкам
  for (long long row = 0; row < n; ++row) {
    // Заполняем окно начальными значениями
    for (long long i = 0; i < b; ++i) {
      window.push(std::vector<long long>{matrix[row][i], row, i});
    }
    // Передвигаем окно, а результат записываем в min_rows
    for (long long col = 0; col < m - b + 1; ++col) {
      min_rows[row][col] = window.top();
      to_delete.push(std::vector<long long>{matrix[row][col], row, col});
      if (col == m - b) {
        continue;
      }
      window.push(std::vector<long long>{matrix[row][col + b], row, col + b});
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
  // Заполняем массив ответов массивами n - a
  for (long long i = 0; i < n - a + 1; ++i) {
    ans.push_back(std::vector<std::vector<long long>>(
        m - b + 1, std::vector<long long>(3)));
  }
  // Проходимся по min_rows новым окном
  for (long long col = 0; col < m - b + 1; ++col) {
    for (long long i = 0; i < a; ++i) {
      window.push(
          std::vector<long long>{min_rows[i][col][0], i, min_rows[i][col][2]});
    }
    for (long long row = 0; row < n - a + 1; ++row) {
      ans[row][col] = window.top();
      to_delete.push(std::vector<long long>{min_rows[row][col][0], row,
                                            min_rows[row][col][2]});
      if (row == n - a) {
        continue;
      }
      window.push(std::vector<long long>{min_rows[row + a][col][0], row + a,
                                         min_rows[row + a][col][2]});
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
  return ans;
}

std::vector<std::vector<std::vector<std::vector<long long>>>> Count3D(
    std::vector<std::vector<std::vector<long long>>>& space,
    std::vector<long long>& nmkabc) {
  long long n = nmkabc[0];
  long long m = nmkabc[1];
  long long k = nmkabc[2];
  long long a = nmkabc[3];
  long long b = nmkabc[4];
  long long c = nmkabc[5];
  std::vector<std::vector<std::vector<std::vector<long long>>>> narrow_space;
  for (long long i = 0; i < n; i++) {
    narrow_space.push_back(Count2D(space[i], m, k, b, c));
  }
  std::vector<std::vector<std::vector<std::vector<long long>>>> ans;
  // Заполняем массив ответов
  for (long long i = 0; i < n - a + 1; ++i) {
    ans.push_back(std::vector<std::vector<std::vector<long long>>>(
        m - b + 1, std::vector<std::vector<long long>>(
                       k - c + 1, std::vector<long long>(4))));
  }
  std::priority_queue<std::vector<long long>> window;
  std::priority_queue<std::vector<long long>> to_delete;
  // Теперь проходимся полосками длины a по длине, ширине и высоте
  for (long long width = 0; width < k - c + 1; width++) {
    for (long long high = 0; high < m - b + 1; high++) {
      // Заполняем окно начальными значениями
      for (long long i = 0; i < a; i++) {
        window.push(std::vector<long long>{narrow_space[i][high][width][0], i,
                                           narrow_space[i][high][width][1],
                                           narrow_space[i][high][width][2]});
      }
      // Проходимся по длине
      for (long long length = 0; length < n - a + 1; length++) {
        ans[length][high][width] = window.top();
        to_delete.push(
            std::vector<long long>{narrow_space[length][high][width][0], length,
                                   narrow_space[length][high][width][1],
                                   narrow_space[length][high][width][0]});
        if (length == n - a) {
          continue;
        }
        Check(window, to_delete);
        window.push(std::vector<long long>{
            narrow_space[length + a][high][width][0], length + a,
            narrow_space[length + a][high][width][1],
            narrow_space[length + a][high][width][2]});
      }
      // Опустошаем окно
      while (!window.empty()) {
        window.pop();
      }
      while (!to_delete.empty()) {
        to_delete.pop();
      }
    }
    // Опустошаем окно
    while (!window.empty()) {
      window.pop();
    }
    while (!to_delete.empty()) {
      to_delete.pop();
    }
  }
  return ans;
}

std::vector<std::vector<long long>> CountPosition(
    std::vector<std::vector<std::vector<long long>>>& space,
    std::vector<long long>& nmkabc, std::vector<std::vector<long long>>& xyz) {
  std::vector<std::vector<std::vector<std::vector<long long>>>> tracer =
      Count3D(space, nmkabc);
  std::vector<std::vector<long long>> ans;
  long long q = (long long)xyz.size();
  long long n = nmkabc[0];
  long long m = nmkabc[1];
  long long k = nmkabc[2];
  long long a = nmkabc[3];
  long long b = nmkabc[4];
  long long c = nmkabc[5];
  for (long long i = 0; i < q; i++) {
    long long x = xyz[i][0];
    long long y = xyz[i][1];
    long long z = xyz[i][2];
    while ((x < n - a + 1 && y < m - b + 1 && z < k - c + 1) &&
           (space[x][y][z] != tracer[x][y][z][0])) {
      std::vector<long long> new_xyz = tracer[x][y][z];
      x = new_xyz[1];
      y = new_xyz[2];
      z = new_xyz[3];
    }
    if (!(x < n - a + 1) || !(y < m - b + 1) || !(z < k - c + 1)) {
      long long nn = std::min(a, n - x);
      long long mm = std::min(b, m - y);
      long long kk = std::min(c, k - z);
      std::vector<std::vector<std::vector<long long>>> little_space(
          nn,
          std::vector<std::vector<long long>>(mm, std::vector<long long>(kk)));
      for (long long ii = x; ii < x + nn; ++ii) {
        for (long long jj = y; jj < y + mm; ++jj) {
          for (long long tt = z; tt < z + kk; ++tt) {
            little_space[ii - x][jj - y][tt - z] = space[ii][jj][tt];
          }
        }
      }
      std::vector<long long> nnmmkkaabbcc{nn, mm, kk, nn, mm, kk};
      std::vector<std::vector<std::vector<std::vector<long long>>>> point =
          Count3D(little_space, nnmmkkaabbcc);
      x += point[0][0][0][1];
      y += point[0][0][0][2];
      z += point[0][0][0][3];
    }
    ans.push_back(std::vector<long long>{x, y, z});
  }
  return ans;
}

int main() {
  freopen("C:/Users/Alimey/Desktop/programming/Algorithms_Problems/Third_Contest/input.txt", "r", stdin);
  const long long cSix = 6;

  std::vector<long long> nmkabc(cSix);
  for (long long i = 0; i < cSix; i++) {
    std::cin >> nmkabc[i];
  }
  std::vector<std::vector<std::vector<long long>>> space(
      nmkabc[0], std::vector<std::vector<long long>>(
                     nmkabc[1], std::vector<long long>(nmkabc[2])));
  for (long long i = 0; i < nmkabc[0]; i++) {
    for (long long j = 0; j < nmkabc[1]; j++) {
      for (long long t = 0; t < nmkabc[2]; t++) {
        std::cin >> space[i][j][t];
      }
    }
  }
  long long q;
  std::cin >> q;
  std::vector<std::vector<long long>> xyz;
  for (long long i = 0; i < q; i++) {
    long long x;
    long long y;
    long long z;
    std::cin >> x >> y >> z;
    xyz.push_back(std::vector<long long>{x, y, z});
  }
  std::vector<std::vector<long long>> ans = CountPosition(space, nmkabc, xyz);
  for (long long i = 0; i < q; i++) {
    std::cout << ans[i][0] << " " << ans[i][1] << " " << ans[i][2] << "\n";
  }
}