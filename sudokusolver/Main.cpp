/*-----------------Terminology----------------
    * 
    * Sudoku matrix:
    *      Representation of the sudoku in most basic form.
    *      Usually 9 * 9 matrix with values from 1 to 9
    * Constraint matrix: 
    *      A matrix whose rows represent the possibilities (initially size^3) and columns the constraint sets (size^2 * 4) of the sudoku
    *      Only contains 0s and 1s in this case
    *      For example empty 9x9 sudoku includes 9*9*9 = 729 possibilities and 9*9*4 = 324 constraint sets.
    *      There are 4 different types of constraints: 
    *           Cell (one number per cell)
    *           Row (one unique number per row), 
    *           Column (one unique number per column),
    *           Box (one unique number per box). Usually size of 3x3
    * 
    * ---------Methodology in a nutshell-------
    * 
    * Basic goal:           Solving an exact cover problem. Sudoku can be considered as one.
    * Search method:        Knuth's Algorithm X (recursive, depth-first, backtracking algorithm to solve exact cover problem)
    * Optimization:         Dancing links technique (constraint matrix as 4-way circular linked list to be used in Algorithm X)
    *                       Speeds up the search considerably.
    * Solve steps:          Sudoku matrix -> constraint matrix -> linked list -> Knuth's Algorithm X -> solved constraint matrix -> solved sudoku matrix
*/

#include <iostream>
#include "sudoku.h"
#include "algx.h"
#include "server.h"

int main()
{
    SudokuSolver::Server server;
    server.startListening();

    // int arr[9][9] = {
    //     {0, 0, 0, 7, 0, 0, 0, 0, 1},
    //     {0, 0, 0, 0, 0, 0, 8, 0, 0},
    //     {0, 2, 0, 8, 6, 0, 0, 5, 0},

    //     {0, 3, 0, 0, 0, 0, 0, 0, 0},
    //     {6, 0, 0, 0, 0, 0, 0, 8, 4},
    //     {0, 1, 2, 6, 0, 7, 0, 3, 0},

    //     {3, 0, 0, 5, 0, 0, 0, 2, 8},
    //     {0, 9, 4, 0, 0, 0, 3, 0, 7},
    //     {0, 7, 0, 0, 0, 0, 0, 0, 0},
    // };
    // SudokuSolver::Sudoku sudoku(arr);
    // SudokuSolver::AlgorithmX algx(sudoku.CMat);
    // algx.findExactCover(algx.root);
    // auto sol = sudoku.toSudokuMatrix(algx.solutionMat);
    // sudoku.printMatrix(sol);
}
