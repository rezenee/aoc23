#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <algorithm>

typedef struct {
    std::string hand;
    unsigned strength;
    unsigned type;
    unsigned buy;
} draw;
typedef struct {
    char symbol;
    unsigned occurance;
} parse_symbol;
std::string intToHexString(int value) {
    std::stringstream ss;
    ss << std::hex << value;  // Converts the integer to a hex string.
    return ss.str();
}

unsigned calculate_strength(std::string hand) {
    unsigned strength = 0;
    // A K Q J T 9 8 7 6 5 4 3 2
    std::vector<char> letters = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J',
                                 'Q', 'K', 'A'};
    // search through every letter in the hand
    std::string strength_str;
    for(int i = 0; i < hand.length(); i++) {
        // search to find which letter it is
        for(int j = 0; j < letters.size(); j++) {
            if(hand[i] == letters[j]) {
                // to construct like 1 4 5 2 11 record
                strength_str += intToHexString(j+1);
            }
        }
    }
    return std::stoul(strength_str, nullptr, 16);
}
unsigned calculate_type(const std::string& hand) {
    // TYPES strongest to weakest
    /* Five of a kind: all five chars are the same
     * Four of a kind: four cards have same label
     * Full house: three chars are one char, two chars are other char
     * Three of a kind: three chars are one char
     * Two pair: two chars are one char, two chars are other char
     * One pair: two chars are one char
     * High card: all chars are unique
     */
    std::vector<parse_symbol> parsed_symbols;
    bool found = false;
    for(char c : hand) {
        for(parse_symbol& p: parsed_symbols) {
            found = false;
            if(p.symbol == c) {
                p.occurance++;
                found = true;
                break;
            }
        }
        if(!found) {
            parse_symbol new_symbol = {c, 1};
            parsed_symbols.push_back(new_symbol);
        }
    }
    unsigned five_pairs = 0;
    unsigned four_pairs = 0;
    unsigned three_pairs = 0;
    unsigned two_pairs = 0;
    for(parse_symbol p: parsed_symbols) {
        if(p.occurance == 5) five_pairs++;
        if(p.occurance == 4) four_pairs++;
        if(p.occurance == 3) three_pairs++;
        if(p.occurance == 2) two_pairs++;
    }
    if(five_pairs == 1) {
        return 7;
    }
    if(four_pairs == 1) {
        return 6;
    }
    if(three_pairs == 1 and two_pairs == 1) {
        return 5;
    }
    if(three_pairs == 1) {
        return 4;
    }
    if(two_pairs == 2) {
        return 3;
    }
    if(two_pairs == 1) {
        return 2;
    }
    return 1;
}
bool compareDraws(const draw& a, const draw& b) {
    if(a.type > b.type) {
        return a.type > b.type;
    }
    else if(a.type < b.type) return false;

    return a.strength > b.strength;
    return false;
}
draw parse_line(const std::string& input) {
    draw hand_drawn;
    std::istringstream stream(input);
    std::string hand;
    char c;
    // read the hand
    while(true) {
        stream >> c;
        hand += c;
        if(stream.peek() == ' ') {
            stream.ignore();
            break;
        }
    }
    unsigned buy;
    // get the buy value
    stream >> buy;
    unsigned strength = calculate_strength(hand);
    unsigned type = calculate_type(hand);
    hand_drawn.strength = strength;
    hand_drawn.type = type;
    hand_drawn.buy = buy;
    hand_drawn.hand = hand;
    return hand_drawn;
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
    std::vector<draw> draws;
    for(std::string& l : lines) {
        draws.push_back(parse_line(l));
    }
    for(draw& d: draws) {
        std::cout << "card: " << d.hand << " type: " << d.type << " strength: " << d.strength << " buy: " << d.buy << std::endl;
    }
    std::sort(draws.begin(), draws.end(), compareDraws);
    std::cout << "SORTED" << std::endl;
    std::reverse(draws.begin(), draws.end());
    for(draw& d: draws) {
        std::cout << "card: " << d.hand << " type: " << d.type << " strength: " << d.strength << " buy: " << d.buy << std::endl;
    }
    long long sum = 0;
    for(int i = 0; i < draws.size(); i++) {
        if(!sum) sum = draws[i].buy;
        else sum += ((i+1) * draws[i].buy);
    }
    std::cout << "The sum of these hands is: " << sum << std::endl;
    return 0;
}
