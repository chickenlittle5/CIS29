#include "Carts.cpp"
#include "BarcodeCookieJar.h"
#include "Consumer.cpp"
#include "Producer.cpp"
#include <thread>

int main() {
    try {
        auto start_time = chrono::high_resolution_clock::now();
        Barcode barcodes("BC3of9.csv");
        ProductMap products("Products.csv", barcodes);
        Carts carts("Carts.csv", products);
        BarcodeCookieJar jar(products);


        thread consumer1(Consumer(carts.getCart(0), ref(jar)));
        thread consumer2(Consumer(carts.getCart(1), ref(jar)));
        thread consumer3(Consumer(carts.getCart(2), ref(jar)));

        thread producer(Producer(ref(jar)));

        consumer1.join();
        consumer2.join();
        consumer3.join();
        jar.markDone();
        producer.join();
        auto duration = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start_time);
        cout << "Execution time: " << duration.count() << "ms" << endl;
    } catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
        return 1;
    }

    return 0;
}