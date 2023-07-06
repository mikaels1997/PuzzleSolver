#include "AlgX.h"
#include "Sudoku.h"
#include <vector>
#include <array>
#include <cmath>
#include <stack>
#include <numeric>
#include <set>
#include <algorithm>

class AlgorithmX {
    private:
        Node* colHeader;
        Node* root;
        Node* solution[81];
    public:
        vector<array<int, 324>> solutionMat;

        AlgorithmX(Node* r, int size) {
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
};
