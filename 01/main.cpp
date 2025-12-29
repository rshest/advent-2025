#include "../common/common.h"

#include <cmath>
#include <stdio.h>

enum class Direction {
  Left,
  Right,
};

struct Operation {
  Direction direction;
  int amount;
};

Operation parse_operation(const std::string &line) {
  Operation op;
  char dir;
  sscanf(line.c_str(), "%c %d", &dir, &op.amount);
  op.direction = (dir == 'L') ? Direction::Left : Direction::Right;
  return op;
}

int apply_operation(int cur_dir, const Operation &op) {
  const int pos =
      cur_dir + (op.direction == Direction::Left ? -1 : 1) * op.amount;
  // make sure it's positive:
  return (pos + 100 * (abs(pos) / 100 + 1)) % 100;
}

int get_num_crossings(int cur_dir, const Operation &op) {
  const int pos =
      op.direction == Direction::Left ? (100 - cur_dir) % 100 : cur_dir;
  return (pos + op.amount) / 100;
}

int main() {
  auto lines = read_input(INPUT_FILE_NAME);
  int cur_dir = 50;
  int num_zeros = 0;
  int num_crossings = 0;
  for (const auto &line : lines) {
    auto op = parse_operation(line);
    num_crossings += get_num_crossings(cur_dir, op);
    cur_dir = apply_operation(cur_dir, op);
    num_zeros += (cur_dir == 0);
  }
  printf("Answer 1: %d\nAnswer 2: %d\n", num_zeros, num_crossings);
  return 0;
}