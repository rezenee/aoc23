#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "../aoc.h"
#include "types.h"

// returns path if found or empty string on failure
std::string walk_loop(std::vector<std::string>& lines, int y, int x, int direction) {
    std::string path;
    char loc;
    // chars |, -, L, J, 7, F, ., S
    while (true) {
        loc = lines[y][x];
        path += loc;
        if(loc == 'S') {
            return path;
        }
        if(loc == '.') {
            return "";
        }
        if(direction == NORTH) {
            if(loc == '|') y--;
            else if(loc == '7') {
                x--;
                direction = WEST;
            }
            else if(loc == 'F') {
                x++;
                direction = EAST;
            }
            else return "";
            continue;
        }
        if(direction == SOUTH) {
            if(loc == '|') y++;
            else if(loc == 'L') {
                x++;
                direction = EAST;
            }
            else if(loc == 'J') {
                x--;
                direction = WEST;
            }
            else return "";
            continue;
        }
        if(direction == EAST) {
            if(loc == '-') x++;
            else if(loc == 'J') {
                y--;
                direction = NORTH;
            }
            else if(loc == '7') {
                y++;
                direction = SOUTH;
            }
            else return "";
            continue;
        }
        if(direction == WEST) {
            if(loc == '-') x--;
            else if(loc == 'L') {
                y--;
                direction = NORTH;
            }
            else if(loc == 'F') {
                y++;
                direction = SOUTH;
            }
            else return "";
            continue;
        }
    }
}
// checks all four directions for the valid path
std::string find_path(std::vector<std::string>& lines, int y, int x) {
    std::string path = "S";
    std::string trying_path;
    path += walk_loop(lines, y - 1, x, NORTH);
    if (path.length() > 1) {
        return path;
    }
    path += walk_loop(lines, y, x + 1, EAST);
    if (path.length() > 1) {
        return path;
    }
    path += walk_loop(lines, y, x - 1, WEST);
    if (path.length() > 1) {
        return path;
    }
    path += walk_loop(lines, y - 1, x, SOUTH);
    return path;
}
// walks through path assigning value of i to each step in forward direction
// in backward direction assigning value of path.length()-i, if < i.
std::vector<unsigned> find_distances(const std::string& path) {
    std::vector<unsigned> distances;
    for(size_t i = 0; i < path.length(); i++) {
        distances.push_back(i);
    }
    for(int  i = path.length()-1; i >= 0; i--) {
        if(distances[i] > path.length() - i) distances[i] = path.length() - i;
    }
    return distances;
}

void find_start(const std::vector<std::string>& lines, int& y, int& x) {
    for(size_t i = 0; i < lines.size(); i++) {
        for(size_t j = 0; j < lines[i].length(); j++) {
            if(lines[i][j] == 'S') {
                x = j;
                y = i;
                break;
            }
        }
    }
}
int main(int argc, char*argv[]) {
    if(argc != 2) {
        std::cerr << "Invalid arguments" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::vector<std::string> lines = aoc::load_file_into_matrix(argv[1]);
    // must find position of the 'S'
    int x, y;
    find_start(lines, y, x);
    std::string path = find_path(lines, y, x);
    // now determine the furthest length on the path
    std::vector<unsigned> distances = find_distances(path);
    unsigned distance = 0;
    for(unsigned& d: distances) {
        if(d > distance) distance = d;
    }
    std::cout << distance << std::endl;
    std::cout << path << std::endl;
    return 0;
}
