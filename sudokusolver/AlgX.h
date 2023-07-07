#ifndef ALGX_H
#define ALGX_H
#include <iostream>
#include "sudoku.h"
#include <vector>
#include <array>

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
        Node(int r, int c, Node* h);
};

class AlgorithmX {
    private:
        Node* colHeader;
        Node* solution[Sudoku::CLS];
    public:
        std::vector<std::array<int, Sudoku::CNS>> solutionMat;
        Node* root;

        AlgorithmX(std::vector<std::array<int, Sudoku::CNS>> cMat);

        void findExactCover(Node* root, std::vector<std::array<int, Sudoku::CNS>> unsolved);

        void search(int k, std::vector<std::array<int, Sudoku::CNS>> unsolved);

        void coverColumn(Node* c);

        void uncoverColumn(Node* c);

        Node* chooseColumn(Node* root);

        Node* toLinkedList(std::vector<std::array<int, Sudoku::CNS>> consMat);
};

#endif