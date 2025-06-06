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
            throw runtime_error("Error opening csv file");
        }

        string line;
        getline(file, line); // Skips first line
        // read 2 characters 0-9 or A-f and then whatever is left
        regex pattern(R"(^([0-9A-F]+),(.*)$)"); 
        // regex pattern(R"(^(.),(.*)$)"); 
        while (getline(file, line)) {
            smatch matches;
            if (regex_match(line, matches, pattern)) {
                string symbol = convertHex(matches[1]);
                // string symbol = matches[1];
                float freq = stof(matches[2]);
                auto leaf = make_shared<Leaf>(freq, symbol);
                // creates a min heap of leafs based on freq
                HF.insert(freq, leaf);
            }
        }

    }

    // self explanatory
    string convertHex(const string& hex) {
        int decimal = stoi(hex, nullptr, 16);
        if (decimal < 0 || decimal > 127) 
            throw runtime_error("Invalid ASCII range");
        char c = decimal;
        return string(1, c);
    }

    /*
    qtree algo. turns the minheap HF into one single branch with all
    the nodes which includes symbol and frequency
    returns the root bc theres only one node
    */
    shared_ptr<NodeBase> QTree() {
        // loops until only one nodeBase
        while (HF.size() > 1) {
            // combines the 2 smallest freq nodes
            auto left = HF.extractMin()->getValue();
            auto right = HF.extractMin()->getValue();
            // make a branch from the
            auto branch = make_shared<Branch>(left, right);
            // inserts back into HF as a branch
            HF.insert(branch->freq(), branch);
        }
        return HF.extractMin()->getValue();
    }

    // recursive function to add bittrails to mkv
    void BitTrail(shared_ptr<NodeBase> node, const string& trail) {
        // checks if its a node is a branch
        if (auto branch = dynamic_pointer_cast<Branch>(node)) {
            // check left recursively and add a '0' to trail
            BitTrail(branch->left(), trail + "0");
            // check right recursively and add a '1' to trail
            BitTrail(branch->right(), trail + "1");
            // if not branch, check if leaf
        } else if (auto leaf = dynamic_pointer_cast<Leaf>(node)) {
            char symbol = leaf->symbol()[0];
            // add node with trail and symbol 
            auto bitNode = make_shared<Node<string, char>>(trail, symbol);
            bitTrails.insert(bitNode, leaf->symbol());
        } else {
            throw runtime_error("Invalid node type");
        }
    }

    void sortBitTrails() {
        sort(bitTrails.begin(), bitTrails.end(), [](const auto& a, const auto& b) {
            const string& strA = a->getKey();
            const string& strB = b->getKey();
            if (strA.size() != strB.size()) 
                return strA.size() > strB.size();
            return strA > strB;
        });

    }

    void printBitTrails() {
        for (int i = 0; i < bitTrails.size(); i++) {
            cout << "Encoding[" << i << "]: " << *bitTrails[i] << endl;
        }
        cout << "Encoding[c]: " << *bitTrails["c"] << endl;
        cout << "Encoding[<]: " << *bitTrails["<"] << endl;
        cout << "Encoding[94]: " << *bitTrails[94] << endl;
    }

    void printHeap() {
        HF.printHeap();
    }

    void readTextFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Error opening text file");
        }
        ofstream out;
        out.open("output.txt");
        if (!out.is_open()) {
            throw runtime_error("Error opening output file");
        }
        string line;
        while (getline(file, line)) {
            for (char c : line) {
                auto trail = bitTrails[string(1, c)]->getKey();
                out << trail;
            }
            out << endl;
        }
        
    }

    void decodeBitTrails(const string& filename) {
        string decode = "";
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Error opening bitTrail file");
        }
        string line;
        while (getline(file, line)) {
            for (char c : line) {

            }
        }
    }

private:
    MinHeap<float, shared_ptr<NodeBase>> HF;
    MultiKeyVector<shared_ptr<Node<string, char>>> bitTrails;
};

int main() {

    HeapTree ht;
    // ht.readFromCSV("MississippiFreq.csv");
    ht.readFromCSV("HFrequencies.csv");
    auto QTree = ht.QTree();
    ht.printHeap();
    cout << QTree->symbol();
    ht.BitTrail(QTree, "");
    // ht.sortBitTrails();
    ht.printBitTrails();
    ht.readTextFile("Mississippi.txt");

    return 0;
}