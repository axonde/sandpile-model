#include <iostream>
#include "parser/parser.h"
#include "utility/utility.h"

int main(int argc, char** argv) {
    Args args = Parse(argc, argv);
    if (!args.is_correct) {
        std::cerr << "\e[1;31mIncorrect usage!\e[0m" << '\n';
        PrintUsage();
        return 1;
    }
    std::cout << "Good!" << '\n';
    PrintArgs(args);

    
    return 0;
}