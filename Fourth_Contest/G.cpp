#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

struct Command {
  std::string command;
  long long value;
};

struct FenwickTree {
  std::vector<long long> tree;
  long long n;

  FenwickTree(long long n) : tree(std::vector<long long>(n + 1)), n(n) {}

  void Add(long long pos, long long x) {
    while (pos <= n) {
      tree[pos] += x;
      pos += pos & -pos;
    }
  }

  long long PrefSum(long long rb) {
    long long ans = 0;
    while (rb > 0) {
      ans += tree[rb];
      rb -= rb & -rb;
    }
    return ans;
  }
};

int main() {
  freopen("input.txt", "r", stdin);
  std::ios_base::sync_with_stdio(false);

  long long q;
  std::cin >> q;
  std::vector<long long> ans;
  std::vector<Command> commands;
  std::map<long long, long long> indexes;
  long long id = 1;
  std::vector<long long> addings;
  for (long long i = 0; i < q; ++i) {
    Command command;
    std::cin >> command.command >> command.value;
    commands.push_back(command);
    addings.push_back(command.value);
  }
  std::sort(addings.begin(), addings.end());
  for (auto& element : addings) {
    if (indexes.contains(element)) {
      continue;
    }
    indexes[element] = id++;
  }
  FenwickTree ft((long long)indexes.size());
  for (auto& command : commands) {
    if (command.command == "+") {
      ft.Add(indexes[command.value], command.value);
    }
    if (command.command == "?") {
      ans.push_back(ft.PrefSum(indexes[command.value]));
    }
  }
  for (size_t i = 0; i < ans.size(); ++i) {
    std::cout << ans[i] << "\n";
  }
}