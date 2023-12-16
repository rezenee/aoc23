#include <iostream>
#include <limits>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>

//// Compute value of lottery card.
//unsigned parse_line(std::string& line) {
//    unsigned points = 0;
//    std::vector<unsigned> winning_numbers;
//    std::vector<unsigned>lotto_numbers;
//    parse_string_into_vectors(line, winning_numbers, lotto_numbers);
//    // for each winning number
//    for(unsigned i: winning_numbers) {
//        // check for each lotto number
//        for(unsigned j: lotto_numbers) {
//            // if they are a match add to the points
//            if(i == j) {
//                if(points) points *= 2;
//                else points = 1;
//            }
//        }
//    }
//    return points;
//}
std::vector<long long> get_seeds(const std::string& input) {
    std::vector<long long> seeds;
    std::istringstream stream(input);
    while(!isdigit(stream.peek())) {
        stream.ignore();
    }
    long long num;
    while(stream >> num) {
        seeds.push_back(num);
    }
    return seeds;
}
typedef struct {
    long long destination;
    long long current;
    long long length;
} conversion;
conversion parse_conversion(const std::string& input) {
    conversion c;
    std::istringstream stream(input);
    unsigned num;
    stream >> num;
    c.destination = num;
    stream >> num;
    c.current = num;
    stream >> num;
    c.length = num;

    return c;
}
std::vector<std::vector<conversion>> create_almanac(const std::vector<std::string>& lines) {
    std::vector<std::vector<conversion>> almanac;
    bool searching = true;
    std::vector<conversion> row;
    for(std::string s : lines) {
        if(!isdigit(s[0])) {
            if(!searching) {
                searching = true;
                almanac.push_back(row);
                row.clear();
            }
            continue;
        }
        searching = false;
        // anything left is a digit
        conversion c = parse_conversion(s);
        row.push_back(c);
    }
    almanac.push_back(row);
    return almanac;
}
long long find_location(const long long& seed, const std::vector<std::vector<conversion>>& almanac) {
    long long map_num = seed;
    for(std::vector<conversion> r : almanac) {
        for(conversion c: r) {
            if(c.current <= map_num && c.current + c.length >= map_num) {
                map_num = c.destination + (map_num - c.current);
                break;
            }
        }
    }
    return map_num;
}
long long parse_seeds(std::vector<std::vector<conversion>> almanac, std::string input) {
    std::istringstream stream(input);
    while(!isdigit(stream.peek())) stream.ignore();

    long long seed;
    long long range;
    long long lowest = std::numeric_limits<long long>::max();
    while(stream >> seed) {
        stream >> range;
        std::cout << "On seed: " << seed << " with range: " << range << std::endl;
        for(long long i = 0; i < range; i++) {
            long long loc = find_location(seed +i, almanac);
            if(loc < lowest) lowest = loc;
        }
    }
    return lowest;
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
    std::vector<long long> seeds = get_seeds(lines[0]);
    unsigned total_points = 0;
    // Add calculated points from each line to running total.
   // for(std::string l : lines) {
   //     // skip past the card name
   //     total_points += parse_line(l);
   // }
   std::vector<std::vector<conversion>> almanac = create_almanac(lines);

   long long lowest = parse_seeds(almanac, lines[0]);

   std::cout << "The lowest location is: " << lowest << std::endl;
   return 0;
}
