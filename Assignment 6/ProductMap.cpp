#include "Barcodes.cpp"
#include "Product.h"

class ProductMap : public MultiKeyVector<shared_ptr<Product>>{

public:

    ProductMap() {}
    ProductMap(const string& filename, Barcode& barcode) :
        barcodes_(barcode) {
        loadFromCSV(filename);
    }
    
    void loadFromCSV(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Could not open Product file: " + filename);
        }
        
        /*
        my explaination of regex pattern
        ^([^,]+) start with anything that is not a comma and also one or more
        ([0-9]+(?:\.[0-9]{1,2})?)$)
        - [0-9]+    =   find anything 0-9 one or more
        - (?:\.[0-9]{1,2})?)$) 
            - ?: means non-capturing group
            - [0-9]{1, 2} find 1 or 2 instances of 0-9
            - the ? outside parentheses means the whole thing is optional
            - $ end of line
        */
        regex pattern(R"(^([^,]+),([0-9]+(?:\.[0-9]{1,2})?)$)");
        string line;
        getline(file, line); // skip first line
        while (getline(file, line)) {
            smatch matches;
            if (regex_match(line, matches, pattern)) {
                string name = matches[1];
                double price = stod(matches[2]);
                string binary = toBinary(name);
                shared_ptr<Product> product = make_shared<Product>(name, price, binary);
                this->insert(product, binary);
            }
        }
    }

    void print() const {
        for (auto& product : *this) {
            cout << product->getName() << "," << product->getPrice() << "," << product->getBinary() << endl;
        }
    }


private:
    Barcode barcodes_;
    string toBinary(const string& name) {
        string result;
        for (int i = 0; i < 5 && i < name.length(); i++) {
            char c = toupper(name[i]);
            result += get<2>(barcodes_[string(1, c)]);
        }
        return result;
    }
};

// int main() {

//     Barcode barcodes("BC3of9.csv");
//     ProductMap products("Products.csv", barcodes);
//     products.print();
// }
