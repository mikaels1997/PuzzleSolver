#include "sudoku.h"
#include "algx.h"
#include <vector>
#include <array>

using namespace std;

Node::Node(int r, int c, Node* h) : row(r), col(c), colHeader(h != NULL ? h : this) {}

AlgorithmX::AlgorithmX(vector<array<int, Sudoku::CNS>> cMat) {
    unsolved = cMat;
    root = toLinkedList(cMat);
};

void AlgorithmX::findExactCover(Node* root) {
    root = root;
    colHeader = root;
    search(0);
}

void AlgorithmX::search(int k) {
    if (root->right == root) {
        // Solution found !
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
        search(k + 1);
        temp = solution[k];
        colHeader = temp->colHeader;
        for (Node* node = temp->left; node != temp; node = node->left) {
            uncoverColumn(node->colHeader);
        }
    }
    uncoverColumn(colHeader);
}

void AlgorithmX::coverColumn(Node* c) {
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

void AlgorithmX::uncoverColumn(Node* c) {
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

Node* AlgorithmX::chooseColumn(Node* root) {
    Node* chosenCol = root->right;
    for (Node* t = chosenCol->right; t != root; t = t->right)
        if (t->size < chosenCol->size)
            chosenCol = t;
    return chosenCol;
}

Node* AlgorithmX::toLinkedList(vector<array<int, Sudoku::CNS>> consMat) {

    Node* colHeaders[Sudoku::CNS];      // The column header nodes (not actual elements in constraint matrix)
    Node* latestColNodes[Sudoku::CNS];  // Keeps track of the "bottom" of linked list
    for (int c = 0; c < Sudoku::CNS; ++c) {
        colHeaders[c] = new Node(-1, c, nullptr);   // Adding column header nodes
        colHeaders[c]->size += 1;
        latestColNodes[c] = colHeaders[c];
    }
    vector<Node*> rowNodes;

    // Init root node with connections (the top-left node)
    Node* root = new Node();
    root->right = colHeaders[0];
    colHeaders[0]->left = root;
    root->left = colHeaders[Sudoku::CNS-1];
    colHeaders[Sudoku::CNS -1]->right = root;

    // Iterating through every element of the constraint matrix
    int size = consMat.size();
    for(int r = -1; r < size; ++r) {
        rowNodes = {};  // Contains nodes of current row
        for(int c = 0; c < Sudoku::CNS; ++c) {
            if (r == -1 && c < Sudoku::CNS) {
                if (c < Sudoku::CNS - 1)  { // Col header node connections
                    colHeaders[c]->right = colHeaders[c+1];
                    colHeaders[c+1]->left = colHeaders[c];
                }
                continue;
            };
            if (consMat[r][c] == 0) continue;   // Not including 0s in the linked list

            Node* n = new Node(r, c, colHeaders[c]);
            if (rowNodes.empty()) rowNodes.push_back(n);

            // Forming 4 way connections of the current node
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
