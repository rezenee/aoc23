#include <iostream>
#include <fstream>
#include <cctype>
#define FAILED_TO_OPEN_FILE -1

int bag_parser(std::string str) {
    int max_red = 0, max_green = 0, max_blue = 0;
    bool within_number = false;
    std::string char_number;
    int found_number;
    // iterate through each char of game hand
    for(char &c: str) {
        // indicate that you are have hit a new number to read or still inside
        if(std::isdigit(c)) {
            char_number.push_back(c);
            within_number = true;
            continue;
        }
        // without this the r in green would think its the r in red. 
        if(!within_number) continue;
        // If you are within number, but now hitting r g or b means read all
        // the numbers needed to read, so assign it to actual int.
        // Also reset the number string and within number state
        if(c == 'r' || c == 'g' || c == 'b') {
            found_number = std::stoi(char_number);
            within_number = false;
            char_number.clear();
        }
        // check if needs to update the max of each number.
        if(c == 'r') if(max_red < found_number) max_red = found_number;
        if(c == 'g') if(max_green < found_number) max_green = found_number;
        if(c == 'b') if(max_blue < found_number) max_blue = found_number;
    }
    // return the power of the set of cubes
    return max_red * max_green * max_blue;
}
int main(int argc, char* argv[]) {
    // open the file that will be reading the input from
    std::ifstream file(argv[1]);
    if(!file.is_open()) {
        std::cerr << "Unable to open file\n";
        exit(FAILED_TO_OPEN_FILE);
    }
    unsigned long sum = 0;
    std::string line;
    // until the file is empty read in each line
    while(getline(file, line)) {
        // update string past the id not used for p2
        line = line.substr(line.find(':') +1);
        // bag_parser returns the power of the sets of cubes
        sum += bag_parser(line);
    }
    std::cout << "The total sum of the power of the sets of cubes: " 
              << sum << std::endl;
    file.close();
    return 0;
}

