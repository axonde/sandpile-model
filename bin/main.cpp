#include <cstdint>
#include <iostream>
// #include "deque/deque.h"
#include "parser/parser.h"
#include "utility/utility.h"
#include "vector/vector.h"

int main(int argc, char** argv) {
    Args args = Parse(argc, argv);
    if (!args.is_correct) {
        std::cerr << "\e[1;31mIncorrect usage!\e[0m" << '\n';
        PrintUsage();
        return 1;
    }
    std::cout << "Good!" << '\n';
    PrintArgs(args);

    // Vector<Vector<uint64_t>> v(1e8);
    // // v.push_front(Vector<uint64_t>(100));
    // // v[0].push_back(12324324);
    // // v[0][0] = 126;
    // // std::cout << v[0][0] << '\n';
    // for (int i = 0; i != 1e7; ++i) {
    //     v.push_back(Vector<uint64_t>());
    // }

    return 0;
}