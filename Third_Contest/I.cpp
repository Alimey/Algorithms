#include <deque>
#include <fstream>
#include <iostream>

// MeanQueue - класс, позволяющий добавлять элементы в середину очереди
class MeanQueue {
 private:
  std::deque<int> left_;
  std::deque<int> right_;

 public:
  void Push(int value) {
    left_.push_front(value);
    if (left_.size() == right_.size() + 1) {
      right_.push_front(left_.back());
      left_.pop_back();
    }
  }

  void PushCenter(int value) {
    if (left_.size() == right_.size()) {
      right_.push_front(value);
    } else {
      left_.push_back(value);
    }
  }

  void Pop() {
    std::cout << right_.back() << "\n";
    right_.pop_back();
    if (right_.size() == left_.size() - 1) {
      right_.push_front(left_.back());
      left_.pop_back();
    }
  }
};

int main() {
  std::ifstream fin;
  fin.open("input.txt");

  MeanQueue mean_queue = MeanQueue();

  int query_number;
  fin >> query_number;
  for (int i = 0; i < query_number; i++) {
    std::string command;
    fin >> command;
    if (command == "+") {
      int value;
      fin >> value;
      mean_queue.Push(value);
    } else if (command == "*") {
      int value;
      fin >> value;
      mean_queue.PushCenter(value);
    } else {
      mean_queue.Pop();
    }
  }
}