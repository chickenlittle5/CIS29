#ifndef PRODUCT
#define PRODUCT

#include <string>
using namespace std;

class Product {

public:
    Product(string n, double p, string b) :
        name_(n), price_(p), binary_(b) {}

    string getName() { return name_; };
    double getPrice() { return price_;}
    string getBinary() { return binary_; }

    void setName(string n) { name_ = n; }
    void setPrice(double p) { price_ = p; }
    void setBinary(string b) { binary_ = b; }

private:
    string name_;
    double price_;
    string binary_;
};

#endif