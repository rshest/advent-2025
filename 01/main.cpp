#include "../common/common.h"

#include <algorithm>
#include <cmath>
#include <stdio.h>

const int START_DIR = 50;

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

int part1(const std::vector<Operation> &operations) {
  int cur_dir = START_DIR;
  int num_zeros = 0;
  for (const auto &op : operations) {
    cur_dir = apply_operation(cur_dir, op);
    num_zeros += (cur_dir == 0);
  }
  return num_zeros;
}

int part2(const std::vector<Operation> &operations) {
  int cur_dir = START_DIR;
  int num_crossings = 0;
  for (const auto &op : operations) {
    num_crossings += get_num_crossings(cur_dir, op);
    cur_dir = apply_operation(cur_dir, op);
  }
  return num_crossings;
}

int main() {
  auto lines = read_input(INPUT_FILE_NAME);
  std::vector<Operation> operations(lines.size());
  std::transform(lines.begin(), lines.end(), operations.begin(),
                 parse_operation);

  TIME1(part1(operations));
  TIME2(part2(operations));
  return 0;
}