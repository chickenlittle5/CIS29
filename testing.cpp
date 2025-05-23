#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {5, 1, 3};
    make_heap(v.begin(), v.end(), [](int a, int b) {
        return a > b; // makes a min-heap
    });
    cout << "Min-heap: ";  // Will be 1 — the smallest
    for (int e : v) {
        cout << e << " ";
    }
    cout << endl;

    make_heap(v.begin(), v.end(), [](int a, int b) {
        return a < b; // makes a max-heap
    });
    cout << "Max-heap: ";  // Will be 1 — the smallest
    for (int e : v) {
        cout << e << " ";
    }
    cout << endl;
    

}