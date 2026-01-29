#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include "word_finder.h"
#include <stdio.h>

// In build directory:
//g++ -std=c++20 -shared -o libwordfinder.dll ../word_finder/word_finder_api.cpp ../word_finder/word_finder.cpp
extern "C" {
    __declspec(dllexport)
    const int handleRequest(const char* input, char* output, int output_size) {
        WordFinder::Grid grid(input);
        std::set<std::string> words = grid.search_words();
        std::string flattened;
        for (auto it = words.begin(); it != words.end(); ++it) {
            if (it != words.begin()) flattened += ";";
            flattened += *it;
        }
        if ((int)flattened.size() + 1 > output_size)
            return -1;

        std::memcpy(output, flattened.c_str(), flattened.size() + 1);
        return 0;
    }
}