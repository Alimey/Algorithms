#include <fstream>
#include <iostream>
#include <queue>
#include <stack>

class MinQueue {
 private:
  std::queue<int> queue_;
  std::priority_queue<int, std::vector<int>, std::greater<int>> minimums_;
  std::priority_queue<int, std::vector<int>, std::greater<int>> to_delete_;

 public:
  void Enqueue(int value) {
    queue_.push(value);
    std::cout << "ok\n";
    minimums_.push(value);
  }

  void Check() {
    while (!to_delete_.empty() && to_delete_.top() == minimums_.top()) {
      to_delete_.pop();
      minimums_.pop();
    }
  }

  void Dequeue() {
    if (queue_.empty()) {
      std::cout << "error\n";
      return;
    }
    int value = queue_.front();
    std::cout << value << "\n";
    queue_.pop();
    to_delete_.push(value);
    Check();
  }

  void Front() {
    if (queue_.empty()) {
      std::cout << "error\n";
      return;
    }
    std::cout << queue_.front() << "\n";
  }

  void Size() { std::cout << queue_.size() << "\n"; }

  void Clear() {
    while (!queue_.empty()) {
      queue_.pop();
    }
    while (!minimums_.empty()) {
      minimums_.pop();
    }
    while (!to_delete_.empty()) {
      to_delete_.pop();
    }
    std::cout << "ok\n";
  }

  void Min() {
    if (queue_.empty()) {
      std::cout << "error\n";
      return;
    }
    std::cout << minimums_.top() << '\n';
  }
};

int main() {
  std::ifstream fin;
  fin.open("input.txt");

  MinQueue min_queue = MinQueue();

  int query_number;
  fin >> query_number;
  for (int i = 0; i < query_number; i++) {
    std::string command;
    fin >> command;
    if (command == "enqueue") {
      int value;
      fin >> value;
      min_queue.Enqueue(value);
    } else if (command == "dequeue") {
      min_queue.Dequeue();
    } else if (command == "front") {
      min_queue.Front();
    } else if (command == "size") {
      min_queue.Size();
    } else if (command == "clear") {
      min_queue.Clear();
    } else {
      min_queue.Min();
    }
  }
}