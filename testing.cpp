#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main() {
    string hex;
    cin >> hex;
    while (hex != " ") {
        int decimal = stoi(hex, nullptr, 16);
        char c = decimal;
        cout << c << endl;
        cin >> hex;
    }
}