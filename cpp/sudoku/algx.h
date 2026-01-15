#ifndef ALGX_H
#define ALGX_H
#include <iostream>
#include "sudoku.h"
#include <vector>
#include <array>

namespace SudokuSolver {
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
            int search_n;                                          // Search number (to determine if solution can be found) 

        public:
            std::vector<std::array<int, Sudoku::CNS>> solutionMat; // Solved exact cover matrix
            Node* root;

            AlgorithmX(std::vector<std::array<int, Sudoku::CNS>> cMat);

            /// @brief Finds solution to exact cover problem
            /// @param root Root of the linked list
            void findExactCover(Node* root);

            /// @brief Recursive depth-first search of Algorithm X
            /// @param k Current depth
            void search(int k);

            /// @brief Covers column as part of Algorithm X
            /// @param c The header of the column to be covered
            void coverColumn(Node* c);

            /// @brief Uncovers column as part of Algorithm X
            /// @param c The header of the column to be uncovered 
            void uncoverColumn(Node* c);

            /// @brief Chooses the column with least size
            /// @param root Root node of linked list
            /// @return The column header with least size
            Node* chooseColumn(Node* root);

            /// @brief Converts constraint matrix to linked list
            /// @param consMat Initialized constraint matrix of a sudoku
            /// @return 4 way circular linked list of an initialized sudoku with additional header nodes  
            Node* toLinkedList(std::vector<std::array<int, Sudoku::CNS>> consMat);
    };
}

#endif