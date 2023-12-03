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
} part_number;
typedef struct {
    int x;
    int y;
} symbol;
void parse_line(std::string line, std::vector<part_number>& part_numbers, 
                std::vector<symbol>& symbols, int y ) {
    bool reading_number = false;
    int start_pos = 0, number_length = 0, pos = 0;
    std::string char_number;
    // search through every char in the line
    for(char &c: line) {
        // if a number is found indicate that you are reading a number and
        // continue to read the entire number
        // once the number has been read (meaning you read a symbol or a period
        // add this number to the part_number vector, and indicate that you are
        // done reading this number so you can read more numbers or symbols.
        // if you happen to read a symbol immediately after the number you have
        // to also add this symbol to the symbols array.
        // if you read a number or are in the process of reading a number
        if('0' <= c && c <= '9') {
            if(!reading_number) {
                start_pos = pos;
                reading_number = true;
                
            }
            char_number.push_back(c);
            number_length++;
            pos++;
            continue;
        }
        if(reading_number) {
            reading_number = false;
            // create the number
            part_number num;
            num.x = start_pos;
            num.y = y;
            num.l = number_length;
            num.number = std::stoi(char_number);
            char_number.clear();
            // reset the number length for next time
            number_length = 0;
            // add it to the array of found numbers
            part_numbers.push_back(num);
        }
        if(c == '.') {
            pos++;
            continue;
        }
        // add if it is a gear
        if(c == '*') {
            // if you were not reading a number simply add the symbol.
            symbol sym;
            sym.x = pos;
            sym.y = y;
            symbols.push_back(sym);
        }
        pos++;
    }
    if(reading_number) {
        reading_number = false;
        // create the number
        part_number num;
        num.x = start_pos;
        num.y = y;
        num.l = number_length;
        num.number = std::stoi(char_number);
        char_number.clear();
        // reset the number length for next time
        number_length = 0;
        // add it to the array of found numbers
        part_numbers.push_back(num);
    }
}

int main(int argc, char*argv[]) {
    // open the file that will be reading the input from
    std::ifstream file(argv[1]);
    
    std::string line;
    if(!file.is_open()) {
        std::cerr << "Unable to open file\n";
        exit(FAILED_TO_OPEN_FILE);
    }
    std::vector<part_number> part_numbers;
    std::vector<symbol> symbols;
    // until the file is empty read in each line
    int lines = 0;
    while(getline(file, line)) {
        //read through the line searching for part numbers and symbols
        // if a symbol or a part number is found, add it to the array of
        // symbols and part numbers
        parse_line(line, part_numbers, symbols, lines);
        lines++;
    }

    // search through every gear to see if it has atleast two part numbers beside it
    int count = 0;
    long long gear_ratio = 1;
    long long sum = 0;
    // read through every gear
    for(symbol &s: symbols) {
        // check each part number
        for(part_number &p: part_numbers) {
            // see if it is close enough
            if(p.y == s.y || p.y == s.y-1 || p.y == s.y+1) {
                if(p.x-1 <= s.x && s.x <= p.x+ p.l) {
                    count++;
                    gear_ratio *= p.number;
                }
            }
        }
        if(count == 2) sum += gear_ratio;
        gear_ratio = 1;
        count = 0;
    }
    std::cout << "The total sum of part numbers is: " << sum << std::endl;
    file.close();
    return 0;
}
