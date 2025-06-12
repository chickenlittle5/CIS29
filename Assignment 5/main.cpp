#include "HeapTree.cpp"
#include "HeapTreeV2.cpp"
#include <chrono>


int main() {
    auto start = chrono::high_resolution_clock::now();
    validateHeapTree();
    auto end = chrono::high_resolution_clock::now();
    auto mkvTime = chrono::duration_cast<chrono::nanoseconds>(end-start);

    start = chrono::high_resolution_clock::now();
    validateHeapTreeV2();
    end = chrono::high_resolution_clock::now();
    auto unmapTime = chrono::duration_cast<chrono::nanoseconds>(end-start);

    cout << "Timer for MKV: " << mkvTime.count() << endl;
    cout << "Timer for unordered_map: " << unmapTime.count() << endl;
    string faster = (mkvTime.count() > unmapTime.count()) ? "unordered_map" : "mkv";
    cout << "This one is faster: " << faster;
}