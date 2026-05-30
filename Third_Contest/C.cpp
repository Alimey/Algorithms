#include <iostream>
#include <vector>

class MinHeap {
 private:
  std::vector<long long> heap_;
  long long size_ = 0;

  void SiftUp(long long index_of_vertice) {
    if (index_of_vertice == 0) {
      return;
    }
    long long parent = (index_of_vertice + 1) / 2 - 1;
    if (heap_[index_of_vertice] < heap_[parent]) {
      std::swap(heap_[index_of_vertice], heap_[parent]);
      SiftUp(parent);
    }
  }

  void SiftDown(long long index_of_vertice) {
    long long left_child_index = 2 * index_of_vertice + 1;
    long long right_child_index = 2 * index_of_vertice + 2;
    if (left_child_index >= size_) {
      return;
    }
    if (right_child_index >= size_ 
        && heap_[left_child_index] >= heap_[index_of_vertice]) {
      return;
    }
    if (right_child_index >= size_) {
      std::swap(heap_[index_of_vertice], heap_[left_child_index]);
      SiftDown(left_child_index);
      return;
    }
    long long min_child =
        (heap_[left_child_index] <= heap_[right_child_index]) 
        ? left_child_index : right_child_index;
    if (heap_[min_child] < heap_[index_of_vertice]) {
      std::swap(heap_[index_of_vertice], heap_[min_child]);
      SiftDown(min_child);
    }
  }

 public:
  void Insert(long long value) {
    heap_.push_back(value);
    SiftUp(size_);
    size_++;
  }

  long long GetMin() { return heap_[0]; }

  void ExtractMin() {
    std::swap(heap_[0], heap_[size_ - 1]);
    heap_.pop_back();
    size_--;
    SiftDown(0);
  }

  void Clear() {
    while (size_ > 0) {
      heap_.pop_back();
      size_--;
    }
  }

  long long Size() const { return size_; }
};

class MaxHeap {
 private:
  std::vector<long long> heap_;
  long long size_ = 0;

  void SiftUp(long long index_of_vertice) {
    if (index_of_vertice == 0) {
      return;
    }
    long long parent = (index_of_vertice + 1) / 2 - 1;
    if (heap_[index_of_vertice] > heap_[parent]) {
      std::swap(heap_[index_of_vertice], heap_[parent]);
      SiftUp(parent);
    }
  }

  void SiftDown(long long index_of_vertice) {
    long long left_child_index = 2 * index_of_vertice + 1;
    long long right_child_index = 2 * index_of_vertice + 2;
    if (left_child_index >= size_) {
      return;
    }
    if (right_child_index >= size_ 
        && heap_[left_child_index] <= heap_[index_of_vertice]) {
      return;
    }
    if (right_child_index >= size_) {
      std::swap(heap_[index_of_vertice], heap_[left_child_index]);
      SiftDown(left_child_index);
      return;
    }
    long long max_child =
        (heap_[left_child_index] >= heap_[right_child_index]) 
        ? left_child_index : right_child_index;
    if (heap_[max_child] > heap_[index_of_vertice]) {
      std::swap(heap_[index_of_vertice], heap_[max_child]);
      SiftDown(max_child);
    }
  }

 public:
  void Insert(long long value) {
    heap_.push_back(value);
    SiftUp(size_);
    size_++;
  }

  long long GetMax() { return heap_[0]; }

  void ExtractMax() {
    std::swap(heap_[0], heap_[size_ - 1]);
    heap_.pop_back();
    size_--;
    SiftDown(0);
  }

  void Clear() {
    while (size_ > 0) {
      heap_.pop_back();
      size_--;
    }
  }

  long long Size() const { return size_; }
};

class MinMaxHeap {
 private:
  MinHeap minh_;
  MaxHeap maxh_;
  MinHeap deleted_from_max_heap_;
  MaxHeap deleted_from_min_heap_;
  long long size_ = 0;

  void Recount() {
    while (deleted_from_min_heap_.Size() > 0 &&
           deleted_from_min_heap_.GetMax() == maxh_.GetMax()) {
      maxh_.ExtractMax();
      deleted_from_min_heap_.ExtractMax();
    }
    while (deleted_from_max_heap_.Size() > 0 &&
           deleted_from_max_heap_.GetMin() == minh_.GetMin()) {
      minh_.ExtractMin();
      deleted_from_max_heap_.ExtractMin();
    }
  }

 public:
  void Insert(long long value) {
    minh_.Insert(value);
    maxh_.Insert(value);
    size_++;
    std::cout << "ok\n";
  }

  void ExtractMin() {
    if (size_ == 0) {
      std::cout << "error\n";
      return;
    }
    std::cout << minh_.GetMin() << "\n";
    deleted_from_min_heap_.Insert(minh_.GetMin());
    minh_.ExtractMin();
    Recount();
    size_--;
  }

  void GetMin() {
    if (size_ == 0) {
      std::cout << "error\n";
      return;
    }
    std::cout << minh_.GetMin() << "\n";
  }

  void ExtractMax() {
    if (size_ == 0) {
      std::cout << "error\n";
      return;
    }
    std::cout << maxh_.GetMax() << "\n";
    deleted_from_max_heap_.Insert(maxh_.GetMax());
    maxh_.ExtractMax();
    Recount();
    size_--;
  }

  void GetMax() {
    if (size_ == 0) {
      std::cout << "error\n";
      return;
    }
    std::cout << maxh_.GetMax() << "\n";
  }

  void Size() const { std::cout << size_ << "\n"; }

  void Clear() {
    minh_.Clear();
    maxh_.Clear();
    deleted_from_max_heap_.Clear();
    deleted_from_min_heap_.Clear();
    size_ = 0;
    std::cout << "ok\n";
  }
};

int main() {
  freopen("input.txt", "r", stdin);

  long long query_number;
  std::cin >> query_number;
  std::string command;
  MinMaxHeap min_max_heap;
  for (long long i = 0; i < query_number; ++i) {
    std::cin >> command;
    if (command == "insert") {
      long long value;
      std::cin >> value;
      min_max_heap.Insert(value);
      continue;
    }
    if (command == "get_min") {
      min_max_heap.GetMin();
      continue;
    }
    if (command == "extract_min") {
      min_max_heap.ExtractMin();
      continue;
    }
    if (command == "get_max") {
      min_max_heap.GetMax();
      continue;
    }
    if (command == "extract_max") {
      min_max_heap.ExtractMax();
      continue;
    }
    if (command == "size") {
      min_max_heap.Size();
      continue;
    }
    if (command == "clear") {
      min_max_heap.Clear();
      continue;
    }
  }
}