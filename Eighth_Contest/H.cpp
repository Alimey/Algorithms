#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

constexpr int cFieldSize = 16;
constexpr int cRowSize = 4;
std::string endpos{"1234567890"};

int ManhDist(const std::string& pos) {
  int dist = 0;

  for (int i = 0; i < cFieldSize; ++i) {
    if (pos[i] == '0') {
      continue;
    }

    int pos_val = pos[i] - '0';

    int cur_x = i % cRowSize;
    int cur_y = i / cRowSize;

    int end_x = (pos_val - 1) % cRowSize;
    int end_y = (pos_val - 1) / cRowSize;

    dist += std::abs(end_x - cur_x) + std::abs(end_y - cur_y);
  }

  return dist;
}

struct State {
  std::string pos;

  int move_count;
  int evristic;

  std::string path;

  bool operator<(const State& another) const {
    return evristic > another.evristic;
  }
};

int GetZeroIndex(const std::string& pos) {
  for (int i = 0; i < cFieldSize; ++i) {
    if (pos[i] == '0') {
      return i;
    }
  }
  return -1;
}

std::string AStar(const std::string& startpos) {
  std::unordered_set<std::string> visited;
  std::priority_queue<State> next_states;

  next_states.push({startpos, 0, ManhDist(startpos), ""});

  while (!next_states.empty()) {
    State cur = next_states.top();
    next_states.pop();

    if (cur.pos == endpos) {
      return cur.path;
    }

    if (visited.contains(cur.pos)) {
      continue;
    }

    visited.insert(cur.pos);

    int zero_index = GetZeroIndex(cur.pos);

    // move zero up
    if (zero_index - cRowSize >= 0) {
      std::string next_pos = cur.pos;
      std::swap(next_pos[zero_index], next_pos[zero_index - cRowSize]);

      if (!visited.contains(next_pos)) {
        next_states.push({next_pos, cur.move_count + 1,
                          ManhDist(next_pos) + cur.move_count + 1,
                          cur.path + 'U'});
      }
    }

    // move zero down
    if (zero_index + cRowSize < cFieldSize) {
      std::string next_pos = cur.pos;
      std::swap(next_pos[zero_index], next_pos[zero_index + cRowSize]);

      if (!visited.contains(next_pos)) {
        next_states.push({next_pos, cur.move_count + 1,
                          ManhDist(next_pos) + cur.move_count + 1,
                          cur.path + 'D'});
      }
    }

    // move zero left
    if (zero_index % cRowSize != 0 && zero_index - 1 >= 0) {
      std::string next_pos = cur.pos;
      std::swap(next_pos[zero_index], next_pos[zero_index - 1]);

      if (!visited.contains(next_pos)) {
        next_states.push({next_pos, cur.move_count + 1,
                          ManhDist(next_pos) + cur.move_count + 1,
                          cur.path + 'L'});
      }
    }

    // move zero right
    if (zero_index % cRowSize != 2) {
      std::string next_pos = cur.pos;
      std::swap(next_pos[zero_index], next_pos[zero_index + 1]);

      if (!visited.contains(next_pos)) {
        next_states.push({next_pos, cur.move_count + 1,
                          ManhDist(next_pos) + cur.move_count + 1,
                          cur.path + 'R'});
      }
    }
  }

  return "-1";
}

int main() {
  freopen("input.txt", "r", stdin);

  std::string startpos;
  for (int i = 0; i < cFieldSize; ++i) {
    int x;
    std::cin >> x;
    startpos.push_back(x + '0');
  }

  std::string move_seq = AStar(startpos);
  if (move_seq == "-1") {
    std::cout << -1;
  } else {
    std::cout << move_seq.size() << "\n";
    std::cout << move_seq;
  }
}