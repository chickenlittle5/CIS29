#include "BarcodeCookieJar.h"
#include <thread>

class Producer {

public:
    Producer(BarcodeCookieJar& j) :
        jar(j){}
    
    void operator()() {
        string barcode;
        while (jar.getBarcode(barcode)) {
            shared_ptr<Product> product = jar.lookupProduct(barcode);
            if (product) {
                cout << "Barcode Server: Found " << product->getName() << " - $" << product->getPrice() << "\n";
            } else {
                cout << "Barcode Server: Product not found for barcode: " << barcode << endl;
            }
            this_thread::sleep_for(chrono::milliseconds(80)); // time to find item
        }
        cout << "ALL barcode processed!" << endl;
    }

private:
    BarcodeCookieJar& jar;

};