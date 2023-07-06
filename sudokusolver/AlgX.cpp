#include "AlgX.h"
#include "Sudoku.h"
#include <vector>
#include <array>
#include <cmath>
#include <stack>
#include <numeric>
#include <set>
#include <algorithm>

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

class AlgorithmX {
    private:
        Node* colHeader;
        Node* root;
    public:
        Node* solution[81];
        AlgorithmX(Node* r) {
            root = r;
            colHeader = r;
        };

        void findExactCover(Node* root, vector<array<int, 324>> unsolved) {
            root = root;
            colHeader = root;
            search(0, unsolved);
        }

        void search(int k, vector<array<int, 324>> unsolved) {
            if (root->right == root) {
                vector<array<int, 324>> subMatrix;
                for (int r = 0; r < 81; ++r) {
                    std::array<int,324> tempRow {0};
                    for (int c = 0; c < 324; ++c)
                        tempRow[c] = unsolved[solution[r]->row][c];
                    subMatrix.push_back(tempRow);
                }
                auto solvedSudoku = toSudokuMatrix(subMatrix);
                printMatrix(solvedSudoku);
                return;
            };
            colHeader = chooseColumn(root);

            coverColumn(colHeader);

            for (Node* temp = colHeader->bottom; temp != colHeader; temp = temp->bottom) {
                solution[k] = temp;
                for (Node* node = temp->right; node != temp; node = node->right) {
                    coverColumn(node->colHeader);
                }

                search(k + 1, unsolved);

                temp = solution[k];
                colHeader = temp->colHeader;
                for (Node* node = temp->left; node != temp; node = node->left) {
                    uncoverColumn(node->colHeader);
                }
            }
            uncoverColumn(colHeader);
        }

        void coverColumn(Node* c) {
            c->right->left = c->left;
            c->left->right = c->right;
            for (Node* rowNode = c->bottom; rowNode != c; rowNode = rowNode->bottom) {
                for (Node* colNode = rowNode->right; colNode != rowNode; colNode = colNode->right) {
                    colNode->bottom->top = colNode->top;
                    colNode->top->bottom = colNode->bottom;
                    colNode->colHeader->size--;
                }
            }
        }

        void uncoverColumn(Node* c) {
            for (Node* rowNode = c->top; rowNode != c; rowNode = rowNode->top) {
                for (Node* colNode = rowNode->left; colNode != rowNode; colNode = colNode->left) {
                    colNode->colHeader->size++;
                    colNode->bottom->top = colNode;
                    colNode->top->bottom = colNode;
                }
            }
            c->right->left = c;
            c->left->right = c;
        }

        Node* chooseColumn(Node* root) {
            Node* chosenCol = root->right;
            for (Node* t = chosenCol->right; t != root; t = t->right)
                if (t->size < chosenCol->size)
                    chosenCol = t;
            return chosenCol;
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
        
        void printMatrix(vector<vector<int>> mat) {
            for (const auto& arr : mat) {
                for (const auto& element : arr) {
                    std::cout << element << " ";
                }
                std::cout << std::endl;
            }
        }
};

class ConstraintMatrix {
    private:
        int N = 1;
        const static int ROWS = 729;//729;
        const static int COLS = 324;//324;
        vector<tuple<int, int, int>> initialNumVecs;

    public:
        int matrix[ROWS][COLS];
        ConstraintMatrix(Sudoku sudoku) {
            for(int r = 0; r < Sudoku::ROWS; ++r) {
                for(int c = 0; c < Sudoku::COLS; ++c) {}
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
                    }
            return fullMatrix;
        }

        const vector<array<int, 324>> reduceMatrix(vector<array<int, 324>> fullMatrix, vector<tuple<int, int, int>> used) {
            set<int> reducedRowInds;
            vector<array<int, 324>> reducedMat;
            initialNumVecs = used;
            for (auto& vec : initialNumVecs) {
                int rowInd = 81*get<0>(vec) + 9*get<1>(vec) + get<2>(vec);
                int boxInd = (3*floor(get<0>(vec)/3)+floor(get<1>(vec)/3));
                int cellCons[9], rowCons[9], colCons[9], boxCons[9];

                int boxRowStart = get<0>(vec)-get<0>(vec) % 3;
                int boxColStart = get<1>(vec)-get<1>(vec) % 3;
                int boxStartInd = 81*boxRowStart + 9*boxColStart;
                for (int i=0; i<9; i++) {
                    reducedRowInds.insert(i + rowInd-rowInd % 9); // Cell cons
                    reducedRowInds.insert(9*i + 81*get<0>(vec) + get<2>(vec)); // Row cons
                    reducedRowInds.insert(81*i + 9*get<1>(vec) + get<2>(vec)); // Col cons
                    reducedRowInds.insert(boxStartInd + 9*(i % 3) + 81*(floor(i/3)) + get<2>(vec)); // Box cons
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

        Node* toLinkedList(vector<array<int, 324>> consMat) {
            int consSetNum = 9 * 9 * 4;
           // int possibiliesNum = 9 * 9 * 9;

            Node* root = new Node();
            Node* colHeaders[consSetNum];
            Node* latestColNodes[consSetNum];
            for (int c = 0; c < consSetNum; ++c) {
                colHeaders[c] = new Node(-1, c, nullptr);
                colHeaders[c]->size += 1;
                latestColNodes[c] = colHeaders[c];
            }
            vector<Node*> rowNodes = {};

            // Init root
            root->right = colHeaders[0];
            colHeaders[0]->left = root;
            root->left = colHeaders[consSetNum-1];
            colHeaders[consSetNum -1]->right = root;
            int size = consMat.size();

            for(int r = -1; r < size; ++r) {
                rowNodes = {};
                for(int c = 0; c < consSetNum; ++c) {
                    if (r == -1 && c < consSetNum) { // The col header nodes (not actual elements in constraint matrix)
                        if (c < consSetNum - 1)  {
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
