#include<cmath>
#include<iostream>
#include<vector>

long double GeometricMean(std::vector<long double>& gm, int l, int r) {
  if (l == 0) {
    return std::pow(2, gm[r]);
  }
  long double gmlr = 1.0 / (r - l + 1) * (gm[r] * (r + 1) - gm[l - 1] * l);
  long double ans = std::pow(2, gmlr);
  return ans;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<double> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  std::vector<long double> gm(n);
  gm[0] = std::log2(a[0]);
  for (int i = 1; i < n; i++) {
    gm[i] = 1.0 / (i + 1) * (gm[i - 1] * i + std::log2(a[i]));
  }

  int q;
  std::cin >> q;
  std::vector<long double> ans;
  for (int i = 0; i < q; i++) {
    int l;
    int r;
    std::cin >> l >> r;
    ans.push_back(GeometricMean(gm, l, r));
  }

  for (long double x : ans) {
    std::cout.setf(std::ios::fixed);
    const int cPr = 10;
    std::cout.precision(cPr);
    std::cout << x << "\n";
  }
}