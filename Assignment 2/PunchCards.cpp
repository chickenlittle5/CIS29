#include "Echars.cpp"

class PunchCards {
public:
    PunchCards() {}
    
    void readPunchCards(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Could not open file");
        }

        vector<string> lines;
        string line;
        while (getline(file, line)) {
            if (line.find('-') == string::npos) {
                lines.push_back(line);
            }
        }

        file.close();

        const int numBits = 12;
        numBlocks = lines.size() / numBits;
        punchcards_.resize(lines.size() / numBits);

        for (int block = 0; block < numBlocks; block++) {
            int startRow = block * numBits;
            for (int col = 0; col < lines[0].size(); col++) {
                bitset<numBits> bits;
                for (int row = 0; row < numBits; row++) {
                    if (lines[startRow + row][col] == '1') {
                        bits.set(row);
                    }
                }
                punchcards_[block].push_back(bits);
            }
        }

    }

    vector<bitset<12>> getBlock(int block) const { return punchcards_[block]; }
    int getNumBlocks() const { return numBlocks; }

    void printPunchcards(Echars& echars) const {
        for (int i = 0; i < numBlocks; i++) {
            for (bitset<12> bits : getBlock(i)) {
                string ascii = echars[bits.to_string()].getAscii();
                cout << ascii;
            }
            cout << endl;
        }
    }


private:
    vector<vector<bitset<12>>> punchcards_;
    int numBlocks;

};

int main() {

    Echars echars;
    echars.readFromCSV("Tuple.csv");
    PunchCards punchcards;
    punchcards.readPunchCards("PumchCards.txt");
    punchcards.printPunchcards(echars);
    // cout << punchcards.getBlock(1)[0];

    

    return 0;
}
