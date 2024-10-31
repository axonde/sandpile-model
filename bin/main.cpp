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

    Sandpile sandpile;

    sandpile = Read(args.input_path);
    if (sandpile.matrix.empty()) {
        std::cerr << "Error while parsing .tsv input file. Please retry." << '\n';
        return 1;
    }

    std::cout << "x y piles" << '\n';
    for (int i = 0; i != sandpile.matrix.size(); ++i) {
        for (int j = 0; j != sandpile.matrix[i].size(); ++j) {
            std::cout << j << ' ' << i << ' ' << sandpile.matrix[i][j].piles << '\n';
        }
    }

    Shake(sandpile, args.max_iter, args.freq);

    std::cout << "after shaking >> " << '\n';
    std::cout << "x y piles" << '\n';
    for (int i = 0; i != sandpile.matrix.size(); ++i) {
        for (int j = 0; j != sandpile.matrix[i].size(); ++j) {
            std::cout << j << ' ' << i << ' ' << sandpile.matrix[i][j].piles << '\n';
        }
    }


    return 0;
}
