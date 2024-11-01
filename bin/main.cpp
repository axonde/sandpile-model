#include <cstdint>
#include <iostream>
#include "vector/vector.h"
#include "sandpile/sandpile.h"
#include "parser/parser.h"
#include "image/image.h"
#include "utility/utility.h"

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

    Shake(sandpile, args);

    Export(sandpile.matrix, args.output_path, "sandpile-output.bmp");

    return 0;
}
