#include <iostream>
#include <vector>

class BinaryHeap {
 private:
  std::vector<std::pair<long long, long long>> h_;
  long long n_ = 0;

  void SiftUp(long long iv) {
    if (iv == 0) {
      return;
    }
    if (h_[iv].first < h_[(iv + 1) / 2 - 1].first) {
      indexes_of_added[h_[iv].second] = (iv + 1) / 2 - 1;
      indexes_of_added[h_[(iv + 1) / 2 - 1].second] = iv;
      std::swap(h_[iv], h_[(iv + 1) / 2 - 1]);
      SiftUp((iv + 1) / 2 - 1);
    }
  }

  void SiftDown(long long iv) {
    if (2 * iv + 1 >= n_) {
      return;
    }
    if (2 * iv + 2 >= n_ && h_[2 * iv + 1].first >= h_[iv].first) {
      return;
    }
    if (2 * iv + 2 >= n_) {
      indexes_of_added[h_[iv].second] = 2 * iv + 1;
      indexes_of_added[h_[2 * iv + 1].second] = iv;
      std::swap(h_[iv], h_[2 * iv + 1]);
      SiftDown(2 * iv + 1);
      return;
    }
    long long min_child = (h_[2 * iv + 1].first <= h_[2 * iv + 2].first)
                              ? 2 * iv + 1
                              : 2 * iv + 2;
    if (h_[min_child].first < h_[iv].first) {
      indexes_of_added[h_[iv].second] = min_child;
      indexes_of_added[h_[min_child].second] = iv;
      std::swap(h_[iv], h_[min_child]);
      SiftDown(min_child);
    }
  }

 public:
  std::vector<long long> indexes_of_added;
  void Insert(long long x, long long step) {
    h_.push_back({x, step});
    indexes_of_added[step] = n_;
    SiftUp(n_);
    n_++;
  }

  long long GetMin() { return h_[0].first; }

  void ExtractMin() {
    indexes_of_added[h_[n_ - 1].second] = 0;
    std::swap(h_[0], h_[n_ - 1]);
    h_.pop_back();
    n_--;
    SiftDown(0);
  }

  void DecreaseKey(long long step, long long delta) {
    h_[indexes_of_added[step]].first -= delta;
    SiftUp(indexes_of_added[step]);
  }
};

int main() {
  freopen("input.txt", "r", stdin);

  long long q;
  std::cin >> q;
  std::string command;
  BinaryHeap h;
  h.indexes_of_added.resize(q);
  for (long long i = 0; i < q; ++i) {
    std::cin >> command;
    if (command == "insert") {
      long long x;
      std::cin >> x;
      h.Insert(x, i);
      continue;
    }
    if (command == "getMin") {
      std::cout << h.GetMin() << "\n";
      continue;
    }
    if (command == "extractMin") {
      h.ExtractMin();
      continue;
    }
    if (command == "decreaseKey") {
      long long i;
      long long delta;
      std::cin >> i >> delta;
      h.DecreaseKey(i - 1, delta);
      continue;
    }
  }
}