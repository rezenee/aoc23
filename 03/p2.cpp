#include <iostream>
#include <fstream>
#include <algorithm>

#define FAILED_TO_OPEN_FILE -1
typedef struct {
    int x;
    int y; 
    int l;
    int number;
    bool read = false;
} part_num;
typedef struct {
    int x;
    int y;
} symbol;
void parse_line(std::string line, std::vector<part_num>& part_nums, 
                std::vector<symbol>& symbols, int y ) {
    bool reading_number = false;
    int start_pos = 0, number_length = 0, pos = 0;
    std::string char_number;
    // Iterate through every char in the line.
    for(char &c: line) {
        // If the char is a number.
        if('0' <= c && c <= '9') {
            // If not already reading, set the beginning position of the number.
            if(!reading_number) {
                start_pos = pos;
                reading_number = true;
            }
            // Add this char to string construction of the number.
            char_number.push_back(c);
            number_length++;
        }
        // If it is a gear add it to the vector. 
        if(c == '*') {
            symbol sym = {pos, y};
            symbols.push_back(sym);
        }
        // If reading_number but the char isn't a number, means done reading.
        if(reading_number && !('0' <= c && c <='9')) {
            // Add the number to the vector and reset state.
            part_num num = {start_pos, y, number_length, std::stoi(char_number)};
            part_nums.push_back(num);
            char_number.clear();
            number_length = 0;
            reading_number = false;
        }
        pos++;
    }
    // if the last char read was a number make sure to add it before returning.
    if(reading_number) {
        part_num num = {start_pos, y, number_length, std::stoi(char_number)};
        part_nums.push_back(num);
    }
}

int main(int argc, char*argv[]) {
    // Open the file that will be reading the input from.
    std::ifstream file(argv[1]);
    if(!file.is_open()) {
        std::cerr << "Unable to open file\n";
        exit(FAILED_TO_OPEN_FILE);
    }
    std::vector<part_num> part_nums;
    std::vector<symbol> symbols;
    int lines = 0;
    std::string line;
    // Read each line in the file, adding part numbers and symbols to respective
    // vectors as they are found. 
    while(getline(file, line)) {
        parse_line(line, part_nums, symbols, lines);
        lines++;
    }
    int count = 0, gear_ratio = 1, sum = 0;
    // Iterate through every gear.
    for(symbol &s: symbols) {
        // Iterate through every part number.
        for(part_num &p: part_nums) {
            // If the part number is close enough.
            if(p.y == s.y || p.y == s.y-1 || p.y == s.y+1) {
                if(p.x-1 <= s.x && s.x <= p.x+ p.l) {
                    // Add the part number to the count and gear ratio.
                    count++;
                    gear_ratio *= p.number;
                }
            }
        }
        // If the gear has exactly 2 part numbers add it to the sum.
        if(count == 2) sum += gear_ratio;
        // Reset variables for next gear.
        gear_ratio = 1;
        count = 0;
    }
    std::cout << "The total sum of part numbers is: " << sum << std::endl;
    file.close();
    return 0;
}
