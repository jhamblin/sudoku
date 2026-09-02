#include <iostream>

#define SUDOKU_TEST 1
#define main sudoku_program_main
#include "sudoku.cpp"
#undef main

int main() {
    sudoku::runTests();
    std::cout << "All tests passed.\n";
    return 0;
}
