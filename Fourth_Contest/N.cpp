#include <algorithm>
#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

struct EmaeKakNenavisuCodstyle {
  int64_t m;
  int64_t n;
  int64_t x1;
  int64_t px;
  int64_t qx;
  int64_t y1;
  int64_t py;
  int64_t qy;
  int64_t k1;
  int64_t pk;
  int64_t qk;
};

std::vector<int64_t> GenerateArray(int64_t n, int64_t a1, int64_t p,
                                   int64_t q) {
  const int64_t cMod = 1e9;
  std::vector<int64_t> a(n);
  a[0] = a1;
  for (int64_t i = 1; i < n; ++i) {
    a[i] = (a[i - 1] * p + q) % cMod;
  }
  return a;
}

struct Query {
  int64_t l, r, k;
};

std::vector<Query> GenerateQueries(EmaeKakNenavisuCodstyle params) {
  if (params.m == 0) {
    return std::vector<Query>();
  }
  int64_t m = params.m;
  int64_t n = params.n;
  int64_t x1 = params.x1;
  int64_t px = params.px;
  int64_t qx = params.qx;
  int64_t y1 = params.y1;
  int64_t py = params.py;
  int64_t qy = params.qy;
  int64_t k1 = params.k1;
  int64_t pk = params.pk;
  int64_t qk = params.qk;
  std::vector<Query> queries(m);
  queries[0] = {std::min(x1, y1), std::max(x1, y1), k1};
  for (int64_t i = 1; i < m; ++i) {
    int64_t li = queries[i - 1].l;
    int64_t ri = queries[i - 1].r;
    int64_t ki = queries[i - 1].k;
    int64_t xi = 1 + ((li - 1) * px + qx) % n;
    int64_t yi = 1 + ((ri - 1) * py + qy) % n;
    int64_t new_li = std::min(xi, yi);
    int64_t new_ri = std::max(xi, yi);
    int64_t range_length = new_ri - new_li + 1;
    int64_t new_ki = 1 + ((ki - 1) * pk + qk) % range_length;
    queries[i] = {new_li, new_ri, new_ki};
  }
  return queries;
}

struct Node {
  Node* left = nullptr;
  Node* right = nullptr;
  int64_t count = 0;

  Node() = default;

  Node(int64_t count) : count(count) {}

  Node(Node* left, Node* right) : left(left), right(right) {
    count = 0;
    if (left != nullptr) {
      count += left->count;
    }
    if (right != nullptr) {
      count += right->count;
    }
  }
};

const int64_t cSize = 10e6;
Node data[cSize];
int64_t it = 0;

Node* Update(Node* v, int64_t lb, int64_t rb, int64_t pos) {
  if (lb == rb) {
    data[it++] = Node(v->count + 1);
    return data + it - 1;
  }
  int64_t mb = (lb + rb) / 2;
  if (pos <= mb) {
    if (v->left == nullptr) {
      data[it++] = Node();
      v->left = data + it - 1;
    }
    data[it++] = Node(Update(v->left, lb, mb, pos), v->right);
    return data + it - 1;
  }
  if (v->right == nullptr) {
    data[it++] = Node();
    v->right = data + it - 1;
  }
  data[it++] = Node(v->left, Update(v->right, mb + 1, rb, pos));
  return data + it - 1;
}

int64_t FindKth(Node* vl, Node* vr, int64_t lb, int64_t rb, int64_t k) {
  if (lb == rb) {
    return lb;
  }
  int64_t mb = (lb + rb) / 2;
  int64_t left_count = 0;
  if (vr != nullptr && vr->left != nullptr) {
    left_count += vr->left->count;
  }
  if (vl != nullptr && vl->left != nullptr) {
    left_count -= vl->left->count;
  }
  if (left_count >= k && vl != nullptr && vr != nullptr) {
    return FindKth(vl->left, vr->left, lb, mb, k);
  }
  if (left_count >= k && vr != nullptr) {
    return FindKth(nullptr, vr->left, lb, mb, k);
  }
  if (left_count >= k && vl != nullptr) {
    return FindKth(vl->left, nullptr, lb, mb, k);
  }
  if (vl != nullptr && vr != nullptr) {
    return FindKth(vl->right, vr->right, mb + 1, rb, k - left_count);
  }
  if (vr != nullptr) {
    return FindKth(nullptr, vr->right, mb + 1, rb, k - left_count);
  }
  if (vl != nullptr) {
    return FindKth(vl->right, nullptr, mb + 1, rb, k - left_count);
  }
  return FindKth(nullptr, nullptr, mb + 1, rb, k - left_count);
}

int main() {
  freopen("input.txt", "r", stdin);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int64_t n;
  std::cin >> n;
  int64_t a1;
  int64_t p;
  int64_t q;
  std::cin >> a1 >> p >> q;
  std::vector<int64_t> a = GenerateArray(n, a1, p, q);
  std::vector<int64_t> sorted_a = a;
  std::sort(sorted_a.begin(), sorted_a.end());
  sorted_a.erase(std::unique(sorted_a.begin(), sorted_a.end()), sorted_a.end());
  for (auto& x : a) {
    x = std::lower_bound(sorted_a.begin(), sorted_a.end(), x) -
        sorted_a.begin();
  }
  /////////////////////////
  std::vector<Node> roots;
  roots.reserve(a.size());
  roots.push_back(Node());
  for (size_t i = 0; i < a.size(); i++) {
    roots.push_back(*Update(&roots.back(), 0, sorted_a.size() - 1, a[i]));
  }
  /////////////////////////
  int64_t b;
  std::cin >> b;
  int64_t ans = 0;
  for (int64_t i = 0; i < b; ++i) {
    int64_t m;
    int64_t x1;
    int64_t px;
    int64_t qx;
    int64_t y1;
    int64_t py;
    int64_t qy;
    int64_t k1;
    int64_t pk;
    int64_t qk;
    std::cin >> m;
    std::cin >> x1 >> px >> qx;
    std::cin >> y1 >> py >> qy;
    std::cin >> k1 >> pk >> qk;
    std::vector<Query> queries =
        GenerateQueries({m, n, x1, px, qx, y1, py, qy, k1, pk, qk});
    for (int64_t i = 0; i < m; ++i) {
      int64_t addition = FindKth(&roots[queries[i].l - 1], &roots[queries[i].r],
                                 0, sorted_a.size() - 1, queries[i].k);
      ans += sorted_a[addition];
    }
  }
  std::cout << ans;
}