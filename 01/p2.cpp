#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>

#define FAILED_TO_OPEN_FILE -1
#define FAILED_TO_READ_NUMBER -2
char find_first_number(std::string str, bool reversed) {
    std::string number_chunk;
    std::string valid_strings[] = {
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine"
    };
    if(reversed) {
        for(std::string& str: valid_strings) {
            reverse(str.begin(), str.end());
        }
    }
    for(char &c: str) {
        if('0' <= c && c <= '9') {
            return c;
        }
        else {
            number_chunk.push_back(c);
        }
        for(int i = 0; i < 9; i++) {

            if(number_chunk.find(valid_strings[i]) != std::string::npos ) {
                return i+49;
            }
        }
        
    }
    return '\0';
}
int main(int argc, char* argv[]) {
    // open the file that will be reading the input from
    std::ifstream file(argv[1]);
    
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
        if( (found = find_first_number(line, 0)) == '\0') {
            std::cerr << "error finding number in line" << std::endl;
            exit(FAILED_TO_READ_NUMBER);
        }    
        calibration.push_back(found);
        // reverse the string to find the last number in practice
        std::reverse(line.begin(), line.end());
        // if number is failed to be found quit
        if( (found = find_first_number(line, 1)) == '\0') {
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
