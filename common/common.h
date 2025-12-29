#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#define INPUT_FILE_NAME "test.txt"

inline std::vector<std::string> read_input(const std::string& filename) {
    std::vector<std::string> lines;
    std::ifstream infile(filename);
    std::string line;
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }
    return lines;
}