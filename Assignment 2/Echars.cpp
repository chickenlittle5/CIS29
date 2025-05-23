#include "Echar.cpp"
#include "MultiKeyVector.cpp"
#include <fstream>
#include <regex>

class Echars : public MultiKeyVector<Echar> {
public:
    Echars() {}

    void readFromCSV(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Could not open file");
        }

        string line;
        regex pattern(R"(([^,]*),([^,]*),([^,]*))"); 
        while (getline(file, line)) {
            smatch matches;
            if (regex_match(line, matches, pattern)) {
                string ebcdic = matches[1];
                string hex = matches[2];
                string ascii = matches[3];
                Echar echar(ascii, ebcdic, hex);
                this->push_back(echar);
                this->setStringIndex(echar.getBits().to_string(), this->size() - 1);
            }
        }
        
        file.close();

    }

    void printEchars() {
        for (Echar echar : *this) {
            echar.printBits();
        }
    }

private:

};

// int main() {

//     Echars echars;
//     echars.readFromCSV("Tuple.csv");
//     cout << echars["000000010001"].getAscii();

//     return 0;
// }