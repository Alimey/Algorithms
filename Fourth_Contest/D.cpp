#include <climits>
#include <iostream>
#include <vector>

struct SegTree {
  std::vector<std::pair<int, int>> tree;
  int n;

  SegTree(int n);
  void Add(int v, int lb, int rb, int pos, int val);
  int FindNotLess(int v, int lb, int rb, int l, int r, int val);
};

SegTree::SegTree(int n)
    : tree(std::vector<std::pair<int, int>>(4 * n, {INT_MIN, -1})), n(n) {}

void SegTree::Add(int v, int lb, int rb, int pos, int val) {
  if (lb == rb) {
    tree[v].first = val;
    tree[v].second = pos;
    return;
  }
  int mb = lb + (rb - lb) / 2;
  if (pos <= mb) {
    Add(2 * v + 1, lb, mb, pos, val);
  } else {
    Add(2 * v + 2, mb + 1, rb, pos, val);
  }
  tree[v] = std::max(tree[2 * v + 1], tree[2 * v + 2]);
}

int SegTree::FindNotLess(int v, int lb, int rb, int l, int r, int val) {
  // Если мы в пределах одного элемента
  if (lb == rb) {
    return tree[v].first >= val ? tree[v].second : -1;
  }

  // Если запрос совпадает с границами текущего отрезка
  if (l == lb && r == rb) {
    int mb = lb + (rb - lb) / 2;

    // Сначала проверяем левый сын
    if (tree[2 * v + 1].first >= val) {
      return FindNotLess(2 * v + 1, lb, mb, l, mb, val);
    }
    // Если не нашли в левом, проверяем правый сын
    if (tree[2 * v + 2].first >= val) {
      return FindNotLess(2 * v + 2, mb + 1, rb, mb + 1, r, val);
    }

    // Элемент не найден
    return -1;
  }

  // Разделяем запрос на две части
  int mb = lb + (rb - lb) / 2;

  // Если запрос полностью в левом подотрезке
  if (r <= mb) {
    return FindNotLess(2 * v + 1, lb, mb, l, r, val);
  }

  // Если запрос полностью в правом подотрезке
  if (l > mb) {
    return FindNotLess(2 * v + 2, mb + 1, rb, l, r, val);
  }

  // Если запрос пересекает оба подотрезка
  int left_result = FindNotLess(2 * v + 1, lb, mb, l, mb, val);
  if (left_result != -1) {
    return left_result;  // Если нашли в левом, возвращаем результат
  }

  return FindNotLess(2 * v + 2, mb + 1, rb, mb + 1, r,
                     val);  // Иначе ищем в правом
}

int main() {
  freopen("input.txt", "r", stdin);

  int n;
  int q;
  std::cin >> n >> q;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  SegTree tree(n);
  for (int i = 0; i < n; ++i) {
    tree.Add(0, 0, tree.n - 1, i, a[i]);
  }
  std::vector<int> answers;
  for (int i = 0; i < q; ++i) {
    int quiery;
    std::cin >> quiery;
    if (quiery == 0) {
      int pos;
      int val;
      std::cin >> pos >> val;
      tree.Add(0, 0, tree.n - 1, pos - 1, val);
    } else if (quiery == 1) {
      int pos;
      int val;
      std::cin >> pos >> val;
      answers.push_back(
          tree.FindNotLess(0, 0, tree.n - 1, pos - 1, tree.n - 1, val));
      if (answers.back() != -1) {
        ++answers.back();
      }
    }
  }
  for (size_t i = 0; i < answers.size(); ++i) {
    std::cout << answers[i] << "\n";
  }
}