#include <iostream>
#include <string>
#include <sstream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

std::string handle_request(const std::string& request) {
    // Handle the request here
    std::cout << request << std::endl;
    return "HTTP/1.1 200 OK\r\nContent-Length: 23\r\nContent-Type: text/plain\r\nAccess-Control-Allow-Origin: *\r\n\r\nHello from C++ Server!!";
}

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock" << std::endl;
        return 1;
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Error creating socket: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Error binding socket: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Error listening on socket: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server listening on port 8080..." << std::endl;

    while (true) {
        sockaddr_in clientAddress{};
        int clientAddressLength = sizeof(clientAddress);

        SOCKET clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddress), &clientAddressLength);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Error accepting client connection: " << WSAGetLastError() << std::endl;
            continue;
        }

        char buffer[4096];
        int bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesRead == SOCKET_ERROR) {
            std::cerr << "Error receiving data from client: " << WSAGetLastError() << std::endl;
            closesocket(clientSocket);
            continue;
        }

        buffer[bytesRead] = '\0';

        std::string request(buffer);
        std::string response = handle_request(request);

        if (send(clientSocket, response.c_str(), response.length(), 0) == SOCKET_ERROR) {
            std::cerr << "Error sending response to client: " << WSAGetLastError() << std::endl;
        }

        closesocket(clientSocket);
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}










// /*-----------------Terminology----------------
//     * 
//     * Sudoku matrix:
//     *      Representation of the sudoku in most basic form.
//     *      Usually 9 * 9 matrix with values from 1 to 9
//     * Constraint matrix: 
//     *      A matrix whose rows represent the possibilities (initially size^3) and columns the constraint sets (size^2 * 4) of the sudoku
//     *      Only contains 0s and 1s in this case
//     *      For example empty 9x9 sudoku includes 9*9*9 = 729 possibilities and 9*9*4 = 324 constraint sets.
//     *      There are 4 different types of constraints: 
//     *           Cell (one number per cell)
//     *           Row (one unique number per row), 
//     *           Column (one unique number per column),
//     *           Box (one unique number per box). Usually size of 3x3
//     * 
//     * ---------Methodology in a nutshell-------
//     * 
//     * Basic goal:           Solving an exact cover problem. Sudoku can be considered as one.
//     * Search method:        Knuth's Algorithm X (recursive, depth-first, backtracking algorithm to solve exact cover problem)
//     * Optimization:         Dancing links technique (constraint matrix as 4-way circular linked list to be used in Algorithm X)
//     *                       Speeds up the search considerably.
//     * Solve steps:          Sudoku matrix -> constraint matrix -> linked list -> Knuth's Algorithm X -> solved constraint matrix -> solved sudoku matrix
// */

// // #include <iostream>
// // #include "sudoku.h"
// // #include "algx.h"
// #include "server.cpp"

// int main()
// {
//     int arr[9][9] = {
//         {0, 0, 0, 7, 0, 0, 0, 0, 1},
//         {0, 0, 0, 0, 0, 0, 8, 0, 0},
//         {0, 2, 0, 8, 6, 0, 0, 5, 0},

//         {0, 3, 0, 0, 0, 0, 0, 0, 0},
//         {6, 0, 0, 0, 0, 0, 0, 8, 4},
//         {0, 1, 2, 6, 0, 7, 0, 3, 0},

//         {3, 0, 0, 5, 0, 0, 0, 2, 8},
//         {0, 9, 4, 0, 0, 0, 3, 0, 7},
//         {0, 7, 0, 0, 0, 0, 0, 0, 0},
//     };
//     SudokuSolver::Sudoku sudoku(arr);
//     SudokuSolver::AlgorithmX algx(sudoku.CMat);
//     algx.findExactCover(algx.root);
//     auto sol = sudoku.toSudokuMatrix(algx.solutionMat);
//     sudoku.printMatrix(sol);
//     testtt();
// }
