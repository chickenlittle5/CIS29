#ifndef CART
#define CART

#include "ProductMap.cpp"
#include <iostream>
#include <iomanip>

class Cart {

public:

    void addProduct(shared_ptr<Product> product) {
        cart_.push_back(product);
    }

    void printReceipt() {
        cout << "----------------------------------" << endl;
        double total = 0;
        for (const auto& prod : cart_) {
            cout << left << setw(10) << prod->getName() << " - $" << fixed << setprecision(2) << prod->getPrice() << endl;
            total += prod->getPrice();
        }
        cout << "----------------------------------" << endl;
        cout << "Total Price: $" << fixed << setprecision(2) << total << endl;
    }


private:
    vector<shared_ptr<Product>> cart_;

};

#endif