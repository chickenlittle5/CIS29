#include "BarcodeCookieJar.h"
#include "Cart.h"
#include <thread>

class Consumer {

public:
    Consumer(Cart& c, BarcodeCookieJar& j) :
        cart(c), jar(j) {}

    void operator()() {
        for (const auto& product : cart.getProducts()) {
            string barcode = product->getBinary();
            cout << "Barcode Reader: Scanned " << barcode << "\n";
            jar.addBarcode(barcode);
            this_thread::sleep_for(chrono::milliseconds(50)); // time to scan item
        }
    }

private:
    Cart& cart;
    BarcodeCookieJar& jar;

};