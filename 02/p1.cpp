#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <string.h>

#define FAILED_TO_OPEN_FILE -1
#define FAILED_TO_READ_NUMBER -2

#define MAX_RED_CUBES 12
#define MAX_GREEN_CUBES 13
#define MAX_BLUE_CUBES 14

int bag_parser(std::string str) {
    if(str.length() == 0) return 0;
    int max_red = 0;
    int max_green = 0;
    int max_blue = 0;
    int index = 0;
    int id;
    std::string id_str;
    // TODO find the id value 
    for(char &c: str) {
        if('0' <= c && c <= '9') {
            id_str.push_back(c);
        }
        if(c == ':') {
            break;
        }
    }
    id = std::stoi(id_str);
    bool after_number = 0;
    bool within_number = 0;
    // making a new string after the id value
    size_t delimiter_pos = str.find(':');
    std::string after_id_str = str.substr(delimiter_pos +1);
    int found_number;
    std::string char_number;
    // for use to indicate you are done reading the number and need to discern its type

    // Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
    for(char &c: after_id_str) {
        // if you are looking for the letter to tell what it is
        if(after_number) {
            if(c == 'r') {
                after_number = 0;
                if(max_red < found_number) max_red = found_number;
            }
            if(c == 'g') {
                after_number = 0;
                if(max_green < found_number) max_green = found_number;
            }
            if(c == 'b') {
                after_number = 0;
                if(max_blue < found_number) max_blue = found_number;
            }
        } // if you are looking for the numbers themselves
        else {
            // the number can have multiple digits so you need to keep a temp
            // means that you have found a number
            if('0' <= c && c <= '9') {
                char_number.push_back(c);
                within_number = 1;
            }
            else {
                // if 'in number' but not actually in number means after the number
                // aka done reading tne number so set it to what you read
                if(within_number) {
                    after_number = 1;
                    within_number = 0;
                    found_number = std::stoi(char_number);
                    char_number.clear();
                }
            }
        }
    }
    if(max_red > MAX_RED_CUBES) {
        return 0;
    }
    if(max_green > MAX_GREEN_CUBES) {
        return 0;
    }
    if(max_blue > MAX_BLUE_CUBES) {
        return 0;
    }
    return id;
}
int main(void) {
    // open the file that will be reading the input from
    std::ifstream file("input.txt");
    
    unsigned long sum = 0;
    std::string calibration;
    std::string line;
    char found;
    bool returned_value;
     // if file fails to open quit program
    if(!file.is_open()) {
        std::cerr << "Unable to open file\n";
        exit(FAILED_TO_OPEN_FILE);
    }
    // until the file is empty read in each line
    while(getline(file, line)) {
        // bag_parser returns the id of the line if valid 0 if invalid
        sum +=bag_parser(line);
        
        line.clear();
    }
    std::cout << "the total sum is " << sum << std::endl;
    return 0;
}
