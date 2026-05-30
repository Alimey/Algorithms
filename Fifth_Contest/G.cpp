#include <cassert>
#include <iostream>
#include <memory>
#include <random>
#include <stack>

#define ll long long
#define shared_t std::shared_ptr<Node>
#define make_shared std::make_shared<Node>

const ll cDist = 1e6;
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dist(1, cDist);

struct Node {
  ll priority = dist(gen);
  ll len = 0;
  ll subsize = 1;
  ll sub_strange_sum = 0;
  shared_t left = nullptr;
  shared_t right = nullptr;

  Node() = default;

  Node(ll len) : len(len), sub_strange_sum(len * len) {}

  void FixSubSize() {
    ll left_size = (left == nullptr) ? 0 : left->subsize;
    ll right_size = (right == nullptr) ? 0 : right->subsize;
    subsize = left_size + right_size + 1;
  }

  void FixSubSum() {
    ll left_sum = (left == nullptr) ? 0 : left->sub_strange_sum;
    ll right_sum = (right == nullptr) ? 0 : right->sub_strange_sum;
    sub_strange_sum = left_sum + right_sum + len * len;
  }

  ll GetLocalIndex() { return (left == nullptr) ? 0 : left->subsize; }
};

shared_t Merge(shared_t root_a, shared_t root_b) {
  if (root_a == nullptr && root_b == nullptr) {
    return nullptr;
  }
  if (root_b == nullptr) {
    return root_a;
  }
  if (root_a == nullptr) {
    return root_b;
  }
  if (root_a->priority <= root_b->priority) {
    root_a->right = Merge(root_a->right, root_b);
    root_a->FixSubSize();
    root_a->FixSubSum();
    return root_a;
  }
  root_b->left = Merge(root_a, root_b->left);
  root_b->FixSubSize();
  root_b->FixSubSum();
  return root_b;
}

std::pair<shared_t, shared_t> Split(shared_t root, ll x, ll add = 0) {
  if (root == nullptr) {
    return {nullptr, nullptr};
  }
  if (x > root->GetLocalIndex() + add) {
    auto [left, right] = Split(root->right, x, add + root->GetLocalIndex() + 1);
    root->right = left;
    root->FixSubSize();
    root->FixSubSum();
    return {root, right};
  }
  auto [left, right] = Split(root->left, x, add);
  root->left = right;
  root->FixSubSize();
  root->FixSubSum();
  return {left, root};
}

shared_t Insert(shared_t root, ll pos, ll len) {
  auto [left, right] = Split(root, pos);
  shared_t node = make_shared(len);
  return Merge(Merge(left, node), right);
}

std::pair<shared_t, ll> Erase(shared_t root, ll pos) {
  auto [left, right] = Split(root, pos);
  auto [lleft, rright] = Split(right, 1);
  ll len_ans = lleft->len;
  right = rright;
  root = Merge(left, right);
  return {root, len_ans};
}

shared_t Update(shared_t root, ll pos, ll adding) {
  auto [new_root, deleted_len] = Erase(root, pos);
  root = new_root;
  root = Insert(root, pos, deleted_len + adding);
  return root;
}

shared_t DeleteAndDistribute(shared_t root, ll pos, ll& n) {
  auto [new_root, deleted_len] = Erase(root, pos);
  --n;
  root = new_root;
  if (pos - 1 >= 0 && pos < n) {
    root = Update(root, pos - 1, deleted_len / 2);
    root = Update(root, pos, deleted_len / 2 + deleted_len % 2);
    return root;
  }
  if (pos - 1 >= 0) {
    root = Update(root, pos - 1, deleted_len);
    return root;
  }
  root = Update(root, pos, deleted_len);
  return root;
}

shared_t Divide(shared_t root, ll pos, ll& n) {
  auto [new_root, deleted_len] = Erase(root, pos);
  --n;
  root = new_root;
  root = Insert(root, pos, deleted_len / 2 + deleted_len % 2);
  ++n;
  root = Insert(root, pos, deleted_len / 2);
  ++n;
  return root;
}

int main() {
  freopen("input.txt", "r", stdin);
  std::ios_base::sync_with_stdio(false);

  ll n;
  std::cin >> n;
  std::stack<shared_t> stack;
  shared_t treap = nullptr;
  for (ll i = 0; i < n; ++i) {
    ll len;
    std::cin >> len;
    treap = Insert(treap, i, len);
  }

  ll q;
  std::cin >> q;
  std::cout << treap->sub_strange_sum << "\n";
  for (ll i = 0; i < q; ++i) {
    ll command;
    ll pos;
    std::cin >> command >> pos;
    --pos;
    if (command == 1) {
      treap = DeleteAndDistribute(treap, pos, n);
    } else {
      treap = Divide(treap, pos, n);
    }
    std::cout << treap->sub_strange_sum << "\n";
  }
}
