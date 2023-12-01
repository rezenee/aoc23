#include <iostream>
#include <fstream>

using namespace std;

int main(void) {
    ifstream file("input.txt");
    if(file.is_open()) {
        string line;
        // read in each line from the file no \n 
        while(getline(file, line)) {
            cout << line << endl;
        }
    }
    else {
        cerr << "Unable to open file\n";
    }
    return 0;
}
