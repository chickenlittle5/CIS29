#include "Carts.cpp"


int main() {
    Barcode barcodes("BC3of9.csv");
    ProductMap products("Products.csv", barcodes);
    Carts carts("Carts.csv", products);
    carts.printCarts();

    return 0;
}