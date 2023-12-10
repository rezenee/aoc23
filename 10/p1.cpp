#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>

std::string find_path(std::vector<std::string>& lines, int direction, int y, int x, std::string path) {
    if (x >= lines.size()) return "";

    // out of bounds in this direction
    //
    if (x < 0 || y < 0 || x >= lines.size() || x >= lines[x].length() || y >= lines.size()) return "";
    char cur_loc = lines[y][x];
    // the first recursive call is on the 'S' with direction 0
    if(direction != 0 && cur_loc == 'S') {
        return path + cur_loc;
    }
    // if the pipe you hit is an impossible path to continue
    if(direction == 1 && (cur_loc == '-' || cur_loc == 'L' || cur_loc == 'J' || cur_loc == '.')) {
        return "";
    }
    if(direction == 2 && (cur_loc == '|' || cur_loc == 'L' || cur_loc == 'F' || cur_loc == '.')) {
        return "";
    }
    if(direction == 3 && (cur_loc == '-' || cur_loc == 'F' || cur_loc == '7' || cur_loc == '.')) {
        return "";
    }
    if(direction == 4 && (cur_loc == '|' || cur_loc == 'J' || cur_loc == '7' || cur_loc == '.')) {
        return "";
    }
    // north
    if(direction != 3 && (cur_loc != '-' && cur_loc != '7' && cur_loc != 'F' && cur_loc != '.')) {
        std::string north = find_path(lines, 1, y - 1, x, path + cur_loc);
        if (!north.empty()) return north;
    }
    // east
    if(direction != 4 && (cur_loc != '|' && cur_loc != 'J' && cur_loc != '7' && cur_loc != '.')) {
        std::string east = find_path(lines, 2, y, x + 1, path + cur_loc);
        if (!east.empty()) return east;
    }
    // south
    if(direction != 1 && (cur_loc != '-' && cur_loc != 'L' && cur_loc != 'J' && cur_loc != '.')) {
        std::string south = find_path(lines, 3, y + 1, x, path + cur_loc);
        if (!south.empty()) return south;
    }
    // west
    if(direction != 2 && (cur_loc != '|' && cur_loc != 'L' && cur_loc != 'F' && cur_loc != '.')) {
        std::string west = find_path(lines, 4, y, x - 1, path + cur_loc);
        if (!west.empty()) return west;
    }

    // if not current location or other location failed path, return ""
    return "";
}
std::vector<unsigned> find_distances(std::string path) {
    std::vector<unsigned> distances;
    for(int i = 0; i < path.length(); i++) {
        distances.push_back(i);
    }
    for(int i = path.length()-1; i >= 0; i--) {
        if(distances[i] > path.length() - i) distances[i] = path.length() - i;
    }
    return distances;
}
int main(int argc, char*argv[]) {
    if(argc != 2) {
        std::cerr << "Invalid arguments" << std::endl;
        exit(EXIT_FAILURE);
    }
    // open the file that will be reading the input from
    std::ifstream file(argv[1]);

    if(!file.is_open()) {
        std::cerr << "Unable to open file\n";
        exit(EXIT_FAILURE);
    }
    std::vector<std::string> lines;
    std::string line;
    // until the file is empty read in each line
    while(getline(file, line)) {
        lines.push_back(line);
    }
    // must find position of the 'S'
    unsigned x, y;
    for(int i = 0; i < lines.size(); i++) {
        for(int j = 0; j < lines[i].length(); j++) {
            if(lines[i][j] == 'S') {
                x = j;
                y = i;
                break;
            }
        }
    }
    std::string path = find_path(lines, 0, y, x, "");
    // now determine the furthest length on the path
    std::vector<unsigned> distances = find_distances(path);
    unsigned distance = 0;
    for(unsigned& d: distances) {
        if(d > distance) distance = d;
    }
    std::cout << distance << std::endl;
    std::cout << path << std::endl;
    file.close();
    return 0;
}
