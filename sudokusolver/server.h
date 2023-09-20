#ifndef SERVER_H
#define SERVER_H

namespace SudokuSolver {
    class Server {
        public:
            Server();
            int startListening();
            std::string handleRequest(std::string request);
    };
}

#endif