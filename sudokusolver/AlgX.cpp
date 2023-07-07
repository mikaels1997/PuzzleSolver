#include "AlgX.h"
#include "sudoku.h"
#include <vector>
#include <array>
#include <cmath>
#include <stack>
#include <numeric>
#include <set>
#include <algorithm>

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

class AlgorithmX {
    private:
        Node* colHeader;
        Node* solution[Sudoku::CLS];
    public:
        vector<array<int, Sudoku::CNS>> solutionMat;
        Node* root;

        AlgorithmX(vector<array<int, Sudoku::CNS>> cMat) {
            root = toLinkedList(cMat);
            colHeader = root;
        };

        void findExactCover(Node* root, vector<array<int, Sudoku::CNS>> unsolved) {
            root = root;
            colHeader = root;
            search(0, unsolved);
        }

        void search(int k, vector<array<int, Sudoku::CNS>> unsolved) {
            if (root->right == root) {
                vector<array<int, Sudoku::CNS>> subMatrix;
                for (int r = 0; r < Sudoku::CLS; ++r) {
                    std::array<int,Sudoku::CNS> tempRow {0};
                    for (int c = 0; c < Sudoku::CNS; ++c)
                        tempRow[c] = unsolved[solution[r]->row][c];
                    subMatrix.push_back(tempRow);
                }
                solutionMat = subMatrix;
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

        Node* toLinkedList(vector<array<int, Sudoku::CNS>> consMat) {
            Node* root = new Node();
            Node* colHeaders[Sudoku::CNS];
            Node* latestColNodes[Sudoku::CNS];
            for (int c = 0; c < Sudoku::CNS; ++c) {
                colHeaders[c] = new Node(-1, c, nullptr);
                colHeaders[c]->size += 1;
                latestColNodes[c] = colHeaders[c];
            }
            vector<Node*> rowNodes = {};

            // Init root
            root->right = colHeaders[0];
            colHeaders[0]->left = root;
            root->left = colHeaders[Sudoku::CNS-1];
            colHeaders[Sudoku::CNS -1]->right = root;
            int size = consMat.size();

            for(int r = -1; r < size; ++r) {
                rowNodes = {};
                for(int c = 0; c < Sudoku::CNS; ++c) {
                    if (r == -1 && c < Sudoku::CNS) { // The col header nodes (not actual elements in constraint numMatrix)
                        if (c < Sudoku::CNS - 1)  {
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
