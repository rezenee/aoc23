#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>

// Compute value of lottery card.
unsigned parse_line(std::string& line) {
    unsigned points = 0;
    std::vector<int> winning_numbers;
    int number;
    std::istringstream stream(line);
    // For each winning number of input add to vector of winning numbers.
    while(stream >> number) {
        winning_numbers.push_back(number);
        // Remove whitespace between significant characters.
        while(isspace(stream.peek())) stream.ignore();
        // Indicates rest of string is lottery numbers.
        if(stream.peek() == '|') {
            stream.ignore();
            break;
        }
    }
    // For each lottery number search each winning number in look for a match.
    // If there is a match update sum accordingly.
    while(stream >> number) {
        // Remove whitespace between significant characters.
        while(isspace(stream.peek())) stream.ignore();
        for(int num: winning_numbers) {
            if(number == num) {
                if(points) points*=2;
                else points = 1;
            }
        }
    }
    return points;
}
int main(int argc, char*argv[]) {
    if(argc != 2) {
        std::cerr << "Invalid arguments: ./p1 input.txt" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    // Open file the input is within.
    std::ifstream file(argv[1]);
    std::string line;
    if(!file.is_open()) {
        std::cerr << "Unable to open file\n";
        std::exit(EXIT_FAILURE);
    }

    unsigned total_points = 0;
    // Add calculated points from each line to running total.
    while(getline(file, line)) {
        // skip past the card name
        line = line.substr(line.find(':')+1);
        total_points += parse_line(line);
    }
    file.close();
    std::cout << "The total winning value is: " << total_points << std::endl;
    return 0;
}
