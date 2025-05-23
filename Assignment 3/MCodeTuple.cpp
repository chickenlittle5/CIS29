#include <tuple>
#include <string>
#include <iostream>
using namespace std;

class MCodeTuple {
public:
    MCodeTuple(string ascii = "", string mCode = "", string bits = "00")
        : mCode_(ascii, mCode, bits) {}

    string getAscii() const { return get<0>(mCode_); }
    string getMCode() const { return get<1>(mCode_); }
    string getBits() const { return get<2>(mCode_); }

    void setAscii(char ascii) { get<0>(mCode_) = ascii; }
    void setMCode(string mCode) { get<1>(mCode_) = mCode; }
    void setBits(string bits) { get<2>(mCode_) = bits; }

    void print() const {
        cout << getAscii() << "," << getMCode() << "," << getBits() << endl;
    }

private:
    tuple<string, string, string> mCode_;
};

int main() {
    return 0;
}