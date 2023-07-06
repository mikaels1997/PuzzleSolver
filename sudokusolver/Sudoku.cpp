#include "Sudoku.h"

using namespace std;

class Sudoku {
    public:
        const static int ROWS = 9;
        const static int COLS = 9;
        int numMatrix[ROWS][COLS];
        
        Sudoku(int mat[ROWS][COLS]) {
            for(int r = 0; r < ROWS; ++r) {
                for(int c = 0; c < COLS; ++c) 
                    numMatrix[r][c] = mat[r][c];
            }
        }
};