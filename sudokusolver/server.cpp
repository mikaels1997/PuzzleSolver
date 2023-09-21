#include <iostream>
#include <string>
#include <sstream>
#include <winsock2.h>
#include <algorithm>
#include "server.h"
#include "sudoku.h"
#include "algx.h"

namespace SudokuSolver {
    Server::Server() {

    };

    int Server::startListening() {
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
            
            // Find the position of the double CRLF that separates headers from the payload
            std::size_t payloadStart = request.find("\r\n\r\n");
            
            if (payloadStart != std::string::npos) {

                payloadStart += 4; // Move to the start of the payload
                
                // Extract the payload based on the Content-Length header
                std::string contentLengthHeader = "Content-Length: ";
                std::size_t contentLengthPos = request.find(contentLengthHeader);

                if (contentLengthPos != std::string::npos) {
                    std::size_t payloadEnd = request.find("\r\n", contentLengthPos);
                    std::string contentLengthStr = request.substr(contentLengthPos + contentLengthHeader.length(), payloadEnd - (contentLengthPos + contentLengthHeader.length()));
                    std::size_t contentLength = std::stoul(contentLengthStr);
                    
                    if (request.length() - payloadStart >= contentLength) {
                        std::string payload = request.substr(payloadStart, contentLength);
                        std::string response = handleRequest(payload);

                        if (send(clientSocket, response.c_str(), response.length(), 0) == SOCKET_ERROR) {
                            std::cerr << "Error sending response to client: " << WSAGetLastError() << std::endl;
                        }
                    }
                }
            }
        }

        closesocket(serverSocket);
        WSACleanup();
        return 0;
    }

    std::string Server::handleRequest(std::string request) {
        char chars[] = "[]";
        for (unsigned int i = 0; i < strlen(chars); ++i)
        {
            request.erase (std::remove(request.begin(), request.end(), chars[i]), request.end());
        }

        std::string origin;
        std::istringstream ss(request);
        std::string item;
        int sudokuArr[9][9];
        int count = 0;
        while (std::getline(ss, item, ',')) {
            int value = std::stoi(item != "null" ? item : "0");
            sudokuArr[count/9][count%9] = value;
            count++;
        }
        std::string flattened = solveSudoku(sudokuArr);
        char buffer[400];
        const char* payload = flattened.c_str();
        sprintf(buffer, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\nContent-Type: text/plain\r\nAccess-Control-Allow-Origin: *\r\n\r\n%s", strlen(payload), payload);
        return buffer;
    }

    std::string Server::solveSudoku(int arr[9][9]) {
        // int arr[9][9] = {
        // {0, 0, 0, 7, 0, 0, 0, 0, 1},
        // {0, 0, 0, 0, 0, 0, 8, 0, 0},
        // {0, 2, 0, 8, 6, 0, 0, 5, 0},

        // {0, 3, 0, 0, 0, 0, 0, 0, 0},
        // {6, 0, 0, 0, 0, 0, 0, 8, 4},
        // {0, 1, 2, 6, 0, 7, 0, 3, 0},

        // {3, 0, 0, 5, 0, 0, 0, 2, 8},
        // {0, 9, 4, 0, 0, 0, 3, 0, 7},
        // {0, 7, 0, 0, 0, 0, 0, 0, 0},
        // };
        SudokuSolver::Sudoku sudoku(arr);
        SudokuSolver::AlgorithmX algx(sudoku.CMat);
        algx.findExactCover(algx.root);
        auto sol = sudoku.toSudokuMatrix(algx.solutionMat);
        std::string flattened = sudoku.solutionAsString(sol);
        return flattened;
    }
}