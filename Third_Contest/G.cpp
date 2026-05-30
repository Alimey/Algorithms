#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Kid {
  int number;
  std::string name;
  Kid* left;
  Kid* right;
};

class Circle {
 private:
  std::vector<Kid*> circle_;
  int n_ = 0;

 public:
  void Push(std::string& name) {
    Kid* kid = new Kid{n_, name, nullptr, nullptr};
    n_++;
    if (n_ >= 2) {
      kid->left = circle_.front();
      kid->right = circle_.back();
      circle_.front()->right = kid;
      circle_.back()->left = kid;
    }
    circle_.push_back(kid);
  }
  void Pop(int to_delete) {
    Kid* kid = circle_[to_delete - 1];
    Kid* left_neighbour = kid->left;
    Kid* right_neighbour = kid->right;
    std::cout << right_neighbour->name << " ";
    std::cout << left_neighbour->name << "\n";
    kid->right = nullptr;
    kid->left = nullptr;
    left_neighbour->right = right_neighbour;
    right_neighbour->left = left_neighbour;
  }
  void Clear(int i) {
    delete circle_[i];
  }
};

int main() {
  std::ifstream fin;
  fin.open("input.txt");

  int n;
  fin >> n;
  Circle roundely;
  for (int i = 0; i < n; i++) {
    std::string name;
    fin >> name;
    roundely.Push(name);
  }
  std::vector<int> order(n - 3);
  for (int i = 0; i < n - 3; i++) {
    fin >> order[i];
  }
  for (int i = 0; i < n - 3; i++) {
    roundely.Pop(order[i]);
  }
  for (int i = 0; i < n; i++) {
    roundely.Clear(i);
  }
}