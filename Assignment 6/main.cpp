#include "Carts.cpp"


int main() {
    try {
        Barcode barcodes("BC3of9.csv");
        ProductMap products("Products.csv", barcodes);
        Carts carts("Carts.csv", products);
        carts.printCarts();
    } catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
        return 1;
    }

    return 0;
}