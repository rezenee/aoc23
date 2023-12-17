#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <algorithm>

typedef struct {
    std::string id;
    std::string left_id;
    std::string right_id;
    void* left;
    void* right;
} node;
void skip_chars_stream(std::istringstream& stream, unsigned n) {
    for(int i = 0; i < n; i++) {
        stream.ignore();
    }
}
std::string stream_to_string(std::istringstream& stream, unsigned n) {
    std::string s;
    for(int i = 0; i < n; i++){
        s += stream.peek();
        stream.ignore();
    }
    return s;
}
// first read in the file the steps
/* then read into the file first pass which will assign the id, left_id, and right_id
 * from each line in the file into the vector of nodes.
 * then you will do second pass, where for each left id and right id you search to assign
 * the address of it.
 * then, you start at AAA, following, until you hit ZZZ.
 */
// AAA = (BBB, CCC)
node parse_node(std::string line) {
    node read_node;
    std::istringstream stream(line);
    std::string id, left_id, right_id;
    stream >> id;
    skip_chars_stream(stream, 4);
    left_id = stream_to_string(stream, 3);
    skip_chars_stream(stream, 2);
    right_id = stream_to_string(stream, 3);
    std::cout << id << ":" << left_id << ":" << right_id << std::endl;

    read_node.id = id;
    read_node.left_id = left_id;
    read_node.right_id = right_id;
    return read_node;
}
std::vector<node> parse_map(std::vector<std::string> lines) {
    std::vector<node> map;
    for(std::string line: lines) {
        map.push_back(parse_node(line));
    }
    return map;
}
void study_map(std::vector<node>& map) {
    unsigned id, left_id, right_id;
    void* left = nullptr;
    void* right = nullptr;
    // go through each node
    for(node& n : map) {
        // find the location of left and right
        for(node& search_node : map) {
            if(search_node.id == n.left_id)  {
                n.left = &search_node;
            }
            if(search_node.id == n.right_id)  {
                n.right = &search_node;
            }
        }
    }
}
std::vector<node*> find_start_positions(const std::vector<node>& map) {
    std::vector<node*> positions;
    for(const node& n: map) {
        if(n.id[2] == 'A') positions.push_back(const_cast<node*>(&n));
    }
    return positions;
}
int main(int argc, char*argv[]) {
    if(argc != 2) {
        std::cerr << "Invalid arguments: ./p1 input.txt" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    // Open file the input is within.
    std::ifstream file(argv[1]);
    std::string line;
    if(!file.is_open()) {
        std::cerr << "Unable to open file\n";
        std::exit(EXIT_FAILURE);
    }
    std::vector<std::string> lines;
    // create a vector of lines from the file
    while(getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    std::string path = lines[0];
    // make it so the input only has maps
    lines.erase(lines.begin(), lines.begin()+2);
    std::vector<node> map = parse_map(lines);

    study_map(map);
    // this is what ZZZ is deal with it
    std::string destination_id = "ZZZ";
    std::vector<node*> moving_nodes = find_start_positions(map);

    bool searching = true;
    long long number_of_searches = 0;
    unsigned at_end;
    unsigned max_found = 0;
    unsigned amount_needed = moving_nodes.size();
    while(searching) {
        // repeatedly loop through the path
        for(char c: path) {
            at_end = 0;
            // every new char of path is a search
            // for each path that is being walked through
            for(int i = 0; i < moving_nodes.size(); i++) {
                if(moving_nodes[i]->id[2] == 'Z') {
                    at_end++;
                }
                if(c == 'L') moving_nodes[i] = (node*) moving_nodes[i]->left;
                else moving_nodes[i] = (node*) moving_nodes[i]->right;
            }
            if(at_end == moving_nodes.size()) {
                searching = false;
                break;
            }
            else {
                if(at_end > max_found) {
                    max_found = at_end;
                }
                std::cout << "search: " << number_of_searches << " found: " << at_end << " needed: "
                          << amount_needed << " max_found: " << max_found << std::endl;
                number_of_searches++;
            }
        }
    }
    std::cout << "The number of maps it took was: " << number_of_searches << std::endl;
    return 0;
}
