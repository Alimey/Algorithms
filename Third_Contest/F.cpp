#include <fstream>
#include <iostream>
#include <string>
#include <stack>

int Count(std::string polyak) {
  std::stack<int> numbers;
  for (char x : polyak) {
    if (x >= '0' && x <= '9') {
      numbers.push(x - '0');
    } else if (x == '+') {
      int a = numbers.top();
      numbers.pop();
      int b = numbers.top();
      numbers.pop();
      numbers.push(a + b);
    } else if (x == '*') {
      int a = numbers.top();
      numbers.pop();
      int b = numbers.top();
      numbers.pop();
      numbers.push(a * b);
    } else if (x == '-') {
      int a = numbers.top();
      numbers.pop();
      int b = numbers.top();
      numbers.pop();
      numbers.push(b - a);
    }
  }
  return numbers.top();
}

int main() {
  std::ifstream fin;
  fin.open("input.txt");

  std::string polyak;
  std::getline(fin, polyak);
  std::cout << Count(polyak);
}