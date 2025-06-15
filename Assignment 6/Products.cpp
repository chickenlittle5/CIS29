#include "Barcodes.cpp"
#include "Product.h"

class Products : public MultiKeyVector<shared_ptr<Product>>{

public:
    void loadFromCSV(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Could not open Product file: " + filename);
        }


        
        /*
        (^([^,]+)   =   start with anything that is not a comma and also one or more
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
        getline(file, line); // skip heading line
        while (getline(file, line)) {

        }

    }


private:

    static string toBinary(const string& name) {
        for (int i = 0; i < 5; i++) {

        }
    }

};