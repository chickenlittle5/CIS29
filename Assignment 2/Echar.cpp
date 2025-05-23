#include <bitset>
#include <tuple>
#include <string>
#include <iostream>
using namespace std;

class Echar {
public:
    Echar(string ascii, string ebcdic, string hex, bitset<12> bits = bitset<12>()) 
        : echar_(ascii, ebcdic, hex, bits) {
            fromHex();
        }

    

    Echar() 
        : echar_(" ", "", "", bitset<12>()) {}

    string getAscii() const { return get<0>(echar_); }
    string getEbdic() const { return get<1>(echar_); }
    string getHex() const { return get<2>(echar_); }
    bitset<12> getBits() const { return get <3>(echar_); }

    void setAscii(string ascii) { get<0>(echar_) = ascii; }
    void setEbdic(string ebdic) { get<1>(echar_) = ebdic; }
    void setHex(string hex) { get<2>(echar_) = hex; }
    void setBits(bitset<12> bits) { get<3>(echar_) = bits; }

    void print() {
        cout << getAscii() << "," << getEbdic() << "," << getHex() << endl;
    }

    void fromHex() {
        for (char c : getHex()) {
            int bitPos = isdigit(c) ? (c - '0') : (toupper(c) - 'A' + 10);
            get<3>(echar_).set(bitPos);
        }
    }

    void printBits() {
        cout << get<3>(echar_) << endl;
    }

private:
    tuple<string, string, string, bitset<12>> echar_;

};

// int main() {
//     Echar echar("Z", "09", "05a");
//     echar.fromHex();
//     echar.printBits();

//     return 0;
// }