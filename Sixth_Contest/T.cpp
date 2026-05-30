#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
struct BigInteger {
  std::vector<int> digits;

  BigInteger(const std::string& num) {
    for (int i = num.size() - 1; i >= 0; --i) {
      digits.push_back(num[i] - '0');
    }
  }

  void divideByTwo() {
    int carry = 0;
    for (int i = digits.size() - 1; i >= 0; --i) {
      int current = digits[i] + carry * 10;
      digits[i] = current / 2;
      carry = current % 2;
    }
    
    while (digits.size() > 1 && digits.back() == 0) {
      digits.pop_back();
    }
  }

  bool operator==(const BigInteger& other) const {
    return digits == other.digits;
  }

  bool operator==(int x) const {
    return *this == BigInteger(std::to_string(x));
  }

  BigInteger& operator--() {
    int borrow = 1;
    for (int i = 0; i < digits.size(); ++i) {
      if (digits[i] >= borrow) {
        digits[i] -= borrow;
        borrow = 0;
        break;
      } else {
        digits[i] = 9;
      }
    }
    
    while (digits.size() > 1 && digits.back() == 0) {
      digits.pop_back();
    }

    return *this;
  }
};

std::vector<std::vector<int>> multiply(const std::vector<std::vector<int>>& a, const std::vector<std::vector<int>>& b) {
  int n = a.size();
  std::vector<std::vector<int>> result(n, std::vector<int>(n, 0));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < n; ++k) {
        result[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  return result;
}

std::vector<std::vector<int>> identityMatrix(int n) {
  std::vector<std::vector<int>> result(n, std::vector<int>(n, 0));
  for (int i = 0; i < n; ++i) {
    result[i][i] = 1;
  }
  return result;
}

std::vector<std::vector<int>> matrixPower(std::vector<std::vector<int>> base, BigInteger exp) {
  int n = base.size();
  std::vector<std::vector<int>> result = identityMatrix(n);

  while (!(exp == 0)) {
    if (exp.digits[0] % 2 == 1) {
      result = multiply(result, base);
    }
    base = multiply(base, base);
    exp.divideByTwo();
  }

  return result;
}

int main() {
  freopen("input.txt", "r", stdin);
  std::ios_base::sync_with_stdio(false);

  int m;
  int z;
  std::string str;
  const int cMod = (1 << m) - 1;
  std::cin >> str >> m >> z;

  BigInteger n(str);

  std::vector<std::vector<int>> match((1 << m), std::vector<int>(1 << m));

  for (int i = 0; i < (1 << m); ++i) {
    for (int j = 0; j < (1 << m); ++j) {
      bool good = true;
      for (int k = 1; k < (1 << (m - 1)); k <<= 1) {
        int check1 = k;
        int check2 = (k << 1);
        if ((check1 & i) == 0 && (check1 & j) == 0 && (check2 & i) == 0 && (check2 & j) == 0) {
          good = false;
          break;
        }
        if ((check1 & i) != 0 && (check1 & j) != 0 && (check2 & i) != 0 && (check2 & j) != 0) {
          good = false;
          break;
        }
      }
      match[i][j] = good ? 1 : 0;
    }
  }

  std::cout << "Исходная match\n";
  for (int i = 0; i < match.size(); ++i) {
    for (int j = 0; j < match[0].size(); ++j) {
      std::cout << match[i][j] << " ";
    }
    std::cout << "\n";
  }

  auto ans = matrixPower(match, n);

  std::cout << "Степень\n";
  for (int i = 0; i < ans.size(); ++i) {
    for (int j = 0; j < ans[0].size(); ++j) {
      std::cout << ans[i][j] << " ";
    }
    std::cout << "\n";
  }

  int d = 0;
  for (int i = 0; i < (1 << m); ++i) {
    for (int j = 0; j < (1 << m); ++j) {
      d = (d + ans[i][j]) % z;
    }
  }

  std::cout << d;
}