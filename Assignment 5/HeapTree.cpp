#include "MultiKeyVector.cpp"
#include "MinHeap.cpp"
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
        // read 2 characters 0-9 or A-f and then whatever is left
        MinHeap<float, string> HF;
        while (getline(file, line)) {
            smatch matches;
            if (regex_match(line, matches, pattern)) {
                string symbol = convertHex(matches[1]);
                float freq = stof(matches[2]);
                HF.insert(freq, symbol);
            }
        }

    }

    MinHeap<float, string> QTree(MinHeap<float, string> HF) {
        MinHeap<float, string> ft;
        while (HF.size() > 1) {
            auto QLeft = HF.front();
            HF.pop();
            auto QRight = HF.front();
            HF.pop();
            Branch bnode(QLeft, QRight);
        }
    }

    string convertHex(string hex) {

    }


private:
    MinHeap<string, string> mh;


};

int main() {

    HeapTree ht;
    ht.readFromCSV("HFrequencies.csv");

    return 0;
}