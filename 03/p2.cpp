#include <iostream>
#include <fstream>

#define FAILED_TO_OPEN_FILE -1

int main(int argc, char*argv[]) {
    // open the file that will be reading the input from
    std::ifstream file(argv[1]);
    
    std::string line;
    if(!file.is_open()) {
        std::cerr << "Unable to open file\n";
        exit(FAILED_TO_OPEN_FILE);
    }
    // until the file is empty read in each line
    while(getline(file, line)) {
    }
    
    file.close();
    return 0;
}
