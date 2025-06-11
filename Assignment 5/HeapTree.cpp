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
        if (root_) {
            // tree has already been built, return existing root
            return root_;
        }
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
        root_ = HF.extractMin()->getValue();
        return root_;
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

    /*
    sorts the bittrails mkv
    it lwky messes everything up cuz it reindexes the mkv and the mappings dont change with it
    */
    void sortBitTrails() {
        sort(bitTrails.begin(), bitTrails.end(), [](const auto& a, const auto& b) {
            const string& strA = a->getKey();
            const string& strB = b->getKey();
            if (strA.size() != strB.size()) 
                return strA.size() > strB.size();
            return strA > strB;
        });
        int index = 0;
        for (const auto& node : bitTrails) {
            char symbol = node->getValue();
            bitTrails.setStringIndex(string(1, symbol), index++);
        }
    }

    // prints the bit trails
    void printBitTrails() {
        for (int i = 0; i < bitTrails.size(); i++) {
            cout << "Encoding[" << i << "]: " << *bitTrails[i] << endl;
        }
        // cout << "Encoding[c]: " << *bitTrails["M"] << endl;
        // cout << "Encoding[<]: " << *bitTrails["<"] << endl;
        // cout << "Encoding[94]: " << *bitTrails[94] << endl;
    }

    // prints minheap
    void printHeap() {
        HF.printHeap();
    }

    // reads text file, retrieves bittrail, and writes to output.txt
    void readTextFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) throw runtime_error("Error opening text file");

        ofstream out;
        out.open("encoded.txt");
        if (!out.is_open()) {
            throw runtime_error("Error opening output file");
        }
        string line;
        while (getline(file, line)) {
            for (char c : line) {
                auto trail = bitTrails[string(1, c)]->getKey();
                out << trail << " ";
            }
            out << endl;
        }
        file.close();
        out.close();
    }

    /*
    reads bittrail and decodes it by traversing the root/qtree.
    using regex is unreasonable bc u need to get each character and not a pattern.
    using mkv bitTrails is also unreasonable bc u alr traversing the qtree. also there 
    is no mapping for the bittrail and only the character
    */
    void decodeBitTrails(const string& filename) {
        // reads file
        ifstream file(filename);
        if (!file.is_open()) throw runtime_error("Error opening bitTrail file");
        ofstream out;
        out.open("decoded.txt");
        if (!out.is_open()) {
            throw runtime_error("Error opening output file");
        }

        string line;
        while (getline(file, line)) {
            // grabs root into node
            // auto node = root_;
            // for (char c : line) {
            //     // if node is a branch
            //     if (auto branch = dynamic_pointer_cast<Branch>(node)) {
            //         // if c is 0 then go left, if 1 then go right
            //         if (c == '0') node = branch->left();
            //         else if (c == '1') node = branch->right();
            //         else throw runtime_error("Invalid character in bittrail: " + string(1, c));
            //     }
            //     if (auto leaf = dynamic_pointer_cast<Leaf>(node)) {
            //         cout << leaf->symbol();
            //         node = root_;
            //     }
            // }
            // cout << endl;
            for (int i = 0; i < bitTrails.size(); i++) {
                auto node = bitTrails[i];
                string bitTrail = node->getKey();
                string symbol(1, node->getValue());
                
                line = regex_replace(line, regex(bitTrail + " "), symbol);
                // cout << "Iteration[" << i << "]" << line << endl;
            }
            out << line << endl;
        }
    }

private:
    MinHeap<float, shared_ptr<NodeBase>> HF;
    MultiKeyVector<shared_ptr<Node<string, char>>> bitTrails;
    shared_ptr<NodeBase> root_;
};

void validateHeapTree() {
    cout << "\n-------Testing HeapTree functions-------\n";
    string csvFile = "HFrequencies.csv";
    string textFile = "test.txt";
    string bitTrail = "encoded.txt";
    string output = "decoded.txt";

    cout << "Creating HeapTree and reading csv file......";
    HeapTree ht;
    ht.readFromCSV(csvFile);
    cout << "Successfully read csv file" << endl;

    cout << "Creating QTree......";
    auto root = ht.QTree();
    cout << "Success" << endl;

    cout << "\n----Current heap----\n" << root->symbol() << endl;

    cout << "Creating bit trails......";
    ht.BitTrail(root, "");
    cout << "Success" << endl;

    cout << "Soriting bit trails......";
    ht.sortBitTrails();
    cout << "Success" << endl;

    cout << "\n----BitTrail mappings----" << endl;
    ht.printBitTrails();

    cout << "\n----Reading files----" << endl;
    cout << "Reading text file: " << textFile << "......";
    ht.readTextFile(textFile);
    cout << "Success\n" << endl;

    cout << "Decoding file: " << bitTrail << " to " << output << "......" << endl;
    ht.decodeBitTrails(bitTrail);
    cout << "Success\n" << endl;
}

int main() {
    validateHeapTree();
    return 0;
}