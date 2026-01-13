#ifndef SUDOKU_H
#define SUDOKU_H
#include <iostream>
#include <vector>
#include <array>
#include <tuple>

namespace SudokuSolver {
    class Sudoku {
        public:
            const static int SIZE = 9;                                  // Side length of the sudoku
            const static int CLS = SIZE * SIZE;                         // Number of cells in the sudoku
            const static int CNS = SIZE * SIZE * 4;                     // Number of constraint sets: 9*9*4

            Sudoku(int mat[SIZE][SIZE]);
            int unsolvedSudokuMat[SIZE][SIZE];                          // Unsolved sudoku matrix
            std::vector<std::array<int, SIZE*SIZE*4>> fullCMat;         // Non-reduced constraint matrix (empty sudoku)
            std::vector<std::array<int, CNS>> CMat;                     // Reduced constraint matrix (initialized sudoku)

            /// @brief Full constraint matrix of a sudoku (empty sudoku)
            std::vector<std::array<int, CNS>> fullConstraintMat();

            /// @brief Reduces constraint matrix to match initialized sudoku
            /// @param fullMatrix Full constraint matrix
            /// @param occupied Number vectors of initially occupied cells (row, col, value-1)
            /// @return Reduced constraint matrix
            const std::vector<std::array<int, CNS>> reduceMatrix(
                std::vector<std::array<int, CNS>> fullMatrix, std::vector<std::tuple<int, int, int>> occupied);

            /// @brief Converts sudoku matrix to a constraint matrix (for exact cover problem)
            const std::vector<std::array<int, CNS>> toConstraintMatrix();

            /// @brief Converts solved constraint matrix to sudoku matrix
            std::vector<std::vector<int>> toSudokuMatrix(std::vector<std::array<int, CNS>> consMat);

            /// @brief Flattened version of the sudoku matrix
            std::string solutionAsString(std::vector<std::vector<int>> mat);

            /// @brief Prints sudoku solution
            void printMatrix(std::vector<std::vector<int>> mat);
    };
}

#endif