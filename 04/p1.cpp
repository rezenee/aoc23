#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>

void parse_string_into_vectors(const std::string& input, std::vector<unsigned>& vec1, std::vector<unsigned>& vec2) {
    // go past the id number
    std::string all_numbers = input.substr(input.find(':') + 1);

    std::string first_numbers = all_numbers.substr(0, all_numbers.find('|'));
    std::string second_numbers = all_numbers.substr(all_numbers.find('|')+1);
    std::istringstream stream1(first_numbers);
    std::istringstream stream2(second_numbers);

    unsigned number;
    while(stream1 >> number) {
        vec1.push_back(number);
    }
    while(stream2 >> number) {
        vec2.push_back(number);
    }
}
// Compute value of lottery card.
unsigned parse_line(std::string& line) {
    unsigned points = 0;
    std::vector<unsigned> winning_numbers;
    std::vector<unsigned>lotto_numbers;
    parse_string_into_vectors(line, winning_numbers, lotto_numbers);
    // for each winning number
    for(unsigned i: winning_numbers) {
        // check for each lotto number
        for(unsigned j: lotto_numbers) {
            // if they are a match add to the points
            if(i == j) {
                if(points) points *= 2;
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
    std::vector<std::string> lines;
    // create a vector of lines from the file
    while(getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    unsigned total_points = 0;
    // Add calculated points from each line to running total.
    for(std::string l : lines) {
        // skip past the card name
        total_points += parse_line(l);
    }
    std::cout << "The total winning value is: " << total_points << std::endl;
    return 0;
}
