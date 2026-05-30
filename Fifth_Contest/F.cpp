#include <iostream>
#include <memory>
#include <random>

#define ll long long
#define shared_t std::shared_ptr<Node>
#define make_shared std::make_shared<Node>

const int cDist = 1e7;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dist(1, cDist);

struct Node {
  ll key = 0;
  ll priority = 0;
  ll sum = 0;
  shared_t right = nullptr;
  shared_t left = nullptr;

  Node() = default;

  Node(ll key) : key(key), priority(dist(gen)), sum(key) {}

  void FixSum() {
    sum = key;
    if (left != nullptr) {
      sum += left->sum;
    }
    if (right != nullptr) {
      sum += right->sum;
    }
  }
};

shared_t Merge(shared_t root_a, shared_t root_b) {
  if (root_a == nullptr && root_b == nullptr) {
    return nullptr;
  }
  if (root_a == nullptr) {
    root_b->FixSum();
    return root_b;
  }
  if (root_b == nullptr) {
    root_a->FixSum();
    return root_a;
  }
  if (root_a->priority <= root_b->priority) {
    root_a->right = Merge(root_a->right, root_b);
    root_a->FixSum();
    return root_a;
  }
  root_b->left = Merge(root_a, root_b->left);
  root_b->FixSum();
  return root_b;
}

std::pair<shared_t, shared_t> Split(shared_t root, ll key) {
  if (root == nullptr) {
    return {nullptr, nullptr};
  }
  if (root->key <= key) {
    auto [left, right] = Split(root->right, key);
    root->right = left;
    root->FixSum();
    return {root, right};
  }
  auto [left, right] = Split(root->left, key);
  root->left = right;
  root->FixSum();
  return {left, root};
}

bool Find(shared_t root, ll x) {
  auto [left, right] = Split(root, x);
  auto [lleft, rright] = Split(left, x - 1);
  bool ans = rright != nullptr;
  left = Merge(lleft, rright);
  root = Merge(left, right);
  return ans;
}

shared_t Insert(shared_t root, ll x) {
  if (Find(root, x)) {
    return root;
  }
  shared_t node = make_shared(x);
  auto [left, right] = Split(root, node->key);
  return Merge(left, Merge(node, right));
}

ll GetSum(shared_t root, ll l, ll r) {
  auto [l_left, l_right] = Split(root, l - 1);
  auto [r_left, r_right] = Split(l_right, r);
  ll ans = (r_left == nullptr) ? 0 : r_left->sum;
  l_right = Merge(r_left, r_right);
  root = Merge(l_left, l_right);
  return ans;
}

int main() {
  freopen("input.txt", "r", stdin);
  std::ios_base::sync_with_stdio(false);

  shared_t treap = nullptr;
  ll q;
  std::cin >> q;
  ll last_answer = LONG_LONG_MIN;
  char last_command = '-';
  const ll cMod = 1e9;
  for (ll i = 0; i < q; ++i) {
    char command;
    std::cin >> command;
    if (command == '+' && last_command == '-') {
      ll x;
      std::cin >> x;
      treap = Insert(treap, x);
    }
    if (command == '+' && last_command != '-') {
      ll x;
      std::cin >> x;
      treap = Insert(treap, (x + last_answer) % cMod);
      last_command = '-';
    }
    if (command == '?') {
      ll l;
      ll r;
      std::cin >> l >> r;
      last_answer = GetSum(treap, l, r);
      std::cout << last_answer << "\n";
      last_command = '?';
    }
  }

  return 0;
}
