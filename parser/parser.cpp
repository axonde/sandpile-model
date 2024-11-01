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
            args.max_iter = std::stoll(argv[i++ + 1]);
            continue;
        }
        if (arg == "--freq" || arg == "-f") {
            args.freq = std::stoll(argv[i++ + 1]);
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
    }
    args.is_correct = true;
    return args;
}

Sandpile Read(const std::string& filepath) {
    std::ifstream input(filepath, std::ios::in);
    if (!input.is_open()) {
        return Sandpile();
    }
    Sandpile sandpile;
    int64_t x, y;
    uint64_t piles;
    int64_t min_x, min_y, max_x, max_y;
    input >> min_x >> min_y >> piles;
    if (piles > 3) {
        sandpile.unstables += 1;
    }
    max_x = min_x;
    max_y = min_y;
    while (input >> x >> y >> piles) {
        if (x < min_x) {
            min_x = x;
        }
        if (x > max_x) {
            max_x = x;
        }
        if (y < min_y) {
            min_y = y;
        }
        if (y > max_y) {
            max_y = y;
        }
        if (piles > 3) {
            sandpile.unstables += 1;
        }
    }

    for (size_t y = min_y; y != max_y + 1; ++y) {
        sandpile.matrix.push_back(Vector<Pixel>());
        for (size_t x = min_x; x != max_x + 1; ++x) {
            sandpile.matrix[y - min_y].push_back(Pixel());
        }
    }

    input.clear();
    input.seekg(0, input.beg);

    while (input >> x >> y >> piles) {
        sandpile.matrix[y - min_y][x - min_x].piles = piles;
    }

    return sandpile;
}
