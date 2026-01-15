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
*/-
#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "sudoku.h"
#include "algx.h"
#include <string>

extern "C" {
    __declspec(dllexport)
    const char* hello(const char* name) {
        static std::string s;
        s = "Hello ";
        s += name;
        return s.c_str();
    }

    /// @brief
    /// @param input Input in the form of [1, 3, 4, 5, ... x81]
    /// @return
    __declspec(dllexport)
    const int handleRequest(const char* input, char* output, int output_size) {
        std::string request(input);
        char chars[] = "[]";
        for (char c : chars)
            request.erase(std::remove(request.begin(), request.end(), c), request.end());

        std::istringstream ss(request);
        std::string item;
        int sudokuArr[9][9];
        int count = 0;
        while (std::getline(ss, item, ',')) {
            int value = std::stoi(item != "null" ? item : "0");
            sudokuArr[count/9][count%9] = value;
            count++;
        }

        SudokuSolver::Sudoku sudoku(sudokuArr);
        SudokuSolver::AlgorithmX algx(sudoku.CMat);
        algx.findExactCover(algx.root);
        auto sol = sudoku.toSudokuMatrix(algx.solutionMat);
        std::string flattened = sudoku.solutionAsString(sol);
        if ((int)flattened.size() + 1 > output_size)
            return -1; // buffer too small

        std::memcpy(output, flattened.c_str(), flattened.size() + 1);
        return 0;
    }
}