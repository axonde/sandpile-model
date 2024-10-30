#include <cstdint>
#include <iostream>
// #include "deque/deque.h"
#include "parser/parser.h"
#include "sandpile/sandpile.h"
#include "utility/utility.h"
#include "vector/vector.h"

int main(int argc, char** argv) {
    Args args = Parse(argc, argv);
    if (!args.is_correct) {
        std::cerr << "\e[1;31mIncorrect usage!\e[0m" << '\n';
        PrintUsage();
        return 1;
    }
    PrintArgs(args);

    Vector<Vector<Pixel>> sandpile = Read(args.input_path);
    if (sandpile.empty()) {
        std::cerr << "Error while parsing .tsv input file. Please retry." << '\n';
        return 1;
    }

    std::cout << "x y piles" << '\n';
    for (int i = 0; i != sandpile.size(); ++i) {
        for (int j = 0; j != sandpile[i].size(); ++j) {
            std::cout << j << ' ' << i << ' ' << sandpile[i][j].piles << '\n';
        }
    }

    return 0;
}