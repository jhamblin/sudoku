#include <iostream>

bool ValidForRow(int board[][9], int row, int candidate)
{
    for (size_t col = 0; col < 9; ++col)
    {
        if (board[row][col] == candidate)
        {
            return false;
        }
    }
    return true;
}

bool ValidForCol(int board[][9], int col, int candidate)
{
    for (size_t row = 0; row < 9; ++row)
    {
        if (board[row][col] == candidate)
        {
            return false;
        }
    }
    return true;
}

bool ValidForHouse(int board[][9], int row, int col, int candidate)
{
    int firstRow = 3 * (row / 3);
    int firstCol = 3 * (col / 3);

    for (size_t row = firstRow; row < firstRow + 3; ++row)
    {
        for (size_t col = firstCol; col < firstCol + 3; ++col)
        {
            if (board[row][col] == candidate)
            {
                return false;
            }
        }
    }
    return true;
}

void PrintBoard(int board[][9])
{    
    std::cout << "___________________\n";
    for (size_t i = 0; i < 9; ++i)
    {
        std::cout << '|';
        for (size_t j = 0; j < 9; ++j)
        {
            if (board[i][j] == 0)
            {
                std::cout << '_';
            }
            else
            {
                std::cout << board[i][j];
            }
            std::cout << '|';
        }
        std::cout << '\n';
    }
}

int Remaining(int board[][9])
{
    int count = 0;
    for (size_t row = 0; row < 9; ++row) 
    {
        for (size_t col = 0; col < 9; ++col) 
        {
            if (board[row][col] == 0) 
            {
                ++count;        
            }
        }
    }
    return count;
}

bool IsSolved(int board[][9])
{
    return Remaining(board) == 0;
}

bool Solve(int board[][9], int row, int col)
{
    if (IsSolved(board)) 
    {
        return true;
    }

    int nextRow = row + ((col + 1) / 9); 
    int nextCol = (col + 1) % 9;

    if (board[row][col] != 0) 
    {
        return Solve(board, nextRow, nextCol);
    }

    for (int candidate = 1; candidate <= 9; ++candidate) 
    {
        if (ValidForRow(board, row, candidate) && 
            ValidForCol(board, col, candidate) && 
            ValidForHouse(board, row, col, candidate)) 
        {
            board[row][col] = candidate;

            if (Solve(board, nextRow, nextCol)) 
            {
                return true;
            }

            board[row][col] = 0; 
        }
    }
    return false;
}

int main()
{
    int hard[9][9] = {{0,0,0,9,0,0,0,0,0},
                      {6,0,3,0,1,2,5,0,0},
                      {9,0,0,0,0,0,0,0,3},
                      {0,0,6,2,0,0,0,5,1},
                      {0,0,1,0,0,0,7,0,0},
                      {2,7,0,0,0,6,8,0,0},
                      {4,0,0,0,0,0,0,0,8},
                      {0,0,5,6,2,0,1,0,7},
                      {0,0,0,0,0,9,0,0,0}};

    int easy[9][9] = {{6,0,0,9,5,0,8,0,0},
                      {0,0,5,1,0,3,0,0,0},
                      {0,1,0,0,6,0,0,0,0},
                      {1,7,0,3,0,0,0,6,2},
                      {3,0,4,0,0,0,7,0,8},
                      {2,5,0,0,0,4,0,3,9},
                      {0,0,0,0,3,0,0,8,0},
                      {0,0,0,2,0,1,3,0,0},
                      {0,0,9,0,8,6,0,0,1}};

    PrintBoard(hard);
    if (Solve(hard, 0, 0))
    {
        PrintBoard(hard); 
    }
}
