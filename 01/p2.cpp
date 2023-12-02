#include <iostream>
#include <fstream>
#include <algorithm>

#define FAILED_TO_OPEN_FILE -1
#define FAILED_TO_READ_NUMBER -2

char find_first_number(std::string str, bool reversed) {
    std::string valid_strings[] = { "one", "two", "three", "four", "five", 
                                    "six", "seven", "eight", "nine"};
    // If the input is reversed, reverse the numbers here too.
    if(reversed) {
        for(std::string& str: valid_strings) {
            reverse(str.begin(), str.end());
        }
    }
    std::string number_chunk;
    for(char &c: str) {
        // if finding real digit return immediately
        if('0' <= c && c <= '9') return c;
        // begin building the word out of letters
        else number_chunk.push_back(c);
        // As you are building the number check if it finds a complete word.
        for(int i = 0; i < 9; i++) {
            if(number_chunk.find(valid_strings[i]) != std::string::npos ) {
                // If number is found return the int equivalent. 
                return i+49;
            }
        }
    }
    // If no number found return error.
    std::cerr << "Error finding number in line." << std::endl;
    exit(FAILED_TO_READ_NUMBER);
}
int parse_line(std::string line) {
    std::string char_num;
    // Add the the character number the number found going forward.
    char_num.push_back(find_first_number(line, false));
    
    // Reverse the string to find the last number in practice.
    std::reverse(line.begin(), line.end());
    
    // Add the the character number the number found going backward.
    char_num.push_back(find_first_number(line, true));
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
    // Until the file is empty read in each line.
    while(getline(file, line)) {
        // Add to the sum the number found for each line.
        sum += parse_line(line);
    }
    std::cout << "The total sum is: " << sum << std::endl;
    return 0;
}
