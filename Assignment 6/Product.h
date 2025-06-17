#ifndef PRODUCT
#define PRODUCT

#include <string>
using namespace std;

class Product {

public:
    Product(string n, double p, string b) :
        name_(n), price_(p), binary_(b) {}

    const string getName() const { return name_; };
    double getPrice() const { return price_;}
    const string getBinary() const { return binary_; }

    void setName(const string& n) { name_ = n; }
    void setPrice(double p) { price_ = p; }
    void setBinary(const string& b) { binary_ = b; }

private:
    string name_;
    double price_;
    string binary_;
};

#endif