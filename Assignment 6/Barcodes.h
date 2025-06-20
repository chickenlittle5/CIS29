#ifndef BARCODES
#define BARCODES

#include "MultiKeyVector.cpp"
#include <fstream>
#include <regex>
#include <bitset>

class Barcode : public MultiKeyVector<tuple<char, string, string>> {

public:
    Barcode() {}
    Barcode(const string& filename) {
        loadFromCSV(filename);
    }

    void loadFromCSV(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Could not open Barcode file: " + filename);
        }
        regex pattern(R"(([^,]),([wn]+))");
        string line;
        while (getline(file, line)) {
            smatch matches;
            if (regex_match(line, matches, pattern)) {
                char ascii = matches[1].str()[0];
                string barcode = matches[2];
                string binary = toBinary(barcode);
                tuple<char, string, string> bc(ascii, barcode, binary);
                this->insert(bc, string(1, ascii));
            }
        }
    }

    void print() const {
        for (auto& node : *this) {
            cout << get<0>(node) << "," << get<1>(node) << "," << get<2>(node) << endl;
        }
    }
    
    
private:

    static string toBinary(const string& barcode) {
        string result;
        for (char c : barcode) {
            if (c == 'w') result += "1";
            else result += "0";
        }
        return result;
    }

};

#endif


// int main() {
//     Barcode bc("BC3of9.csv");
//     bc.print();
// }
