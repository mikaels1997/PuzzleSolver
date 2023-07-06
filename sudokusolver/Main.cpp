#include <iostream>
#include "Sudoku.cpp"
#include <tuple>
#include "AlgX.cpp"

int main()
{
    int arr[9][9] = {
        {0, 0, 0, 7, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 8, 0, 0},
        {0, 2, 0, 8, 6, 0, 0, 5, 0},

        {0, 3, 0, 0, 0, 0, 0, 0, 0},
        {6, 0, 0, 0, 0, 0, 0, 8, 4},
        {0, 1, 2, 6, 0, 7, 0, 3, 0},

        {3, 0, 0, 5, 0, 0, 0, 2, 8},
        {0, 9, 4, 0, 0, 0, 3, 0, 7},
        {0, 7, 0, 0, 0, 0, 0, 0, 0},
    };

    Sudoku sudoku (arr);
    AlgorithmX algX = AlgorithmX(sudoku.linkedList);
    algX.findExactCover(sudoku.linkedList, sudoku.CMat);
}
