#include <iostream>
#include <string>
#include <fstream>
#include <regex>
using namespace std;


class HeapTree {

public:

    void readFromCSV(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Error opening file");
        }

        string line;
        getline(file, line); // Skips first line
        regex pattern(R"(^([0-9A-F]+),(.*)$)"); 
        // read 2 characters 0-9 or A-f and then 
        while (getline(file, line)) {
            smatch matches;
            if (regex_match(line, matches, pattern)) {
                cout << matches[1] << endl;
                cout << matches[2] << endl;
            }
        }

    }


private:


};

int main() {

    HeapTree ht;
    ht.readFromCSV("HFrequencies.csv");

    return 0;
}