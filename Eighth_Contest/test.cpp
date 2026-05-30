#include <cstdint>
#include <iostream>

struct State {
  int8_t mv_cnt;
  uint64_t pos;
};

int main() {
  std::cout << sizeof(State);
}