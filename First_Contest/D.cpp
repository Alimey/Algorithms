#include<iostream>
#include<limits>

double CountExpr(int a, int b, int c, int d, double m) {
  return a * m * m * m + b * m * m + c * m + d;
}

double FindSol(int a, int b, int c, int d) {
  double r = 1'000;
  double l = -1'000;
  if (a < 0) {
    a = -a;
    b = -b;
    c = -c;
    d = -d;
  }

  while (r - l > 0.00000001) {
    double m = (r + l) / 2;
    double expr = CountExpr(a, b, c, d, m);
    if (expr == 0) {
      return m;
    }
    if (expr > 0) {
      r = m;
    } else {
      l = m;
    }
  }
  return r;
}

int main() {
  int a;
  int b;
  int c;
  int d;
  std::cin >> a >> b >> c >> d;
  std::cout.setf(std::ios::fixed);
  const int cPr = 10;
  std::cout.precision(cPr);
  std::cout << FindSol(a, b, c, d);
}