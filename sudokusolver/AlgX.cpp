#include "AlgX.h"
#include "Sudoku.h"
#include <vector>
#include <array>
#include <cmath>
#include <stack>
#include <numeric>
#include <set>

struct Node {
    public:
        Node* top;
        Node* right;
        Node* bottom;
        Node* left;
        int row = -1; // y coordinate
        int col = -1; // x coordinate
        int size = -1;
        string name;
        Node* colHeader;

        Node() {};
        Node(int r, int c, Node* h) : row(r), col(c), colHeader(h != NULL ? h : this) {}
};

class AlgorithmX {
    private:
        Node* colHeader;
        Node* root;
    public:
        Node solution[20];
        AlgorithmX(Node* r) {
            root = r;
            colHeader = r;
        };

        void search(int k) {
            if (root->right == root) {
                int lol = 3;
                return;
            };
            colHeader = chooseColumn(root);
            coverColumn(colHeader);

            Node *r = colHeader->bottom;
            while (r != colHeader) {
                solution[k] = *r;
                Node* j = r->right;
                while(j != r) {
                    coverColumn(j->colHeader);
                    j = j->right;
                }
                search(k + 1);
                r = &solution[k];
                colHeader = r->colHeader;
                j = r->left;
                while (j->col != r->col) {
                    uncoverColumn(j->colHeader);
                    j = j->left;
                }
                r = r->bottom;
            }
            uncoverColumn(colHeader);
            return;
        }

        void coverColumn(Node* c) {
            c->right->left = c->left;
            c->left->right = c->right;
            Node* i = c->bottom;
            while (i != c) {
                Node *j = i->right;
                while (j != i) {
                    j->bottom->top = j->top;
                    j->top->bottom = j->bottom;
                    j->colHeader->size -= 1;
                    j = j->right;
                }
                i = i->bottom;
            }
        }

        void uncoverColumn(Node* c) {
            Node *i = c->top;
            while (i != c) {
                Node *j = i->left;
                while(j != i) {
                    j->colHeader->size += 1;
                    j->bottom->top = j;
                    j->top->bottom = j;
                    j = j->left;
                }
                i = i->top;
            }
            c->right->left = c;
            c->left->right = c;
        }

        Node* chooseColumn(Node* root) {
            Node* temp = root->right;
            int minSize = 999;
            Node* chosenCol;
            while(temp != root) {
                if (temp->size < minSize && temp->size >= 0) {
                    chosenCol = temp;
                    minSize = temp->size;
                }
                temp = temp->right;
            }
            return chosenCol;
        }
};

class ConstraintMatrix {
    private:
        int N = 1;
        const static int ROWS = 6;
        const static int COLS = 7;
        vector<tuple<int, int, int>> initialNumVecs;

    public:
        int matrix[ROWS][COLS];
        ConstraintMatrix(Sudoku sudoku) {
            for(int r = 0; r < Sudoku::ROWS; ++r) {
                for(int c = 0; c < Sudoku::COLS; ++c) 
                    std::cout << "Hello World" << std::endl;
            }
        }
        ConstraintMatrix(int mat[ROWS][COLS]) {
            for(int r = 0; r < ROWS; ++r) {
                for(int c = 0; c < COLS; ++c) 
                    matrix[r][c] = mat[r][c];
            }
        }

        const vector<array<int, 324>> fullConstraintMat() {
            vector<array<int, 324>> fullMatrix;

            for (int r = 0; r < 9; ++r)
                for (int c = 0; c < 9; ++c)
                    for (int v = 1; v < 10; ++v) {
                        array<int, 324> row {0};
                        int i = 81 *r + 9*c + v - 1;

                        int cellCons = 9*r + c;
                        int rowCons = 9*r + v;
                        int colCons = 9*c + v;
                        int boxCons = 9*((3*floor(r/3) + 1) + floor(c/3) - 1) + v;

                        row[cellCons] = 1;
                        row[80+rowCons] = 1;
                        row[161+colCons] = 1;
                        row[242+boxCons] = 1;
                        fullMatrix.push_back(row);

                        // char buffer[100];
                        // sprintf(buffer, "%d, %d, %d, %d", cellCons, rowCons, colCons, boxCons);
                        // cout << buffer << endl;
                    }
            return fullMatrix;
        }

        const vector<array<int, 324>> reduceMatrix(vector<array<int, 324>> fullMatrix, vector<tuple<int, int, int>> used) {
            set<int> reducedRowInds;
            vector<array<int, 324>> reducedMat;
            initialNumVecs = used;
            for (auto& vec : initialNumVecs) {
                int colInd = 81*get<0>(vec) + 9*get<1>(vec) + get<2>(vec);
                int boxInd = (3*floor(get<0>(vec)/3)+floor(get<1>(vec)/3));
                int cellCons[9], rowCons[9], colCons[9], boxCons[9];

                int boxRowStart = get<0>(vec)-get<0>(vec) % 3;
                int boxColStart = get<1>(vec)-get<1>(vec) % 3;
                int boxStartInd = 81*boxRowStart + 9*boxColStart;
                for (int i=0; i<9; i++) {
                    reducedRowInds.insert(i + colInd-colInd % 9); // Cell cons
                    reducedRowInds.insert(9*i + 81*get<0>(vec) + get<2>(vec)); // Row cons
                    reducedRowInds.insert(81*i + 9*get<1>(vec) + get<2>(vec)); // Col cons
                    reducedRowInds.insert(boxStartInd + 9*(i % 3) + 81*(floor(i/3)) + get<2>(vec)); // Box cons
                }
            }
            for (int i=0; i<fullMatrix.size(); i++) {
                bool contains = reducedRowInds.find(i) != reducedRowInds.end();
                if (!contains)
                    reducedMat.push_back(fullMatrix[i]);
            }
            return reducedMat;
        }

        const vector<array<int, 324>> toConstraintMatrix(Sudoku sudoku) {
            vector<tuple<int, int, int>> numVecs;
            for (int r=0; r<sudoku.ROWS; r++)
                for (int c=0; c<sudoku.COLS; c++) {
                    int value = sudoku.matrix[r][c];
                    if (value == 0) continue;
                    numVecs.push_back(tuple<int, int, int>{r, c, value-1});
                }
            auto& full = fullConstraintMat();
            auto& mat = reduceMatrix(full, numVecs);
            return mat;
        }

        vector<vector<int>> toSudokuMatrix(vector<array<int, 324>> consMat) {
            vector<vector<int>> sudokuMat(9, vector<int>(9, 0));
            for (auto& vec : consMat) {
                int numVec[3];
                for (int i=0; i<vec.size(); i++) {
                    if (vec[i] == 1 && i < 81) {
                        numVec[0] = floor(i/9);
                        numVec[1] = i % 9;
                    }
                    else if (vec[i] == 1) {
                        numVec[2] = i % 9; 
                        sudokuMat[numVec[0]][numVec[1]] = numVec[2] + 1;
                        break;
                    }
                }
            }
            return sudokuMat;
        }

        Node* toLinkedList() {
            vector<vector<int>> test = {
                {1, 0, 0, 1, 0, 0, 1},
                {1, 0, 0, 1, 0, 0, 0},
                {0, 0, 0, 1, 1, 0, 1},
                {0, 0, 1, 0, 1, 1, 0},
                {0, 1, 1, 0, 0, 1, 1},
                {0, 1, 0, 0, 0, 0, 1},
            };

            // int test[ROWS][COLS] = {
            //     {0, 0, 1, 0, 1, 1, 0},
            //     {1, 0, 0, 1, 0, 0, 1},
            //     {0, 1, 1, 0, 0, 1, 0},
            //     {1, 0, 0, 1, 0, 0, 0},
            //     {0, 1, 0, 0, 0, 0, 1},
            //     {0, 0, 0, 1, 1, 0, 1},
            // };

            Node* root = new Node();
            Node* colHeaders[COLS];
            Node* latestColNodes[COLS];
            for (int c = 0; c < COLS; ++c) {
                colHeaders[c] = new Node(-1, c, nullptr);
                colHeaders[c]->size += 1;
                latestColNodes[c] = colHeaders[c];
            }
            std::vector<Node*> rowNodes = {};

            // Init root
            root->right = colHeaders[0];
            colHeaders[0]->left = root;
            root->left = colHeaders[COLS-1];
            colHeaders[COLS -1]->right = root;

            for(int r = -1; r < ROWS; ++r) {
                rowNodes = {};
                for(int c = 0; c < COLS; ++c) {
                    if (r == -1 && c < COLS) { // The col header nodes (not actual elements in constraint matrix)
                        if (c < COLS - 1)  {
                            colHeaders[c]->right = colHeaders[c+1];
                            colHeaders[c+1]->left = colHeaders[c];
                        }
                        continue;
                    };
                    if (test[r][c] == 0) continue;
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

        vector<array<int, COLS>> findExactCover() {
            Node* root = toLinkedList();
            AlgorithmX alg = AlgorithmX(root);
            alg.search(0);
            vector<array<int, COLS>> subMatrix;
            for (int r = 0; r < 20; ++r) {
                if (alg.solution[r].row == -1) break;
                std::array<int,COLS> tempRow {0};
                for (int c = 0; c < COLS; ++c){
                    tempRow[c] = matrix[alg.solution[r].row][c];
                }
                subMatrix.push_back(tempRow);
            }
            printMatrix(subMatrix);
            return subMatrix;
        }

        void printMatrix(vector<array<int, COLS>> mat) {
            for (const auto& arr : mat) {
                for (const auto& element : arr) {
                    std::cout << element << " ";
                }
                std::cout << std::endl;
            }
        }
        void printArray(int** arr)
        {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    cout << arr[i][j]<<" ";
                }
                cout << endl;
            }
        }

};
