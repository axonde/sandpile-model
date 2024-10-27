#include "parser.h"

Args Parse(int argc, char** argv) {
    Args args;
    if (argc < 7) {
        return args;
    }

    std::string arg;
    for (int i = 1; i != argc; ++i) {
        arg = std::string(argv[i]);
        if (arg == "--input" || arg == "-i") {
            args.input_path = std::string(argv[i++ + 1]);
            continue;
        }
        if (arg == "--output" || arg == "-o") {
            args.output_path = std::string(argv[i++ + 1]);
            continue;
        }
        if (arg == "--max-iter" || arg == "-m") {
            args.max_iter = std::stoi(argv[i++ + 1]);
            continue;
        }
        if (arg == "--freq" || arg == "-f") {
            args.freq = std::stoi(argv[i++ + 1]);
            continue;
        }
        return args;
    }
    {
        if (args.input_path == "") {
            return args;
        }
        if (args.output_path == "") {
            return args;
        }
        if (args.max_iter < 1) {
            return args;
        }
    }
    args.is_correct = true;
    return args;
}