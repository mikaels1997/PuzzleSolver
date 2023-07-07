#ifndef SUDOKU_H
#define SUDOKU_H
#include <iostream>
#include <vector>
#include <array>
#include <tuple>


class Sudoku {
    public:
        const static int SIZE = 9;                                  // Side length of the sudoku
        const static int CLS = SIZE * SIZE;                         // Number of cells in the sudoku
        const static int CNS = SIZE * SIZE * 4;                     // Number of constraint sets: 9*9*4

        Sudoku(int mat[SIZE][SIZE]);
        int numMatrix[SIZE][SIZE];                                  // Sudoku matrix in basic form
        std::vector<std::array<int, SIZE*SIZE*4>> fullCMat;                   // Non-reduced constraint matrix (empty sudoku)
        std::vector<std::array<int, CNS>> CMat;                            // Reduced constraint matrix (initialized sudoku)

        std::vector<std::array<int, CNS>> fullConstraintMat();

        const std::vector<std::array<int, CNS>> reduceMatrix(
            std::vector<std::array<int, CNS>> fullMatrix, std::vector<std::tuple<int, int, int>> used);

        const std::vector<std::array<int, CNS>> toConstraintMatrix();

        std::vector<std::vector<int>> toSudokuMatrix(std::vector<std::array<int, CNS>> consMat);
        void printMatrix(std::vector<std::vector<int>> mat);
};

#endif