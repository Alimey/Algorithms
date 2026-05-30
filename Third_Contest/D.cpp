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
    long long parent = (iv + 1) / 2 - 1;
    if (h_[iv].first < h_[parent].first) {
      indexes_of_added[h_[iv].second] = parent;
      indexes_of_added[h_[parent].second] = iv;
      std::swap(h_[iv], h_[parent]);
      SiftUp(parent);
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