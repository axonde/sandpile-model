#include <iostream>
#include "deque/deque.h"
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

    Deque<int> deq;
    deq.push_front(12);
    deq.push_front(2);
    deq.push_front(52);
    deq.push_front(1);
    Deque<int> deq2(3);
    deq.pop_head();

    Deque<Deque<int>> deq_special;
    deq_special.push_front(deq);
    deq_special.push_front(deq);

    deq_special.push_front(deq);

    std::cout << "ПЕЧАТЬ" << '\n';
    std::cout << deq << '\n';
    std::cout << "next" << '\n';
    std::cout << deq2 << '\n';
    std::cout << "next" << '\n';
    std::cout << deq_special << '\n';

    std::cout << "ЧИСТКА" << '\n';

    return 0;
}