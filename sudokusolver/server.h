#ifndef SERVER_H
#define SERVER_H
#include <array>

namespace SudokuSolver {
    class Server {
        public:
            Server();
            int startListening();
            std::string handleRequest(std::string request);
            std::string solveSudoku(int sudoku[][9]);
    };
}

#endif