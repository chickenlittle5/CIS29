#ifndef BARCODE_COOKIE_JAR
#define BARCODE_COOKIE_JAR

#include <mutex>
#include <condition_variable>
#include <queue>
#include "ProductMap.h"

class BarcodeCookieJar {

public:
    BarcodeCookieJar(ProductMap& products) : productMap(products) {}

    void addBarcode(const string& barcode) {
        unique_lock<mutex> lock(queueMutex);
        barcodeQueue.push(barcode);
        queueCV.notify_one();
    }

    bool getBarcode(string& barcode) {
        unique_lock<mutex> lock(queueMutex);
        queueCV.wait(lock, [this]() { return !barcodeQueue.empty() || done; });

        if (!barcodeQueue.empty()) {
            barcode = barcodeQueue.front();
            barcodeQueue.pop();
            return true;
        }
        return false;
    }

    shared_ptr<Product> lookupProduct(const string& barcode) {
        unique_lock<mutex> lock(productMutex);
        return productMap[barcode];
    }

    void markDone() {
        unique_lock<mutex> lock(queueMutex);
        done = true;
        queueCV.notify_all();
    }


private:
    queue<string> barcodeQueue;
    mutex queueMutex;
    condition_variable queueCV;
    ProductMap& productMap;
    mutex productMutex;
    bool done = false;

};


#endif