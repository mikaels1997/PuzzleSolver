#ifdef SUDOKU_H
#define SUDOKU_H

struct Node {
    public:
        Node* top;
        Node* right;
        Node* bottom;
        Node* left;
        int row; // y coordinate
        int col; // x coordinate
        int size;
        Node* colHeader;

        Node() {};
        Node(int r, int c, Node* h) : row(r), col(c), colHeader(h != NULL ? h : this);
};

class Sudoku {
    public:
        extern const static int SIZE = 9;                                  // Side length of the sudoku
        extern const static int CLS = SIZE * SIZE;                         // Number of cells in the sudoku
        extern const static int CNS = SIZE * SIZE * 4;                     // Number of constraint sets: 9*9*4

        int numMatrix[SIZE][SIZE];                                  // Sudoku matrix in basic form
        vector<array<int, SIZE*SIZE*4>> fullCMat;      // Non-reduced constraint matrix (empty sudoku)
        vector<array<int, CNS>> CMat;                               // Reduced constraint matrix (initialized sudoku)

        Sudoku(int mat[SIZE][SIZE]);

        vector<array<int, CNS>> fullConstraintMat();

        const vector<array<int, CNS>> reduceMatrix(vector<array<int, CNS>> fullMatrix, vector<tuple<int, int, int>> used);

        const vector<array<int, CNS>> toConstraintMatrix();

        vector<vector<int>> toSudokuMatrix(vector<array<int, CNS>> consMat);
        void printMatrix(vector<vector<int>> mat);
};

#endif