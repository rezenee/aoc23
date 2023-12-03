#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>
#define FAILED_TO_OPEN_FILE -1
#define FAILED_TO_READ_NUMBER -2

char find_first_number(std::string str) {
    for(char &c: str) {
        if(std::isdigit(c)) return c;
    }
    std::cerr << "Error finding number in line." << std::endl;
    exit(FAILED_TO_READ_NUMBER);
}
int parse_line(std::string line) {
    std::string char_num;
    // add the the character number the number found going forward
    char_num.push_back(find_first_number(line));
    
    // reverse the string to find the last number in practice
    std::reverse(line.begin(), line.end());
    
    // add the the character number the number found going backward
    char_num.push_back(find_first_number(line));
    return std::stoi(char_num);
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
        // Add to the sum the number found for each line.
        sum += parse_line(line);
    }
    std::cout << "The total sum is: " << sum << std::endl;
    return 0;
}
