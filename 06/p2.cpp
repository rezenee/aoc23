#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>

unsigned parse_string_into_vectors(const std::string& input, std::vector<unsigned>& vec1, std::vector<unsigned>& vec2) {
    unsigned id;
    // go past the id number
    std::string all_numbers = input.substr(input.find(':') + 1);
    std::istringstream idstream(input);
    while(!isdigit(idstream.peek())) {
        idstream.ignore();
    }
    idstream >> id;

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
    return id;
}
// Compute value of lottery card.
unsigned parse_line(const std::string& line, unsigned& id) {
    unsigned points = 0;
    std::vector<unsigned> winning_numbers;
    std::vector<unsigned>lotto_numbers;
    id = parse_string_into_vectors(line, winning_numbers, lotto_numbers);
    // for each winning number
    for(unsigned i: winning_numbers) {
        // check for each lotto number
        for(unsigned j: lotto_numbers) {
            // if they are a match add to the points
            if(i == j) {
                points++;
            }
        }
    }
    return points;
}
void add_won_cards(std::vector<std::string>& lines, unsigned id, unsigned wins, unsigned endpoint) {
    // to make id coincide with the index in the array
    id -= 1;
    // have the loop start one after the card we are adding for
    for(unsigned i = 1; i < wins + 1; i++) {
        // the endpoint has to be unchanging because else infinity
        if(id+i >= endpoint) break;
        lines.push_back(lines[id+i]);
    }
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
    unsigned wins = 0;
    unsigned sum = lines.size();
    unsigned breakpoint = sum;
    size_t idx = 0;
    unsigned id;
    while(true) {
        // skip past the card name
        wins = parse_line(lines[idx++], id);
        sum+= wins;
        add_won_cards(lines, id, wins, breakpoint);
        std::cout << "idx: " << idx << " lines.size(): " << lines.size() << std::endl;
        if(lines.size() == idx) {
            break;
        }
    }
    std::cout << "The total winning value is: " << sum << std::endl;
    return 0;
}
