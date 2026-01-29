#ifndef WORD_FINDER_H
#define WORD_FINDER_H
#include <iostream>
#include <map>
#include <set>
#include <vector>

namespace WordFinder {

    using namespace std;
    const static std::vector<std::pair<int, int>> ADJANCENT = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

    class Grid {
        public:
            set<string> found_words;
            Grid(const string letters); 
            set<string> search_words();
        private:
            std::set<string> all_words;
            std::set<string> sub_words;
            std::map<std::pair<int, int>, char> tiles;
            void read_words();
            void dfs(const map<std::pair<int, int>, char>& tiles, std::pair<int, int> coord, const std::string& seq, set<std::pair<int, int>> visited, set<string>& words);
    };
}

#endif