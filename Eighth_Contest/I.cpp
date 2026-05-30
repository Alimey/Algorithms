#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define ll long long
#define sc static_cast<int>
#define lc static_cast<int8_t>

constexpr int cFieldSize = 16;
constexpr int cRowSize = 4;

constexpr int cOne = 1;
constexpr int cTwo = 2;
constexpr int cThree = 3;
constexpr int cFour = 4;
constexpr int cFive = 5;
constexpr int cSix = 6;
constexpr int cSeven = 7;
constexpr int cEight = 8;
constexpr int cNine = 9;
constexpr int cTen = 10;
constexpr int cEleven = 11;
constexpr int cTwelve = 12;
constexpr int cThirteen = 13;
constexpr int cFourteen = 14;
constexpr int cFifteen = 15;

uint64_t PackPos(const std::vector<int>& pos);
uint64_t GetCell(uint64_t pos, int ind);

std::vector endpos_vec{cOne,      cTwo,      cThree,   cFour, cFive,   cSix,
                       cSeven,    cEight,    cNine,    cTen,  cEleven, cTwelve,
                       cThirteen, cFourteen, cFifteen, 0};

uint64_t endpos = PackPos(endpos_vec);

int ManhDist(uint64_t pos) {
  int dist = 0;

  for (int i = 0; i < cFieldSize; ++i) {
    if (GetCell(pos, i) == 0) {
      continue;
    }

    int cur_x = i % cRowSize;
    int cur_y = i / cRowSize;

    int end_x = (GetCell(pos, i) - 1) % cRowSize;
    int end_y = (GetCell(pos, i) - 1) / cRowSize;

    dist += std::abs(end_x - cur_x) + std::abs(end_y - cur_y);
  }

  return dist;
}

struct State {
  uint64_t pos;
  int8_t mv_cnt;

  bool operator<(const State& another) const {
    return ManhDist(pos) + sc(mv_cnt) > ManhDist(another.pos) + sc(another.mv_cnt);
  }
};

uint64_t PackPos(const std::vector<int>& pos) {
  uint64_t ans = 0;
  for (int i = 0; i < cFieldSize; ++i) {
    ans |= (static_cast<uint64_t>(pos[i]) << (4 * i));
  }
  return ans;
}

uint64_t GetCell(uint64_t pos, int ind) {
  const uint64_t cOhMyGod = 0xF;
  return (pos >> (4 * ind)) & cOhMyGod;
}

int GetZeroIndex(uint64_t pos) {
  for (int i = 0; i < cFieldSize; ++i) {
    if (GetCell(pos, i) == 0) {
      return i;
    }
  }
  return -1;
}

void SwapCells(uint64_t& pos, int first_ind, int second_ind) {
  uint64_t first_val = GetCell(pos, first_ind);
  uint64_t second_val = GetCell(pos, second_ind);

  const uint64_t cImTired = 0xFULL;

  uint64_t mask =
      ~(cImTired << (4 * first_ind)) & ~(cImTired << (4 * second_ind));
  pos &= mask;

  pos |= first_val << (4 * second_ind);
  pos |= second_val << (4 * first_ind);
}

char GetStep(uint64_t last, uint64_t prev) {
  int last_zero_index = GetZeroIndex(last);
  int prev_zero_index = GetZeroIndex(prev);

  int x_diff = (last_zero_index % cRowSize - prev_zero_index % cRowSize);
  int y_diff = (last_zero_index / cRowSize - prev_zero_index / cRowSize);

  if (x_diff == 1) {
    return 'L';
  }
  if (x_diff == -1) {
    return 'R';
  }
  if (y_diff == 1) {
    return 'U';
  }
  return 'D';
}

std::string MakePath(uint64_t startpos,
                     std::unordered_map<uint64_t, uint64_t>& from,
                     uint64_t pos) {
  std::string path;
  uint64_t prev = from[pos];
  while (prev != startpos) {
    path.push_back(GetStep(pos, prev));
    pos = prev;
    prev = from[pos];
  }
  path.push_back(GetStep(pos, prev));
  std::reverse(path.begin(), path.end());
  return path;
}

std::string AStar(uint64_t startpos) {
  std::unordered_map<uint64_t, ll> cost;
  std::priority_queue<State> next_states;
  std::unordered_map<uint64_t, uint64_t> from;

  next_states.push({startpos, 0});

  while (!next_states.empty()) {
    State cur = next_states.top();
    next_states.pop();

    if (cur.pos == endpos) {
      return MakePath(startpos, from, endpos);
    }

    int zero_index = GetZeroIndex(cur.pos);

    // move zero left
    if (zero_index % cRowSize != 0 && zero_index - 1 >= 0) {
      uint64_t next_pos = cur.pos;
      SwapCells(next_pos, zero_index, zero_index - 1);

      if (!cost.contains(next_pos) || cost[next_pos] > sc(cur.mv_cnt) + 1) {
        cost[next_pos] = sc(cur.mv_cnt) + 1;
        next_states.push({next_pos, cur.mv_cnt + lc(1)});
        from[next_pos] = cur.pos;
      }
    }

    // move zero right
    if (zero_index % cRowSize != cRowSize - 1) {
      uint64_t next_pos = cur.pos;
      SwapCells(next_pos, zero_index, zero_index + 1);

      if (!cost.contains(next_pos) || cost[next_pos] > sc(cur.mv_cnt) + 1) {
        cost[next_pos] = sc(cur.mv_cnt) + 1;
        next_states.push({next_pos, cur.mv_cnt + lc(1)});
        from[next_pos] = cur.pos;
      }
    }

    // move zero up
    if (zero_index - cRowSize >= 0) {
      uint64_t next_pos = cur.pos;
      SwapCells(next_pos, zero_index, zero_index - cRowSize);

      if (!cost.contains(next_pos) || cost[next_pos] > sc(cur.mv_cnt) + 1) {
        cost[next_pos] = sc(cur.mv_cnt) + 1;
        next_states.push({next_pos, cur.mv_cnt + lc(1)});
        from[next_pos] = cur.pos;
      }
    }

    // move zero down
    if (zero_index + cRowSize < cFieldSize) {
      uint64_t next_pos = cur.pos;
      SwapCells(next_pos, zero_index, zero_index + cRowSize);

      if (!cost.contains(next_pos) || cost[next_pos] > sc(cur.mv_cnt) + 1) {
        cost[next_pos] = sc(cur.mv_cnt) + 1;
        next_states.push({next_pos, cur.mv_cnt + lc(1)});
        from[next_pos] = cur.pos;
      }
    }
  }

  return "-1";
}

int main() {
  freopen("input.txt", "r", stdin);

  std::vector<int> startpos_vec(cFieldSize);
  for (int i = 0; i < cFieldSize; ++i) {
    std::cin >> startpos_vec[i];
  }

  uint64_t startpos = PackPos(startpos_vec);
  std::string move_seq = AStar(startpos);
  if (move_seq == "-1") {
    std::cout << -1;
  } else {
    std::cout << move_seq.size() << "\n";
    std::cout << move_seq;
  }
}