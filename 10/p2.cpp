#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>

typedef struct {
    int x;
    int y;
    char c;
} tile;
std::vector<tile> find_path(std::vector<std::string>& lines, int direction, int y, int x, std::vector<tile> path) {
    std::vector<tile> empty;

    // out of bounds in this direction
    if (x < 0 || y < 0 || x >= lines.size() || x >= lines[x].length() || y >= lines.size()) return empty;
    tile cur_loc = {x, y, lines[y][x]};

    // the first recursive call is on the 'S' with direction 0
    if(direction != 0 && cur_loc.c == 'S') {
        path.push_back(cur_loc);
        return path;
    }
    // if the pipe you hit is an impossible path to continue
    if(direction == 1 && (cur_loc.c == '-' || cur_loc.c == 'L' || cur_loc.c == 'J' || cur_loc.c == '.')) {
        return empty;
    }
    if(direction == 2 && (cur_loc.c == '|' || cur_loc.c == 'L' || cur_loc.c == 'F' || cur_loc.c == '.')) {
        return empty;
    }
    if(direction == 3 && (cur_loc.c == '-' || cur_loc.c == 'F' || cur_loc.c == '7' || cur_loc.c == '.')) {
        return empty;
    }
    if(direction == 4 && (cur_loc.c == '|' || cur_loc.c == 'J' || cur_loc.c == '7' || cur_loc.c == '.')) {
        return empty;
    }
    // north
    if(direction != 3 && (cur_loc.c != '-' && cur_loc.c != '7' && cur_loc.c != 'F' && cur_loc.c != '.')) {
        path.push_back(cur_loc);
        std::vector<tile> north = find_path(lines, 1, y - 1, x, path);
        if (!north.empty()) return north;
        else path.pop_back();
    }
    // east
    if(direction != 4 && (cur_loc.c != '|' && cur_loc.c != 'J' && cur_loc.c != '7' && cur_loc.c != '.')) {
        path.push_back(cur_loc);
        std::vector<tile> east = find_path(lines, 2, y, x + 1, path);
        if (!east.empty()) return east;
        else path.pop_back();
    }
    // south
    if(direction != 1 && (cur_loc.c != '-' && cur_loc.c != 'L' && cur_loc.c != 'J' && cur_loc.c != '.')) {
        path.push_back(cur_loc);
        std::vector<tile> south = find_path(lines, 3, y + 1, x, path);
        if (!south.empty()) return south;
        else path.pop_back();
    }
    // west
    if(direction != 2 && (cur_loc.c != '|' && cur_loc.c != 'L' && cur_loc.c != 'F' && cur_loc.c != '.')) {
        path.push_back(cur_loc);
        std::vector<tile> west = find_path(lines, 4, y, x - 1, path);
        if (!west.empty()) return west;
        else path.pop_back();
    }
    // if not current location or other location failed path, return ""
    return empty;
}

void wipe_map(std::vector<std::string>& lines) {
    for(int i = 0; i < lines.size(); i++) {
        for(int j = 0; j < lines[i].length(); j++)
            lines[i][j] = '.';
    }
}
void display_map(std::vector<std::string>& lines) {
    for(std::string s : lines){
        std::cout << s << std::endl;
    }
}
void rebuild_map(std::vector<std::string>& lines, const std::vector<tile>& path) {
    for(int i = 0; i < path.size(); i++)
    {
        lines[path[i].y][path[i].x] = path[i].c;
    }
}
// S-7|J-L|S
void rebuild_path(std::vector<std::string>& lines, std::string path, int y, int x) {
    for(int i = 0; i < path.length(); i++){
        lines[y][x] = path[i];
        // if on last char of path job is done.
        if(i == path.length() - 1) {
            break;
        }
    }
}

int check_if_bounded(std::vector<std::string>& lines, int y, int x, int direction) {
    char cur_loc = lines[y][x];
    // if it hits an edge anywhere than it must be unbounded
    if (x < 0 || y < 0 || x >= lines.size() || x >= lines[x].length() || y >= lines.size()) return 0;

    // left vertical slips: J, 7, ., |
    // right vertical slips: L, F, ., |
    // potential slips JL 7L .L |L JF 7F .F |F J. 7. .. ||
    // if cur_loc is any of the chars in right vertical slip, if any char in left vertical slips is to the left it is a slip.
    // if cur_loc is any of the chars in the left vertical slip, if any char in the right vertical slips is to the right it is a slip.
    // horizontal above slips: -, L, J, .
    // horizontal below sips: -, J, 7, F
    // potential slips
    // - L J J . L
    // - J 7 F F 7
    // if you are going up for down check for slips on that axis
    char besides_loc;
    int north, east, south, west;
    if(direction == 1 || direction == 3) {
        // if cur_loc is left slip
        if(cur_loc == 'J' || cur_loc == '7' || cur_loc == '|') {
            // if cur_loc is the rightmost location impossible to have right slip
            if(x >= lines[y].length()) return 1;
            // check the right location if right slip exists.
            besides_loc = lines[y][x+1];
            if(besides_loc == 'L' || besides_loc == 'F' || besides_loc == '.' || besides_loc == '|') {
                // Current tile is northern of previous tile.
                if(direction == 1) {
                       north = check_if_bounded(lines, y - 1, x, 1);
                       if (!north) return 0;
                }
                // Current tile is southern of previous tile.
                if(direction == 3) {
                    south = check_if_bounded(lines, y + 1, x, 3);
                    if (!south) return 0;
                }
            }
        }
        // if cur_loc is right slip
        if(cur_loc == 'L' || cur_loc == 'F' || cur_loc == '|') {
            // cur_loc is leftmost location impossible to have left slip
            if(x == 0) return 1;
            // check the left location if slip exists.
            besides_loc = lines[y][x-1];
            if(besides_loc == 'J' || besides_loc == '7' || besides_loc == '.' || besides_loc == '|') {
               // Current tile is northern of previous tile.
                if(direction == 1) {
                       north = check_if_bounded(lines, y - 1, x, 1);
                       if (!north) return 0;
                }
                // Current tile is southern of previous tile.
                if(direction == 3) {
                    south = check_if_bounded(lines, y + 1, x, 3);
                    if (!south) return 0;
                }
            }
        }
    }

    // anything here is on a '.' icon, or it is a pipe that is a slip
    if(direction != 3) {
        north = check_if_bounded(lines, y - 1, x, 1);
        if (!north) return 0;
    }
    if(direction != 4) {
        east = check_if_bounded(lines, y, x + 1, 2);
        if (!east) return 0;
    }
    if(direction != 1) {
        south = check_if_bounded(lines, y + 1, x, 3);
        if (!south) return 0;
    }
    if(direction != 2) {
        west = check_if_bounded(lines, y, x-1, 4);
        if(!west) return 0;
    }
    // if after everything no edge is hit then it must be bounded
    return 1;
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
    file.close();
    // must find position of the 'S'
    int x, y;
    for(int i = 0; i < lines.size(); i++) {
        for(int j = 0; j < lines[i].length(); j++) {
            if(lines[i][j] == 'S') {
                x = j;
                y = i;
                break;
            }
        }
    }

    std::vector<tile> empty;
    std::vector<tile> path = find_path(lines, 0, y, x, empty);
    for(int i = 0; i < path.size(); i++) {
        std::cout << path[i].c;
    }
    std::cout << std::endl;
    // TODO convert the map to only . and path
    wipe_map(lines);
    rebuild_map(lines, path);
    display_map(lines);
    /* for each char in lines if it is a '.'
     * if it is possible to find an out-of-bounds position, return 0
     * if it is not possible return 1
     * the only way that a '.' will not find an out-of-bounds position is if it
     * is within the constraints of the path
     */
    int sum = 0;
    for(int i = 0; i < lines.size(); i++) {
        for(int j = 0; j < lines[i].length(); i++) {
            sum += check_if_bounded(lines, i, j, 0);
        }
    }

    return 0;
}
