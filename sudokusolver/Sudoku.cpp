#include "sudoku.h"
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <set>
#include <tuple>

using namespace std;

Sudoku::Sudoku(int mat[SIZE][SIZE]) {
    for(int r = 0; r < SIZE; ++r) {
        for(int c = 0; c < SIZE; ++c) 
            unsolvedSudokuMat[r][c] = mat[r][c];
    }
    fullCMat = fullConstraintMat();
    CMat = toConstraintMatrix();
}

vector<array<int, Sudoku::CNS>> Sudoku::fullConstraintMat() {
    vector<array<int, CNS>> fullMatrix;

    for (int r = 0; r < SIZE; ++r)
        for (int c = 0; c < SIZE; ++c)
            for (int v = 1; v <= SIZE; ++v) {
                array<int, CNS> row {0};
                int i = CLS *r + SIZE*c + v - 1;

                int cellCons = SIZE*r + c;
                int rowCons = SIZE*r + v;
                int colCons = SIZE*c + v;
                int boxCons = SIZE*((3*floor(r/3) + 1) + floor(c/3) - 1) + v;

                row[cellCons] = 1;
                row[CLS-1+rowCons] = 1;
                row[2*CLS-1+colCons] = 1;
                row[3*CLS-1+boxCons] = 1;
                fullMatrix.push_back(row);
            }
    return fullMatrix;
}

const vector<array<int, Sudoku::CNS>> Sudoku::reduceMatrix(vector<array<int, Sudoku::CNS>> fullMatrix, vector<tuple<int, int, int>> occupied) {
    set<int> reducedRowInds;                                                // Row indexes to exclude in constraint matrix
    vector<array<int, CNS>> reducedMat;                                     // Reduced constraint matrix
    for (tuple<int, int, int> vec : occupied) {
        int rowInd = CLS*get<0>(vec) + SIZE*get<1>(vec) + get<2>(vec);      // Row index of the 
        int boxInd = (3*floor(get<0>(vec)/3)+floor(get<1>(vec)/3));
        int cellCons[SIZE], rowCons[SIZE], colCons[SIZE], boxCons[SIZE];

        int boxRowStart = get<0>(vec)-get<0>(vec) % 3;      // Row index of a box
        int boxColStart = get<1>(vec)-get<1>(vec) % 3;      // Col index of a box
        int boxStartInd = 81*boxRowStart + 9*boxColStart;   // First row index of that box within full constraint matrix
        for (int i=0; i<9; i++) {
            reducedRowInds.insert(i + rowInd-rowInd % SIZE);                                    // Cell constraints
            reducedRowInds.insert(SIZE*i + CLS*get<0>(vec) + get<2>(vec));                      // Row constraints
            reducedRowInds.insert(CLS*i + SIZE*get<1>(vec) + get<2>(vec));                      // Col constraints
            reducedRowInds.insert(boxStartInd + SIZE*(i % 3) + CLS*(floor(i/3)) + get<2>(vec)); // Box constraints
            reducedRowInds.erase(rowInd);                                                       // Not including the occupied 
        }
    }
    for (int i=0; i<fullMatrix.size(); i++) {
        bool contains = reducedRowInds.find(i) != reducedRowInds.end();
        if (!contains)
            reducedMat.push_back(fullMatrix[i]);
    }
    return reducedMat;
}

const vector<array<int, Sudoku::CNS>> Sudoku::toConstraintMatrix() {
    vector<tuple<int, int, int>> numVecs;
    for (int r=0; r<SIZE; r++)
        for (int c=0; c<SIZE; c++) {
            int value = unsolvedSudokuMat[r][c];
            if (value == 0) continue;
            numVecs.push_back(tuple<int, int, int>{r, c, value-1});
        }
    auto mat = reduceMatrix(fullCMat, numVecs);
    return mat;
}

vector<vector<int>> Sudoku::toSudokuMatrix(vector<array<int, Sudoku::CNS>> consMat) {
    vector<vector<int>> sudokuMat(SIZE, vector<int>(SIZE, 0));
    for (auto vec : consMat) {
        int numVec[3];
        for (int i=0; i<vec.size(); i++) {
            if (vec[i] == 1 && i < CLS) {
                numVec[0] = floor(i/SIZE);
                numVec[1] = i % SIZE;
            }
            else if (vec[i] == 1) {
                numVec[2] = i % SIZE; 
                sudokuMat[numVec[0]][numVec[1]] = numVec[2] + 1;
                break;
            }
        }
    }
    return sudokuMat;
}

void Sudoku::printMatrix(vector<vector<int>> mat) {
    for (const auto arr : mat) {
        for (const auto element : arr) {
            cout << element << " ";
        }
        cout << endl;
    }
}
