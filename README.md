# Sudoku Solver

This repository contains a cleaned-up version of an old interview exercise: write a Sudoku solver.

The implementation is intentionally straightforward. It uses classic backtracking, separates validation from solving, and includes a lightweight test mode so the project is easy to read, build, and discuss in an interview setting.

## What changed

- refactored the original solution into smaller, named functions
- added board validation so obviously invalid puzzles fail fast
- improved board formatting for readable console output
- added a simple test harness and a `Makefile`
- expanded this README with build instructions and candidate guidance

## Build and run

```bash
make
./sudoku
```

Run tests:

```bash
make test
```

Clean build artifacts:

```bash
make clean
```

## How the solver works

The solver uses depth-first search with backtracking:

1. Find the next empty cell.
2. Try candidate values `1` through `9`.
3. For each candidate, check whether it is valid in the row, column, and 3x3 box.
4. If valid, place it and recursively solve the rest of the board.
5. If that path fails, reset the cell to empty and try the next candidate.
6. If there are no empty cells left, the puzzle is solved.

This is not the most optimized Sudoku solver, but it is a strong interview solution because it is:

- correct
- easy to explain
- easy to test
- easy to extend with heuristics later

## A candidate-friendly approach

If I were giving this problem to a candidate, a strong approach would be:

1. Pick a simple board representation, such as a `9x9` array where `0` means empty.
2. Write helper functions first:
   - check whether a value fits in a row
   - check whether it fits in a column
   - check whether it fits in a 3x3 box
3. Write a function to find the next empty cell.
4. Implement recursive backtracking.
5. Add a few tests:
   - solvable puzzle
   - invalid puzzle
   - already-solved or nearly-solved puzzle
6. Only optimize after the simple version works.

That path demonstrates decomposition, recursion, correctness, and communication, which is usually more important in an interview than squeezing out every last bit of runtime.

## Notes for interview discussion

Good follow-up topics include:

- how to detect invalid input early
- how to improve performance with heuristics like "choose the emptiest cell first"
- how to separate solver logic from I/O
- how to structure tests for edge cases

## Files

- `sudoku.cpp` - solver, board printer, test harness, and sample puzzle
- `Makefile` - build and test commands
