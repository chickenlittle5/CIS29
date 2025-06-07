#include "MultiKeyVector.cpp"
#include "MCodeTuple.cpp"
#include <fstream>
#include <regex>

class MCodeDict {
public: 
    MCodeDict(const string& filename) {
        readMorseCSV(filename);
    }

    void readMorseCSV(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Error: could not open CSV file");
        }

        string line;
        getline(file, line);
        regex pattern(R"(^(.),(.*)$)");
        while (getline(file, line)) {
            smatch matches;
            if (regex_match(line, matches, pattern)) {
                string ascii = matches[1];
                string morse = matches[2];
                string bits = getBits(morse);
                MCodeTuple mCode(ascii, morse, bits);
                dict_.push_back(mCode);
                dict_.setStringIndex(bits, dict_.size() - 1);
            }
        }
    }

    
    string getBits(const string& mCode) {
        string bits = "";
        for (char c : mCode) {
            switch (c) {
            case '.':
                bits += "10";
                break;
            case '-':
                bits += "01";
                break;
            default:
                cerr << "Error not a '.' or '-'" << endl;
                break;
            }
        }
        return bits;
    }
    
    string readBinaryFile(const string& filename) {
        ifstream file(filename, ios::binary);
        if (!file.is_open()) {
            throw runtime_error("Error: could not open binary file");
        }
        string bits;
        char byte;
        while (file.read(&byte, 1)) {
            for (int i = 7; i >= 0; i--) {
                bits += ((byte >> i) & 1) ? '1' : '0';
            }
        }

        return bits;
    }
 
    string decodeBinaryMorse(const string& bits) {
        string output;
        string morseString;
        for (int i = 0; i < bits.size(); i+=2) {
            string chunk = bits.substr(i, 2);
            if (chunk == "10") {
                morseString += ".";
            } else if (chunk == "01") {
                morseString += "-";
            } else if (chunk == "00") {
                output += dict_[getBits(morseString)].getAscii();
                // output += morseString + " ";
                // cout << morseString << dict_[getBits(morseString)].getAscii() << endl;
                morseString.clear();
            } else if (chunk == "11") {
                output += " ";
            }
        }

        return output;
    }


    void print() {
        for (MCodeTuple mCode : dict_) {
            mCode.print();
        }
    }

    MultiKeyVector<MCodeTuple>& getDict() {
        return dict_;   
    }

private:
    MultiKeyVector<MCodeTuple> dict_;

};

// int main() {
//     MCodeDict MorseCodeDictionary("MCode.csv");
//     // MorseCodeDictionary.print();
//     // cout << MorseCodeDictionary.getDict()["1001"].getAscii() << endl;
//     string bits = MorseCodeDictionary.readBinaryFile("ascii_output.bin");
//     string decodedMessage = MorseCodeDictionary.decodeBinaryMorse(bits);
//     cout << decodedMessage << endl;
//     // cout << bits << endl;
}