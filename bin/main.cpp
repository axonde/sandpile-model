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

    Vector<Vector<uint64_t>> v(3);
    v[0].push_back(1);
    v[0].push_back(2);
    v[0].push_back(3);
    v[1].push_back(4);
    v[1].push_back(5);
    v[1].push_back(6);
    v[2].push_back(7);
    v[2].push_back(8);
    v[2].push_back(9);
    for (int i = 0; i != 3; ++i) {
        for (int j = 0; j != 3; ++j) {
            std::cout << v[i][j] << ' ';
        }
        std::cout << '\n';
    }
    // // v.push_front(Vector<uint64_t>(100));
    // // v[0].push_back(12324324);
    // // v[0][0] = 126;
    // // std::cout << v[0][0] << '\n';
    // for (int i = 0; i != 1e7; ++i) {
    //     v.push_back(Vector<uint64_t>());
    // }

    return 0;
}