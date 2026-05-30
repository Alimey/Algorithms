#include <fstream>
#include <iostream>
#include <vector>

std::vector<std::pair<int, int>> Merge(std::vector<std::pair<int, int>>& a,
                                       std::vector<std::pair<int, int>>& b) {
  std::vector<std::pair<int, int>> c;
  int i = 0;
  int j = 0;
  int n = a.size();
  int m = b.size();

  while (i < n && j < m) {
    // Прописываем отдельно первый шаг
    if (c.empty() && a[i].first <= b[j].first) {
      c.push_back(a[i]);
      i++;
      continue;
    }
    if (c.empty()) {
      c.push_back(b[j]);
      j++;
      continue;
    }
    // Далее, если массив c уже не пуст
    // Если левый конец отрезка a[i] левее, чем левый конец b[j]
    if (a[i].first <= b[j].first) {
      // И если левый конец a[i] левее, чем правый конец последнего отрезка c
      if (a[i].first <= c.back().second) {
        if (a[i].second <= c.back().second) {
          i++;
          continue;
        }
        // Сливаем a[i] с последним отрезком c
        c.back().second = a[i].second;
      } else {
        // Иначе a[i] не пересекается с последним отрезком с
        c.push_back(a[i]);
      }
      i++;
    } else {
      // Иначе, отрезок b[j] левее, чем a[i]
      // Тогда сравниваем левый конец b[j] с правым концом c.back()
      if (b[j].first <= c.back().second) {
        if (b[j].second <= c.back().second) {
          j++;
          continue;
        }
        c.back().second = b[j].second;
      } else {
        c.push_back(b[j]);
      }
      j++;
    }
  }
  // Проверяем, запихнули ли мы все элементы из всех массивов
  while (i < n) {
    // Отдельно прописываем для первого из оставшихся
    if (a[i].first <= c.back().second && a[i].second <= c.back().second) {
      i++;
      continue;
    }
    if (a[i].first <= c.back().second) {
      c.back().second = a[i].second;
      i++;
      continue;
    }
    // Далее, просто докладываем остальные
    c.push_back(a[i]);
    i++;
  }

  while (j < m) {
    // Отдельно прописываем для первого из оставшихся
    if (b[j].first <= c.back().second && b[j].second <= c.back().second) {
      j++;
      continue;
    }
    if (b[j].first <= c.back().second) {
      c.back().second = b[j].second;
      j++;
      continue;
    }
    // Далее, просто докладываем остальные
    c.push_back(b[j]);
    j++;
  }

  return c;
}

std::vector<std::pair<int, int>> MergeSort(
    std::vector<std::pair<int, int>>& segments, int l, int r) {
  std::vector<std::pair<int, int>> merged;
  if (l >= r) {
    std::vector<std::pair<int, int>> s;
    s.push_back(segments[r]);
    return s;
  }
  int m = l + (r - l) / 2;
  std::vector<std::pair<int, int>> left_side = MergeSort(segments, l, m);
  std::vector<std::pair<int, int>> right_side = MergeSort(segments, m + 1, r);
  merged = Merge(left_side, right_side);
  return merged;
}

int main() {
  std::ifstream fin;
  fin.open("input.txt");

  int n;
  fin >> n;
  std::vector<std::pair<int, int>> segments;
  for (int i = 0; i < n; i++) {
    int x;
    int y;
    fin >> x >> y;
    std::pair<int, int> p = std::make_pair(x, y);
    segments.push_back(p);
  }

  std::vector<std::pair<int, int>> merged = MergeSort(segments, 0, n - 1);
  std::cout << merged.size() << "\n";
  for (size_t i = 0; i < merged.size(); i++) {
    std::cout << merged[i].first << " " << merged[i].second << "\n";
  }
}