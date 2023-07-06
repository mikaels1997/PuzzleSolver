//#include "Sudoku.h"
#include <vector>
#include <array>
#include <cmath>
#include <stack>
#include <numeric>
#include <set>
#include <algorithm>
#include <tuple>

using namespace std;

struct Node {
    public:
        Node* top;
        Node* right;
        Node* bottom;
        Node* left;
        int row = -1; // y coordinate
        int col = -1; // x coordinate
        int size = -1;
        Node* colHeader;

        Node() {};
        Node(int r, int c, Node* h) : row(r), col(c), colHeader(h != NULL ? h : this) {}
};

class Sudoku {
    public:
        const static int SIZE = 9;                      // Side length of the sudoku
        const static int CLS = SIZE * SIZE;             // Number of cells in the sudoku
        const static int CNS = SIZE * SIZE * 4;         // Number of constraint sets: 9*9*4

        int numMatrix[SIZE][SIZE];                      // Sudoku matrix in basic form
        vector<array<int, SIZE*SIZE*4>> fullCMat;       // Non-reduced constraint matrix (empty sudoku)
        vector<array<int, CNS>> CMat;                   // Reduced constraint matrix (initialized sudoku)
        Node* linkedList;                               // 4-way circular linked list

        Sudoku(int mat[SIZE][SIZE]) {
            for(int r = 0; r < SIZE; ++r) {
                for(int c = 0; c < SIZE; ++c) 
                    numMatrix[r][c] = mat[r][c];
            }
            fullCMat = fullConstraintMat();
            CMat = toConstraintMatrix();
            linkedList = toLinkedList(CMat);
        }

        const vector<array<int, CNS>> fullConstraintMat() {
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
                        row[80+rowCons] = 1;
                        row[161+colCons] = 1;
                        row[242+boxCons] = 1;
                        fullMatrix.push_back(row);
                    }
            return fullMatrix;
        }

        const vector<array<int, CNS>> reduceMatrix(vector<array<int, CNS>> fullMatrix, vector<tuple<int, int, int>> used) {
            set<int> reducedRowInds;
            vector<array<int, CNS>> reducedMat;
            for (tuple<int, int, int> vec : used) {
                int rowInd = CLS*get<0>(vec) + SIZE*get<1>(vec) + get<2>(vec);
                int boxInd = (3*floor(get<0>(vec)/3)+floor(get<1>(vec)/3));
                int cellCons[SIZE], rowCons[SIZE], colCons[SIZE], boxCons[SIZE];

                int boxRowStart = get<0>(vec)-get<0>(vec) % 3;
                int boxColStart = get<1>(vec)-get<1>(vec) % 3;
                int boxStartInd = 81*boxRowStart + 9*boxColStart;
                for (int i=0; i<9; i++) {
                    reducedRowInds.insert(i + rowInd-rowInd % SIZE); // Cell cons
                    reducedRowInds.insert(SIZE*i + CLS*get<0>(vec) + get<2>(vec)); // Row cons
                    reducedRowInds.insert(CLS*i + SIZE*get<1>(vec) + get<2>(vec)); // Col cons
                    reducedRowInds.insert(boxStartInd + SIZE*(i % 3) + CLS*(floor(i/3)) + get<2>(vec)); // Box cons
                    reducedRowInds.erase(rowInd);
                }
            }
            for (int i=0; i<fullMatrix.size(); i++) {
                bool contains = reducedRowInds.find(i) != reducedRowInds.end();
                if (!contains)
                    reducedMat.push_back(fullMatrix[i]);
            }
            return reducedMat;
        }

        const vector<array<int, CNS>> toConstraintMatrix() {
            vector<tuple<int, int, int>> numVecs;
            for (int r=0; r<SIZE; r++)
                for (int c=0; c<SIZE; c++) {
                    int value = numMatrix[r][c];
                    if (value == 0) continue;
                    numVecs.push_back(tuple<int, int, int>{r, c, value-1});
                }
            auto mat = reduceMatrix(fullCMat, numVecs);
            return mat;
        }

        Node* toLinkedList(vector<array<int, CNS>> consMat) {
            Node* root = new Node();
            Node* colHeaders[CNS];
            Node* latestColNodes[CNS];
            for (int c = 0; c < CNS; ++c) {
                colHeaders[c] = new Node(-1, c, nullptr);
                colHeaders[c]->size += 1;
                latestColNodes[c] = colHeaders[c];
            }
            vector<Node*> rowNodes = {};

            // Init root
            root->right = colHeaders[0];
            colHeaders[0]->left = root;
            root->left = colHeaders[CNS-1];
            colHeaders[CNS -1]->right = root;
            int size = consMat.size();

            for(int r = -1; r < size; ++r) {
                rowNodes = {};
                for(int c = 0; c < CNS; ++c) {
                    if (r == -1 && c < CNS) { // The col header nodes (not actual elements in constraint numMatrix)
                        if (c < CNS - 1)  {
                            colHeaders[c]->right = colHeaders[c+1];
                            colHeaders[c+1]->left = colHeaders[c];
                        }
                        continue;
                    };
                    if (consMat[r][c] == 0) continue;
                    Node* n = new Node(r, c, colHeaders[c]);

                    if (rowNodes.empty())
                        rowNodes.push_back(n);

                    n->left = rowNodes.back();
                    rowNodes.back()->right = n;
                    n->right = rowNodes.front();
                    rowNodes.front()->left = n;

                    n->top = latestColNodes[c];
                    latestColNodes[c]->bottom = n;

                    n->bottom = colHeaders[c];
                    colHeaders[c]->top = n;

                    latestColNodes[c] = n;
                    rowNodes.push_back(n);

                    n->colHeader->size += 1;
                }
            }
            return root;
        }
};