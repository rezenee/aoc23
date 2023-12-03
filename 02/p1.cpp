#include <iostream>
#include <fstream>
#include <cctype>

#define FAILED_TO_OPEN_FILE -1
#define FAILED_TO_READ_NUMBER -2

#define MAX_RED_CUBES 12
#define MAX_GREEN_CUBES 13
#define MAX_BLUE_CUBES 14

int find_id(std::string str) {
    std::string char_number;
    for(char &c: str) {
        if(std::isdigit(c)) char_number.push_back(c);
        if(c == ':') break;
    }
    return std::stoi(char_number);
}
int bag_parser(std::string str) {
    int id = find_id(str);
    // making a new string after the id value
    str = str.substr(str.find(':')+1);
    
    int max_red = 0, max_green = 0, max_blue = 0;
    bool within_number = false;
    std::string char_number;
    int found_number;
    for(char &c: str) {
        // indicate that you are have hit a new number to read or still inside
        if(std::isdigit(c)) {
            char_number.push_back(c);
            within_number = 1;
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
    if(max_red > MAX_RED_CUBES) return 0;
    if(max_green > MAX_GREEN_CUBES) return 0;
    if(max_blue > MAX_BLUE_CUBES) return 0;
    // so long as all marble counts are possible return the id
    return id;
}
int main(int argc, char*argv[]) {
    // open the file that will be reading the input from
    std::ifstream file(argv[1]);
    
    unsigned long sum = 0;
    std::string line;
    if(!file.is_open()) {
        std::cerr << "Unable to open file\n";
        exit(FAILED_TO_OPEN_FILE);
    }
    // until the file is empty read in each line
    while(getline(file, line)) {
        // bag_parser returns the id of the line if valid or 0 if invalid.
        sum += bag_parser(line);
    }
    std::cout << "The total sum is: " << sum << std::endl;
    file.close();
    return 0;
}
