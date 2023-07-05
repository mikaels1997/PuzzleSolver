#include <iostream>
#include "Sudoku.cpp"
#include <tuple>
#include "AlgX.cpp"

// void printSudoku(SudokuMatrix sudoku) {
//     for (int i = 0; i < 3; ++i) {
//         for (int j = 0; j < 3; ++j) {
//             std::cout << sudoku.data[i][j] << " ";
//         }
//         std::cout << std::endl;
//     }
// }

int main()
{
    int arr[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},

        {8, 0, 0, 0, 6, 0, 0, 0, 0},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},

        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9},
    };

    int testCons[6][7] = {
        {1, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 0, 1},
        {0, 0, 1, 0, 1, 1, 0},
        {0, 1, 1, 0, 0, 1, 1},
        {0, 1, 0, 0, 0, 0, 1},
    };

    Sudoku sudoku (arr);
    // ConstraintMatrix test (testCons);
    // vector<tuple<int, int, int>> vec;
    // vec.push_back(make_tuple(0, 0, 0));
    auto& constMat = test.toConstraintMatrix(sudoku);
    auto sudokuMat = test.toSudokuMatrix(constMat);
    //test.printArray(sudokuMat);
}
