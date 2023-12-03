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
        else {
            // if you were not reading a number simply add the symbol.
            symbol sym;
            sym.x = pos;
            sym.y = y;
            symbols.push_back(sym);
            pos++;
        }
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
    int sum = 0;
    while(getline(file, line)) {
        //read through the line searching for part numbers and symbols
        // if a symbol or a part number is found, add it to the array of
        // symbols and part numbers
        parse_line(line, part_numbers, symbols, lines);
        lines++;
    }
    std::cout << "PARTNUMBERS" << std::endl;
    for(part_number &p: part_numbers) {
        std::cout << "x: " << p.x << " y: " << p.y << " l: " << p.l << std::endl;
    }
    std::cout << "SYMBOLS" << std::endl;
    for(symbol &s: symbols) {
        std::cout << "x: " << s.x << " y: " << s.y << std::endl;
    }
    // search through every part number
    for(part_number &p: part_numbers) {
        // search through every symbol 
        for(symbol &s: symbols) {
            if(p.y == s.y || p.y == s.y-1 || p.y == s.y+1) {
                if(p.x-1 <= s.x && s.x <= p.x+ p.l) {
                    if(p.read == false) {
                        std::cout << p.number << std::endl;
                        sum+=p.number;
                        p.read = true;
                    }
                }
            }
        }
    }
    std::cout << "The total sum of part numbers is: " << sum << std::endl;
    file.close();
    return 0;
}
