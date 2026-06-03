#include <array>
#include <cstddef>
#include <iostream>
#include <ostream>

#ifndef SUDOKU_TEST
#define SUDOKU_TEST 0
#endif

#if SUDOKU_TEST
#include <cassert>
#define SUDOKU_ASSERT(condition) assert(condition)
#else
#define SUDOKU_ASSERT(condition) ((void)0)
#endif

namespace sudoku {

constexpr std::size_t kBoardSize = 9;
constexpr std::size_t kBoxSize = 3;
using Board = std::array<std::array<int, kBoardSize>, kBoardSize>;

bool isValueInRange(int value) {
    return value >= 0 && value <= static_cast<int>(kBoardSize);
}

bool isCandidateInRange(int candidate) {
    return candidate >= 1 && candidate <= static_cast<int>(kBoardSize);
}

bool isValidForRow(const Board& board, std::size_t row, int candidate) {
    for (std::size_t col = 0; col < kBoardSize; ++col) {
        if (board[row][col] == candidate) {
            return false;
        }
    }
    return true;
}

bool isValidForColumn(const Board& board, std::size_t col, int candidate) {
    for (std::size_t row = 0; row < kBoardSize; ++row) {
        if (board[row][col] == candidate) {
            return false;
        }
    }
    return true;
}

bool isValidForBox(const Board& board, std::size_t row, std::size_t col, int candidate) {
    const std::size_t firstRow = kBoxSize * (row / kBoxSize);
    const std::size_t firstCol = kBoxSize * (col / kBoxSize);

    for (std::size_t boxRow = firstRow; boxRow < firstRow + kBoxSize; ++boxRow) {
        for (std::size_t boxCol = firstCol; boxCol < firstCol + kBoxSize; ++boxCol) {
            if (board[boxRow][boxCol] == candidate) {
                return false;
            }
        }
    }

    return true;
}

bool isValidPlacement(const Board& board, std::size_t row, std::size_t col, int candidate) {
    return isCandidateInRange(candidate) &&
           isValidForRow(board, row, candidate) &&
           isValidForColumn(board, col, candidate) &&
           isValidForBox(board, row, col, candidate);
}

bool findEmptyCell(const Board& board, std::size_t& row, std::size_t& col) {
    for (row = 0; row < kBoardSize; ++row) {
        for (col = 0; col < kBoardSize; ++col) {
            if (board[row][col] == 0) {
                return true;
            }
        }
    }

    return false;
}

bool isBoardShapeValid(const Board& board) {
    for (const auto& row : board) {
        for (int value : row) {
            if (!isValueInRange(value)) {
                return false;
            }
        }
    }

    return true;
}

bool hasNoConflicts(const Board& board) {
    for (std::size_t row = 0; row < kBoardSize; ++row) {
        for (std::size_t col = 0; col < kBoardSize; ++col) {
            const int value = board[row][col];
            if (value == 0) {
                continue;
            }

            Board boardWithoutCurrent = board;
            boardWithoutCurrent[row][col] = 0;
            if (!isValidPlacement(boardWithoutCurrent, row, col, value)) {
                return false;
            }
        }
    }

    return true;
}

bool isBoardValid(const Board& board) {
    return isBoardShapeValid(board) && hasNoConflicts(board);
}

bool isSolved(const Board& board) {
    std::size_t row = 0;
    std::size_t col = 0;
    return hasNoConflicts(board) && !findEmptyCell(board, row, col);
}

bool solve(Board& board) {
    std::size_t row = 0;
    std::size_t col = 0;
    if (!findEmptyCell(board, row, col)) {
        return true;
    }

    for (int candidate = 1; candidate <= static_cast<int>(kBoardSize); ++candidate) {
        if (!isValidPlacement(board, row, col, candidate)) {
            continue;
        }

        board[row][col] = candidate;
        if (solve(board)) {
            return true;
        }

        board[row][col] = 0;
    }

    return false;
}

void printBoard(const Board& board, std::ostream& output = std::cout) {
    output << "+-------+-------+-------+\n";
    for (std::size_t row = 0; row < kBoardSize; ++row) {
        output << "| ";
        for (std::size_t col = 0; col < kBoardSize; ++col) {
            if (board[row][col] == 0) {
                output << ". ";
            } else {
                output << board[row][col] << ' ';
            }

            if ((col + 1) % kBoxSize == 0) {
                output << "| ";
            }
        }
        output << '\n';

        if ((row + 1) % kBoxSize == 0) {
            output << "+-------+-------+-------+\n";
        }
    }
}

#if SUDOKU_TEST
void runTests() {
    const Board easyPuzzle = {{{6, 0, 0, 9, 5, 0, 8, 0, 0},
                               {0, 0, 5, 1, 0, 3, 0, 0, 0},
                               {0, 1, 0, 0, 6, 0, 0, 0, 0},
                               {1, 7, 0, 3, 0, 0, 0, 6, 2},
                               {3, 0, 4, 0, 0, 0, 7, 0, 8},
                               {2, 5, 0, 0, 0, 4, 0, 3, 9},
                               {0, 0, 0, 0, 3, 0, 0, 8, 0},
                               {0, 0, 0, 2, 0, 1, 3, 0, 0},
                               {0, 0, 9, 0, 8, 6, 0, 0, 1}}};

    const Board easySolution = {{{6, 4, 2, 9, 5, 7, 8, 1, 3},
                                 {7, 8, 5, 1, 2, 3, 9, 4, 6},
                                 {9, 1, 3, 4, 6, 8, 5, 2, 7},
                                 {1, 7, 8, 3, 9, 5, 4, 6, 2},
                                 {3, 9, 4, 6, 1, 2, 7, 5, 8},
                                 {2, 5, 6, 8, 7, 4, 1, 3, 9},
                                 {5, 2, 1, 7, 3, 9, 6, 8, 4},
                                 {8, 6, 7, 2, 4, 1, 3, 9, 5},
                                 {4, 3, 9, 5, 8, 6, 2, 7, 1}}};

    const Board hardSolution = {{{1, 5, 7, 9, 6, 3, 4, 8, 2},
                                 {6, 8, 3, 4, 1, 2, 5, 7, 9},
                                 {9, 2, 4, 7, 8, 5, 6, 1, 3},
                                 {8, 4, 6, 2, 3, 7, 9, 5, 1},
                                 {5, 3, 1, 8, 9, 4, 7, 2, 6},
                                 {2, 7, 9, 1, 5, 6, 8, 3, 4},
                                 {4, 6, 2, 5, 7, 1, 3, 9, 8},
                                 {3, 9, 5, 6, 2, 8, 1, 4, 7},
                                 {7, 1, 8, 3, 4, 9, 2, 6, 5}}};

    const Board hardPuzzle = {{{0, 0, 0, 9, 0, 0, 0, 0, 0},
                               {6, 0, 3, 0, 1, 2, 5, 0, 0},
                               {9, 0, 0, 0, 0, 0, 0, 0, 3},
                               {0, 0, 6, 2, 0, 0, 0, 5, 1},
                               {0, 0, 1, 0, 0, 0, 7, 0, 0},
                               {2, 7, 0, 0, 0, 6, 8, 0, 0},
                               {4, 0, 0, 0, 0, 0, 0, 0, 8},
                               {0, 0, 5, 6, 2, 0, 1, 0, 7},
                               {0, 0, 0, 0, 0, 9, 0, 0, 0}}};

    const Board invalidPuzzle = {{{6, 6, 0, 9, 5, 0, 8, 0, 0},
                                  {0, 0, 5, 1, 0, 3, 0, 0, 0},
                                  {0, 1, 0, 0, 6, 0, 0, 0, 0},
                                  {1, 7, 0, 3, 0, 0, 0, 6, 2},
                                  {3, 0, 4, 0, 0, 0, 7, 0, 8},
                                  {2, 5, 0, 0, 0, 4, 0, 3, 9},
                                  {0, 0, 0, 0, 3, 0, 0, 8, 0},
                                  {0, 0, 0, 2, 0, 1, 3, 0, 0},
                                  {0, 0, 9, 0, 8, 6, 0, 0, 1}}};

    {
        Board puzzle = easyPuzzle;
        SUDOKU_ASSERT(isBoardValid(puzzle));
        SUDOKU_ASSERT(solve(puzzle));
        SUDOKU_ASSERT(puzzle == easySolution);
        SUDOKU_ASSERT(isSolved(puzzle));
    }

    {
        Board puzzle = hardPuzzle;
        SUDOKU_ASSERT(isBoardValid(puzzle));
        SUDOKU_ASSERT(solve(puzzle));
        SUDOKU_ASSERT(puzzle == hardSolution);
        SUDOKU_ASSERT(isSolved(puzzle));
    }

    {
        Board puzzle = invalidPuzzle;
        SUDOKU_ASSERT(!isBoardValid(puzzle));
    }

    {
        Board puzzle = easyPuzzle;
        SUDOKU_ASSERT(isValidPlacement(puzzle, 0, 1, 3));
        SUDOKU_ASSERT(!isValidPlacement(puzzle, 0, 1, 6));
    }

    {
        std::size_t row = 0;
        std::size_t col = 0;
        Board puzzle = easySolution;
        SUDOKU_ASSERT(!findEmptyCell(puzzle, row, col));
        SUDOKU_ASSERT(isSolved(puzzle));
    }
}
#endif

Board samplePuzzle() {
    return {{{0, 0, 0, 9, 0, 0, 0, 0, 0},
             {6, 0, 3, 0, 1, 2, 5, 0, 0},
             {9, 0, 0, 0, 0, 0, 0, 0, 3},
             {0, 0, 6, 2, 0, 0, 0, 5, 1},
             {0, 0, 1, 0, 0, 0, 7, 0, 0},
             {2, 7, 0, 0, 0, 6, 8, 0, 0},
             {4, 0, 0, 0, 0, 0, 0, 0, 8},
             {0, 0, 5, 6, 2, 0, 1, 0, 7},
             {0, 0, 0, 0, 0, 9, 0, 0, 0}}};
}

}  // namespace sudoku

int main() {
    sudoku::Board puzzle = sudoku::samplePuzzle();
    if (!sudoku::isBoardValid(puzzle)) {
        std::cerr << "Puzzle is invalid.\n";
        return 1;
    }

    std::cout << "Input puzzle:\n";
    sudoku::printBoard(puzzle);

    if (!sudoku::solve(puzzle)) {
        std::cerr << "Puzzle has no solution.\n";
        return 1;
    }

    std::cout << "Solved puzzle:\n";
    sudoku::printBoard(puzzle);
    return 0;
}
