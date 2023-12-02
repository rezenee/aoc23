#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>

#define FAILED_TO_OPEN_FILE -1
#define FAILED_TO_READ_NUMBER -2
char find_first_number(std::string str) {
    for(char &c: str) {
        if('0' <= c && c <= '9') {
            return c;
        }
    }
    return '\0';
}
int main(void) {
    // open the file that will be reading the input from
    std::ifstream file("input_short.txt");
    
    unsigned long sum = 0;
    std::string calibration;
    std::string line;
    char found;
    // if file fails to open quit program
    if(!file.is_open()) {
        std::cerr << "Unable to open file\n";
        exit(FAILED_TO_OPEN_FILE);
    }
    // until the file is empty read in each line
    while(getline(file, line)) {
        std::cout << line << std::endl;
        // reset the string that holds each lines found number
        calibration.clear();
        // if number is failed to be found quit
        if( (found = find_first_number(line)) == '\0') {
            std::cerr << "error finding number in line" << std::endl;
            exit(FAILED_TO_READ_NUMBER);
        }    
        calibration.push_back(found);
        // reverse the string to find the last number in practice
        std::reverse(line.begin(), line.end());
        // if number is failed to be found quit
        if( (found = find_first_number(line)) == '\0') {
            std::cerr << "error finding number in line" << std::endl;
            exit(FAILED_TO_READ_NUMBER);
        }
        calibration.push_back(found);
        std::cout << calibration << std::endl;
        // add to the running total this found number
        sum += stoi(calibration);
        // reset the string for next line
        line.clear();
    }
    std::cout << "the total sum is " << sum << std::endl;
    return 0;
}
