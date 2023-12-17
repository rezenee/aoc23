#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <numeric>

// this function destructively reduces the passed in vector to the differences
// until the vector has a difference of all 0.
long long calculate_difference(std::vector<long long>& sequence) {
    // make n in the sequence equal to n+1 - n
    for(size_t i = 0; i < sequence.size() -1; i++) {
        sequence[i] = sequence[i+1] - sequence[i];
    }
    // remove the final number and return it
    long long back = sequence.back();
    sequence.pop_back();
    return back;
}
// this function finds the next value that would be in the sequence from line.
long long next_value_in_sequence(const std::string& line) {
    long long value = 0;
    std::vector<long long> sequence;
    std::vector<long long> final_numbers;
    std::istringstream stream(line);
    long long num;
    while(stream >> num) {
        sequence.push_back(num);
    }
    long long last_value;
    for(auto n: sequence) {
        std::cout << n << ", ";
    }
    std::cout << std::endl;
    while(true) {
        last_value = calculate_difference(sequence);
        std::cout << "last value: " << last_value << std::endl;
        for(auto n: sequence) {
            std::cout << n << ", ";
        }
        std::cout << std::endl;
        final_numbers.push_back(last_value);
        if(std::accumulate(sequence.begin(), sequence.end(), 0LL) == 0) {
            std::cout << "differences are all 0, finished. " << std::endl;
            break;
        }
    }
    for(auto final_num: final_numbers) {
        value += final_num;
    }
    return value;
}
int main(int argc, char*argv[]) {
    if(argc != 2) {
        std::cerr << "Invalid arguments: ./p1 input.txt" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    // Open file the input is within.
    std::ifstream file(argv[1]);
    if(!file.is_open()) {
        std::cerr << "Unable to open file\n";
        std::exit(EXIT_FAILURE);
    }
    // create a vector of lines from the file
    std::string line;
    std::vector<std::string> lines;
    while(getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    long long sum = 0;
    long long current_value;
    for(const std::string& l : lines) {
        current_value = next_value_in_sequence(l);
        sum += current_value;
        std::cout << "the next value in seq is: " << current_value << std::endl << std::endl;
    }
    std::cout << "The sum of these sequences is: " << sum << std::endl;
    return 0;
}
