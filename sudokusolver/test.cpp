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

    // int arr[9][9] = {
    //     {5, 3, 4, 6, 7, 8, 9, 1, 2},
    //     {6, 7, 2, 1, 9, 5, 3, 4, 8},
    //     {1, 9, 8, 3, 4, 2, 5, 6, 7},

    //     {8, 5, 9, 7, 6, 1, 4, 2, 3},
    //     {4, 2, 6, 8, 5, 3, 7, 9, 1},
    //     {7, 1, 3, 9, 2, 4, 8, 5, 6},

    //     {9, 6, 1, 5, 3, 7, 2, 8, 4},
    //     {2, 8, 7, 4, 1, 9, 6, 3, 5},
    //     {3, 4, 5, 2, 8, 6, 1, 0, 0},
    // };

    // vector<array<int, 7>> testConsMat = {
    //     {1, 0, 0, 1, 0, 0, 1},
    //     {1, 0, 0, 1, 0, 0, 0},
    //     {0, 0, 0, 1, 1, 0, 1},
    //     {0, 0, 1, 0, 1, 1, 0},
    //     {0, 1, 1, 0, 0, 1, 1},
    //     {0, 1, 0, 0, 0, 0, 1},
    // };

    // int test[6][7] = {
    //     {0, 0, 1, 0, 1, 1, 0},
    //     {1, 0, 0, 1, 0, 0, 1},
    //     {0, 1, 1, 0, 0, 1, 0},
    //     {1, 0, 0, 1, 0, 0, 0},
    //     {0, 1, 0, 0, 0, 0, 1},
    //     {0, 0, 0, 1, 1, 0, 1},
    // };

    Sudoku sudoku (arr);
    ConstraintMatrix test (sudoku);
    // vector<tuple<int, int, int>> vec;
    // vec.push_back(make_tuple(0, 0, 0));
    auto& constMat = test.toConstraintMatrix(sudoku);
    auto linkedList = test.toLinkedList(constMat);
    auto solution = test.findExactCover(linkedList, constMat);
    auto solvedSudoku = test.toSudokuMatrix(solution);
    test.printMatrix(solvedSudoku);
    //test.printArray(sudokuMat);
}
