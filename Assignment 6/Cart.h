#ifndef CART
#define CART

#include "ProductMap.h"
#include <iostream>
#include <iomanip>

class Cart {

public:

    void addProduct(shared_ptr<Product> product) {
        cart_.push_back(product);
    }

    void printReceipt() const {
        cout << "----------------------------------" << endl;
        double total = 0;
        for (const auto& prod : cart_) {
            string name = prod->getName();
            double price = prod->getPrice();
            cout << left << setw(27) << name 
                << right << "$" << setw(6) << fixed << setprecision(2) << price << endl;
            total += price;
        }
        cout << "----------------------------------" << endl;
        cout << left << setw(27) << "Total Price:" 
            << right << "$" << setw(6) << fixed << setprecision(2) << total << endl;
    }

    const vector<shared_ptr<Product>> getProducts() {
        return cart_;
    }


private:
    vector<shared_ptr<Product>> cart_;

};

#endif