#include <iostream>
#include <limits>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>

typedef struct {
    long long time;
    long long distance;
} race;
unsigned long parse_race(const race& r) {
    long long velocity = 0;
    long long number_of_wins = 0;
    for(long long i = 1; i <= r.time; i++) {
        velocity = i;
        if(velocity * (r.time - i) > r.distance) {
            number_of_wins++;
        }

    }
    return number_of_wins;
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
    std::istringstream time_stream(lines[0]);
    std::istringstream distance_stream(lines[1]);
    long long time;
    long long  distance;
    std::vector<race> races;
    while(!isdigit(time_stream.peek())) time_stream.ignore();
    while(!isdigit(distance_stream.peek())) distance_stream.ignore();
    while(time_stream >> time) {

        distance_stream >> distance;
        race r = {time, distance};
        races.push_back(r);
    }
    long long sum = 1;
    for(race r : races) {
        sum *= parse_race(r);
    }
    std::cout << "The sum of wins is: " << sum << std::endl;
    return 0;
}
