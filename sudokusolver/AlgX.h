#ifndef ALGX_H
#define ALGX_H
#include <iostream>
#include "sudoku.h"
#include <vector>
#include <array>

/// @brief Used to form linked list to utilize Dancing Links technique
struct Node {
    public:
        Node* top;      // Link to top node
        Node* right;    // Link to right node
        Node* bottom;   // Link to bottom node
        Node* left;     // Link to left node
        int row;        // Row index
        int col;        // Column index
        int size;       // Column size (only used by header nodes)
        Node* colHeader;// Link to column header

        Node() {};
        Node(int r, int c, Node* h);
};

/// @brief Implementation of Knuth's Algorithm X with dancing links technique to solve exact cover problem
class AlgorithmX {
    private:
        Node* colHeader;
        Node* solution[Sudoku::CLS];
        std::vector<std::array<int, Sudoku::CNS>> unsolved;    // Unsolved exact cover constraint matrix

    public:
        std::vector<std::array<int, Sudoku::CNS>> solutionMat; // Solved exact cover matrix
        Node* root;

        AlgorithmX(std::vector<std::array<int, Sudoku::CNS>> cMat);

        void findExactCover(Node* root);

        void search(int k);

        void coverColumn(Node* c);

        void uncoverColumn(Node* c);

        Node* chooseColumn(Node* root);

        Node* toLinkedList(std::vector<std::array<int, Sudoku::CNS>> consMat);
};

#endif