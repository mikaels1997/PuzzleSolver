#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <iterator>
#include "word_finder.h"

namespace WordFinder {
    using namespace std;

    Grid::Grid(const string letters)
    {
        for (int i = 0; letters[i] != '\0'; ++i) {
            this->tiles[{i/4, i%4}] = letters[i];
        }
        this->read_words();
    }

    std::set<string> Grid::search_words() {
        for (const auto& entry : tiles){
            set<std::pair<int, int>> visited = {};
            set<string> words = {};
            string sequence(1, tiles[entry.first]);
            this->dfs(tiles, entry.first, sequence, visited, words);
        }
        return this->found_words;
    }

    void Grid::dfs(
        const map<std::pair<int, int>, char>& tiles, 
        std::pair<int, int> coord, 
        const std::string& seq, 
        set<std::pair<int, int>> visited, 
        set<string>& words) 
    {
        if (this->all_words.find(seq) != this->all_words.end()){
            this->found_words.insert(seq);
        }
        for (const auto& a: WordFinder::ADJANCENT) {
            std::pair<int, int> n = {coord.first + a.first, coord.second + a.second };
            if (!tiles.contains(n) 
                || visited.contains(n)
                || !sub_words.contains(seq)
                || seq.length() >= 10) {
                continue;
            }
            auto nextVisited = visited;
            nextVisited.insert(n);
            this->dfs(
                tiles,
                n,
                seq + tiles.at(n),
                nextVisited,
                words            
            );
        }
    }

    void Grid::read_words() {
        ifstream infile; 
        infile.open("D://Koodiohjelmat//Scripts//Cpp//PuzzleSolver//cpp//word_finder//words.txt"); 
        for (string line; getline(infile, line); ) {
            this->all_words.insert(line); 
        }
        infile.close(); 
        infile.open("D://Koodiohjelmat//Scripts//Cpp//PuzzleSolver//cpp//word_finder//subwords.txt"); 
        for (string line; getline(infile, line); ) {
            this->sub_words.insert(line); 
        }
        infile.close();
    }
}
