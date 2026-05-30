#include <algorithm>
#include <climits>
#include <iostream>
#include <unordered_map>
#include <vector>

enum class EventType { CPrefMinusSum, CAddPoint, CPrefPlusSum };

struct Event {
  int x;
  int y1;
  int y2;
  EventType type;
  int cell;

  bool operator<(const Event& other) const {
    if (x == other.x) {
      return type < other.type;
    }
    return x < other.x;
  }
};

struct SegmentTree {
  std::vector<int> tree;
  int n;

  SegmentTree(int n) : tree(std::vector<int>(4 * n)), n(n) {}

 private:
  void UpdatePrivate(int v, int lb, int rb, int pos) {
    if (lb == rb) {
      tree[v] = 1;
      return;
    }
    int mb = lb + (rb - lb) / 2;
    if (pos <= mb) {
      UpdatePrivate(2 * v, lb, mb, pos);
    } else {
      UpdatePrivate(2 * v + 1, mb + 1, rb, pos);
    }
    tree[v] = tree[2 * v] + tree[2 * v + 1];
  }

  int GetSumPrivate(int v, int lb, int rb, int l, int r) {
    if (l <= lb && rb <= r) {
      return tree[v];
    }
    int mb = lb + (rb - lb) / 2;
    int sum = 0;
    if (l <= mb) {
      sum += GetSumPrivate(2 * v, lb, mb, l, r);
    }
    if (r > mb) {
      sum += GetSumPrivate(2 * v + 1, mb + 1, rb, l, r);
    }
    return sum;
  }

 public:
  void Update(int pos) { UpdatePrivate(1, 1, n, pos); }

  int GetSum(int l, int r) { return GetSumPrivate(1, 1, n, l, r); }
};

int main() {
  freopen("input.txt", "r", stdin);
  std::ios_base::sync_with_stdio(false);

  int n;
  int q;
  std::cin >> n >> q;
  std::vector<int> a(n + 1);
  std::vector<Event> events;
  for (int i = 1; i < n + 1; ++i) {
    std::cin >> a[i];
    events.push_back({i, a[i], -1, EventType::CAddPoint, -1});
  }
  std::vector<int> ans(q + 1);
  for (int i = 1; i < q + 1; ++i) {
    int l;
    int r;
    int x;
    int y;
    std::cin >> l >> r >> x >> y;
    events.push_back({l, x, y, EventType::CPrefMinusSum, i});
    events.push_back({r, x, y, EventType::CPrefPlusSum, i});
  }
  std::sort(events.begin(), events.end());
  SegmentTree st(n);
  for (auto& event : events) {
    if (event.type == EventType::CAddPoint) {
      st.Update(event.y1);
    }
    if (event.type == EventType::CPrefMinusSum) {
      ans[event.cell] -= st.GetSum(event.y1, event.y2);
    }
    if (event.type == EventType::CPrefPlusSum) {
      ans[event.cell] += st.GetSum(event.y1, event.y2);
    }
  }
  for (int i = 1; i < q + 1; ++i) {
    std::cout << ans[i] << "\n";
  }
}