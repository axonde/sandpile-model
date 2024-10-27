#pragma once
#include <cstddef>
#include <string>
#include <iostream>

struct Args {
    std::string input_path;
    std::string output_path;
    uint64_t max_iter = 0;
    uint64_t freq = 0;
    bool is_correct = false;
};

Args Parse(int argc, char** argv);