#include <fstream>
#include <iostream>
#include <string>
#include <stack>

bool IsOneType(char open, char close) {
  return ((open == '{' && close == '}') || (open == '(' && close == ')') || (open == '[' && close == ']'));
}

bool IsCorrect(std::string parentheses) {
  std::stack<char> opened_parentheses;
  for (auto parenthesis : parentheses) {
    if (parenthesis == '{' || parenthesis == '[' || parenthesis == '(') {
      opened_parentheses.push(parenthesis);
    } else if (!opened_parentheses.empty() && IsOneType(opened_parentheses.top(), parenthesis)) {
      opened_parentheses.pop();
    } else {
      return false;
    }
  }
  return opened_parentheses.empty();
}

int main() {
  std::ifstream fin;
  fin.open("input.txt");

  std::string parentheses;
  fin >> parentheses;
  if (IsCorrect(parentheses)) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
}