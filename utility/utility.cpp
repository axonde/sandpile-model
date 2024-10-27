#include "utility.h"

void PrintUsage() {
    std::cout << "Usage: ./sandpile-model [options][paths... / size...]\n";
    std::cout << "Options:\n";
    std::cout << "  " << "-i --input <.tsv file>" << "\t\t\t" << "input file\n";
    std::cout << "  " << "-o --output <path>" << "\t\t\t\t" << "path to the output directory\n";
    std::cout << "  " << "-m --max-iter <unsigned number>" << "\t\t" << "maximum counts of providing iterations\n";
    std::cout << "  " << "-f --freq <number>" << "\t\t\t\t" << "frequency of saving got image states\n";
}

void PrintArgs(Args args) {
    std::cout << "\e[33m[PrintArgs] >> ";
    std::cout << "\t input_path: " << args.input_path << '\n';
    std::cout << "\t\t output_path: " << args.output_path << '\n';
    std::cout << "\t\t max iter: " << args.max_iter << '\n';
    std::cout << "\t\t freq: " << args.freq << '\n';
    std::cout << "\t\t is_correct: " << args.is_correct << '\n' << "\e[0m";
}