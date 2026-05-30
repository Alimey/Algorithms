#include <algorithm>
#include <iostream>
#include <vector>

struct EsqElement {
  bool greater_than_prev = true;
  int len = 1;
};

void DoFirst(int n, std::vector<int>& prev, std::vector<EsqElement>& dp,
             std::vector<int>& a) {
  for (int i = 0; i < n; ++i) {
    int max_greater = -1;
    int max_smaller = -1;
    for (int j = 0; j < i; ++j) {
      if (a[j] < a[i] && !dp[j].greater_than_prev &&
          (max_smaller == -1 || dp[max_smaller].len < dp[j].len)) {
        max_smaller = j;
      }
      if (a[j] > a[i] && dp[j].greater_than_prev &&
          (max_greater == -1 || dp[max_greater].len < dp[j].len)) {
        max_greater = j;
      }
    }
    if (max_greater == -1 && max_smaller == -1) {
      continue;
    }
    if (max_smaller == -1 ||
        (max_greater != -1 && dp[max_greater].len > dp[max_smaller].len)) {
      dp[i].len = dp[max_greater].len + 1;
      dp[i].greater_than_prev = false;
      prev[i] = max_greater;
    } else {
      dp[i].len = dp[max_smaller].len + 1;
      dp[i].greater_than_prev = true;
      prev[i] = max_smaller;
    }
  }
}

void DoSecond(int n, std::vector<int>& second_prev, std::vector<EsqElement>& dp,
              std::vector<int>& a) {
  for (int i = 0; i < n; ++i) {
    int max_greater = -1;
    int max_smaller = -1;
    for (int j = 0; j < i; ++j) {
      if (a[j] < a[i] && !dp[j].greater_than_prev &&
          (max_smaller == -1 || dp[max_smaller].len < dp[j].len)) {
        max_smaller = j;
      }
      if (a[j] > a[i] && dp[j].greater_than_prev &&
          (max_greater == -1 || dp[max_greater].len < dp[j].len)) {
        max_greater = j;
      }
    }
    if (max_greater == -1 && max_smaller == -1) {
      continue;
    }
    if (max_smaller == -1 ||
        (max_greater != -1 && dp[max_greater].len > dp[max_smaller].len)) {
      dp[i].len = dp[max_greater].len + 1;
      dp[i].greater_than_prev = false;
      second_prev[i] = max_greater;
    } else {
      dp[i].len = dp[max_smaller].len + 1;
      dp[i].greater_than_prev = true;
      second_prev[i] = max_smaller;
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  freopen("input.txt", "r", stdin);

  int n;
  std::cin >> n;

  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }

  // First part - first element is greater than second

  std::vector<int> prev(n, -1);

  std::vector<EsqElement> dp(n);

  DoFirst(n, prev, dp, a);

  int max_len = 0;
  int id = -1;
  for (int i = 0; i < n; ++i) {
    if (max_len < dp[i].len) {
      max_len = dp[i].len;
      id = i;
    }
  }

  std::vector<int> ans;
  while (id != -1) {
    ans.push_back(a[id]);
    id = prev[id];
  }

  // Second part - second element is smaller than second

  std::vector<int> second_prev(n, -1);

  for (int i = 0; i < n; ++i) {
    dp[i] = {false, 1};
  }

  DoSecond(n, second_prev, dp, a);

  int max_len_second = 0;
  int id_second = -1;
  for (int i = 0; i < n; ++i) {
    if (max_len_second < dp[i].len) {
      max_len_second = dp[i].len;
      id_second = i;
    }
  }

  std::vector<int> ans_second;
  while (id_second != -1) {
    ans_second.push_back(a[id_second]);
    id_second = second_prev[id_second];
  }

  std::cout << std::max(max_len, max_len_second) << "\n";
  if (max_len > max_len_second) {
    std::reverse(ans.begin(), ans.end());
    for (auto x : ans) {
      std::cout << x << " ";
    }
  } else {
    std::reverse(ans_second.begin(), ans_second.end());
    for (auto x : ans_second) {
      std::cout << x << " ";
    }
  }
}