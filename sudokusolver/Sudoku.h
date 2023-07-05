#ifdef SUDOKU_H
#define SUDOKU_H

class Sudoku {
    private:
        const static int ROWS;
        const static int COLS;
    public:
        int data[ROWS][COLS];
        Sudoku(int mat[ROWS][COLS]);
};

#endif