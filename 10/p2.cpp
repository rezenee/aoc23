#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <utility>
#include "../aoc.h"
#include "types.h"

// returns path if found or empty string on failure
std::vector<tile> walk_loop(std::vector<std::string>& lines, int y, int x, int direction) {
    std::vector<tile> empty;
    std::vector<tile> path;
    tile loc;
    // chars |, -, L, J, 7, F, ., S
    while (true) {
        loc.c = lines[y][x];
        loc.x = x;
        loc.y = y;
        path.push_back(loc);
        if(loc.c == 'S') {
            return path;
        }
        if(loc.c == '.') {
            return empty;
        }
        if(direction == NORTH) {
            if(loc.c == '|') y--;
            else if(loc.c == '7') {
                x--;
                direction = WEST;
            }
            else if(loc.c == 'F') {
                x++;
                direction = EAST;
            }
            else return empty;
            continue;
        }
        if(direction == SOUTH) {
            if(loc.c == '|') y++;
            else if(loc.c == 'L') {
                x++;
                direction = EAST;
            }
            else if(loc.c == 'J') {
                x--;
                direction = WEST;
            }
            else return empty;
            continue;
        }
        if(direction == EAST) {
            if(loc.c == '-') x++;
            else if(loc.c == 'J') {
                y--;
                direction = NORTH;
            }
            else if(loc.c == '7') {
                y++;
                direction = SOUTH;
            }
            else return empty;
            continue;
        }
        if(direction == WEST) {
            if(loc.c == '-') x--;
            else if(loc.c == 'L') {
                y--;
                direction = NORTH;
            }
            else if(loc.c == 'F') {
                y++;
                direction = SOUTH;
            }
            else return empty;
            continue;
        }
    }
}
// checks all four directions for the valid path
std::vector<tile> find_path(std::vector<std::string>& lines, int y, int x) {
    std::vector<tile> path;
    tile start {x, y, 'S'};
    std::string trying_path;
    path = walk_loop(lines, y - 1, x, NORTH);
    if (!path.empty()) {
        path.insert(path.begin(), start);
        return path;
    }
    path = walk_loop(lines, y, x + 1, EAST);
    if (!path.empty()) {
        path.insert(path.begin(), start);
        return path;
    }
    path = walk_loop(lines, y, x - 1, WEST);
    if (!path.empty()) {
        path.insert(path.begin(), start);
        return path;
    }
    path = walk_loop(lines, y - 1, x, SOUTH);
    path.insert(path.begin(), start);
    return path;
}

void wipe_map(std::vector<std::string>& lines) {
    for(int i = 0; i < lines.size(); i++) {
        for(int j = 0; j < lines[i].length(); j++)
            lines[i][j] = '.';
    }
}
void rebuild_map(std::vector<std::string>& lines, const std::vector<tile>& path) {
    for(int i = 0; i < path.size(); i++)
    {
        lines[path[i].y][path[i].x] = path[i].c;
    }
}
void draw_path(std::vector<tile> path) {
    for(int i = 0; i < path.size(); i++) {
        std::cout << path[i].c;
    }
    std::cout << std::endl;
}
int main(int argc, char*argv[]) {
    if(argc != 2) {
        std::cerr << "Invalid arguments" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::vector<std::string> lines = aoc::load_file_into_matrix(argv[1]);
    // must find position of the 'S'
    std::pair<int, int> coords = aoc::find_char_in_matrix(lines, 'S');
    int x = coords.first;
    int y = coords.second;

    std::vector<tile> path = find_path(lines, y, x);
    draw_path(path);
    // TODO convert the map to only . and path
    wipe_map(lines);
    rebuild_map(lines, path);
    aoc::draw_matrix(lines);


    return 0;
}