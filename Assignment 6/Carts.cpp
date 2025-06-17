#include "Cart.h"

class Carts {

public:
    Carts() {}
    Carts(const string& filename, ProductMap& products) : 
        products_(products) {
            loadFromCSV(filename);
        }

    void loadFromCSV(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Could not open Carts file: " + filename);
        }

        regex pattern(R"([0-1]+)");
        string line;
        while (getline(file, line)) {
            Cart cart;
            // iterate through every patterned group
            sregex_iterator it(line.begin(), line.end(), pattern);
            sregex_iterator end;
            for (; it != end; it++) {
                string binary = (*it)[0];
                shared_ptr product = products_[binary];
                if (product) {
                    cart.addProduct(product);
                } else {
                    cerr << "WARNING: No product found for barcode: " << binary << endl;
                }
            }
            carts_.push_back(cart);     // add cart to carts
        }
    }

    void printCarts() {
        for (int i = 0; i < carts_.size(); i++) {
            cout << "Cart #" << i + 1 << endl;
            cout << left << setw(25) << "Item" << right << setw(9) << "Price" << endl; 
            carts_[i].printReceipt();
            cout << endl << endl;
        }
    }

private:
    vector<Cart> carts_;
    ProductMap products_;
};

// int main() {


// }