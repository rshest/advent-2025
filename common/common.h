#pragma once

#include <chrono>
#include <cmath>
#include <cstdint>
#include <execution>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#define TIME(Id, CodeBlock)                                                    \
  {                                                                            \
    auto start = std::chrono::high_resolution_clock::now();                    \
    auto res = CodeBlock;                                                      \
    auto end = std::chrono::high_resolution_clock::now();                      \
    std::chrono::duration<double, std::milli> duration = end - start;          \
    std::cout << "Answer" << Id << " (" << duration.count() << " ms): " << res \
              << std::endl;                                                    \
  }

#define TIME1(CodeBlock) TIME(1, CodeBlock)
#define TIME2(CodeBlock) TIME(2, CodeBlock)

#ifdef LOCAL_TEST
#define INPUT_FILE_NAME "input.txt"
#else
#define INPUT_FILE_NAME "test.txt"
#endif

inline std::vector<std::string> read_input(const std::string &filename) {
  std::vector<std::string> lines;
  std::ifstream infile(filename);
  std::string line;
  while (std::getline(infile, line)) {
    lines.push_back(line);
  }
  return lines;
}

inline std::vector<std::string> split_by(const std::string &str,
                                         const std::string &delimiter) {
  std::vector<std::string> res;
  if (str.empty()) {
    return res;
  }
  std::string val;
  size_t pos = 0;
  while (true) {
    const size_t pos_end = str.find(delimiter, pos);
    if (pos_end == std::string::npos) {
      res.push_back(str.substr(pos, str.size() - pos));
      break;
    }
    res.push_back(str.substr(pos, pos_end - pos));
    pos = pos_end + delimiter.length();
  }
  return res;
}

template <typename T, typename TRes>
TRes acc_elements(const std::vector<T> &ranges, TRes (*fn)(const T &),
                  bool parallel = false) {
  return parallel ? std::transform_reduce(std::execution::par, ranges.begin(),
                                          ranges.end(), TRes{},
                                          std::plus<TRes>(), fn)
                  : std::transform_reduce(ranges.begin(), ranges.end(), TRes{},
                                          std::plus<TRes>(), fn);
}