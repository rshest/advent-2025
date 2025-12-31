#include "../common/common.h"

#include <algorithm>
#include <cmath>
#include <stdio.h>

typedef uint64_t num_t;

struct Range {
  num_t start;
  num_t end;
};

Range parse_range(const std::string &str) {
  Range range;
  auto parts = split_by(str, "-");
  range.start = std::stoull(parts[0]);
  range.end = std::stoull(parts[1]);
  return range;
}

num_t num_digits(num_t val) {
  if (val == 0ul) {
    return 1ul;
  }
  return std::log10(val) + 1ul;
}

num_t get_half_pivot(num_t start_val) {
  const int digits = num_digits(start_val);
  if (digits % 2 == 0) {
    return start_val / std::pow(10uL, digits / 2);
  } else {
    return std::pow(10uL, digits / 2);
  }
}

num_t part1(const Range &range) {
  num_t res = 0;

  num_t pivot = get_half_pivot(range.start);
  num_t pivot_base = std::pow(10, num_digits(pivot));

  while (true) {
    const num_t test_num = pivot * pivot_base + pivot;
    if (test_num > range.end) {
      break;
    } else if (test_num >= range.start) {
      res += test_num;
    }

    pivot++;
    if (pivot == pivot_base) {
      pivot_base *= 10;
    }
  }

  return res;
}

num_t part2(const Range &range) {
  num_t res = 0;

  num_t pivot_start = get_half_pivot(range.start);
  const num_t num_start_digits = num_digits(range.start);
  const num_t num_end_digits = num_digits(range.end);

  num_t pivot = pivot_start;
  num_t num_pivot_digits = num_digits(pivot_start);
  num_t pivot_base = std::pow(10, num_pivot_digits);

  printf("Range: %llu-%llu, IDs: ", range.start, range.end);

  while (num_pivot_digits < num_end_digits) {
    num_t test_num = pivot;
    for (num_t i = num_pivot_digits; i < num_start_digits;
         i += num_pivot_digits) {
      test_num = test_num * pivot_base + pivot;
    }

    if (test_num > range.end) {
      break;
    } else if (test_num >= range.start) {
      res += test_num;
      printf(" %llu ", test_num);
    }

    pivot++;
    if (pivot == pivot_base) {
      pivot_base *= 10;
      num_pivot_digits++;
    }
  }

  printf("\n\n");

  return res;
}

int main() {
  auto lines = read_input("input.txt");
  auto parts = split_by(lines[0], ",");
  std::vector<Range> ranges(parts.size());
  std::transform(parts.begin(), parts.end(), ranges.begin(), parse_range);

  TIME1(acc_elements(ranges, part1));
  TIME2(acc_elements(ranges, part2));

  return 0;
}