#include <vector>
#include <tuple>
#include <iostream>
#include <string>
using namespace std;

template <typename T>
class MultiKeyVector : public vector<T> {

public:
    MultiKeyVector(T defaultValue = T()) 
        : defaultValue_(defaultValue) {}

    void setStringIndex(const string& key, int index) {
        if (index < 0) {
            throw out_of_range("Negative Index");
        }
        if (index >= this->size()) {
            this->resize(index + 1, defaultValue_);
        }
        
        for (auto& node : mapping_) {
            if (get<0>(node) == key) {
                get<1>(node) = index;
                return;
            }
        }
        mapping_.push_back(make_tuple(key, index));
    }

    T& operator[](int index) {
        if (index < 0) {
            throw out_of_range("Negative Index");
        }
        if (index >= this->size()) {
            this->resize(index + 1, defaultValue_);
        }
        return vector<T>::operator[](index);
    }

    T& operator[](const string& key) {
        for (auto& node : mapping_) {
            if (get<0>(node) == key) {
                int index = get<1>(node);
                if (index >= this->size()) {
                    this->resize(index + 1, defaultValue_);
                }
                return this->at(index);
            }
        }
        return defaultValue_;
    }


private:
    T defaultValue_;
    vector<tuple<string, int>> mapping_;

};



int main() {
    try {
        // MultiKeyVector<int> intVec(0);
        // intVec.push_back(4);
        // intVec.push_back(2);
        // intVec.push_back(9);
        // intVec.setStringIndex("first", 0);
        // intVec.setStringIndex("second", 1);
        // intVec.setStringIndex("third", 2);
        // cout << "Element at index 1: " << intVec[1] << endl;
        // cout << "Element at 'first': " << intVec["first"] << endl;
        // cout << "Element at 'second': " << intVec["second"] << endl;
        // cout << "Element at 'third': " << intVec["third"] << endl;
        // cout << "Element at 'fourth': " << intVec["fourth"] << endl << endl;

        // MultiKeyVector<string> strVec("nothing");
        // strVec.push_back("Hello!");
        // strVec.push_back("My name is Ethan.");
        // strVec.push_back("Goodbye!");
        // strVec.setStringIndex("greeting", 0);
        // strVec.setStringIndex("introduction", 1);
        // strVec.setStringIndex("farewell", 2);
        // cout << "Element at index 0: " << strVec[0] << endl;
        // cout << "Element at 'greeting': " << strVec["greeting"] << endl;
        // cout << "Element at 'introduction': " << strVec["introduction"] << endl;
        // cout << "Element at 'farewell': " << strVec["farewell"] << endl;
        // cout << "Element at 'not found': " << strVec["not found"] << endl;

        // MultiKeyVector<double> dmk(100);
        // double dvalue = 100;
        // for (int i = 0; i < 10; i++)
        //     dmk.push_back(dvalue++);
        // dmk[50] = 5050.50;
        // cout << dmk[50] << endl;
        // cout << dmk["test value"] << endl;
        // for (int j = 0; j < dmk.size(); j++)
        //     cout << dmk[j] << endl;
        MultiKeyVector<tuple<string,int>> mintstr(make_tuple("hundred", 100));
        mintstr[50] = make_tuple("fifty", 50);
        mintstr["abc"] = make_tuple("Hello", 1);
        cout << "Element at index 50: (" << get<0>(mintstr[50]) << ", " << get<1>(mintstr[50]) << ")" << endl;
        cout << "Element at 'abc': (" << get<0>(mintstr["abc"]) << ", " << get<1>(mintstr["abc"]) << ")" << endl;
    } catch (exception e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}