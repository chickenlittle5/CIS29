/*
Ethan Tran
20559495
5/14/25
*/

#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <string>
#include <optional>
using namespace std;

class HashTable {
public:

    HashTable(int size)
        : capacity_(size), count_(0), 
          intTable_(size), stringTable_(size) {}

    void insert(int key, const string& value = "\"default\"") {
        int index = hashFunction(key);
        auto& chain = intTable_[index];
        for (auto& node : chain) {
            if (get<0>(node) == key) {
                get<1>(node) = value;
                return;
            }
        }
        chain.emplace_back(key, value); // same as insert(make_tuple(key, value))
        count_++;
    }

    void insert(const string& key, int value = 0) {
        int index = hashFunction(key);
        auto& chain = stringTable_[index];
        for (auto& node : chain) {
            if (get<0>(node) == key) {
                get<1>(node) = value;
                return;
            }
        }
        chain.emplace_back(key, value);
        count_++;
    }

    const string* search(int key) const {
        int index = hashFunction(key);
        auto& chain = intTable_[index];
        for (auto& node : chain) {
            if (get<0>(node) == key) {
                return &get<1>(node);
            }
        }
        return nullptr;
    }
    
    const int* search(const string& key) const {
        int index = hashFunction(key);
        auto& chain = stringTable_[index];
        for (auto& node : chain) {
            if (get<0>(node) == key) {
                return &get<1>(node);
            }
        }
        return nullptr;
    }
    

    void erase(int key) {
        int index = hashFunction(key);
        auto& chain = intTable_[index];
        for (auto node = chain.begin(); node != chain.end(); node++) {
            if (get<0>(*node) == key) {
                chain.erase(node);
                count_--;
                return;
            }
        }
    }

    void erase(string key) {
        int index = hashFunction(key);
        auto& chain = stringTable_[index];
        for (auto node = chain.begin(); node != chain.end(); node++) {
            if (get<0>(*node) == key) {
                chain.erase(node);
                count_--;
                return;
            }
        }
    }

    void clear() {
        for (auto& chain : intTable_) chain.clear();
        for (auto& chain : stringTable_) chain.clear();
        count_ = 0;
    }

    int size() const { return capacity_; }

    void display() {
        cout << "Integer Table:" << endl;
        for (int i = 0; i < capacity_; i++) {
            cout << i << ": ";
            for (const auto& node : intTable_[i]) {
                cout << "(" << get<0>(node) << ", " << get<1>(node) << ") ";
            }
            cout << endl;
        }
        cout << "String Table:" << endl;
        for (int i = 0; i < capacity_; i++) {
            cout << i << ": ";
            for (const auto& node : stringTable_[i]) {
                cout << "(" << get<0>(node) << ", " << get<1>(node) << ") ";
            }
            cout << endl;
        }
    }

    auto begin(int key) {
        int index = hashFunction(key);
        return intTable_[index].begin();
    }
    auto begin(string key) {
        int index = hashFunction(key);
        return stringTable_[index].begin();
    }
    auto end(int key) {
        int index = hashFunction(key);
        return intTable_[index].end();
    }
    auto end(string key) {
        int index = hashFunction(key);
        return stringTable_[index].end();
    }

    int& operator[](string key) {
        int index = hashFunction(key);
        auto& chain = stringTable_[index];
        for (auto& node : chain) {
            if (get<0>(node) == key) {
                return get<1>(node);
            }
        }
        chain.emplace_back(key, 0);
        count_++;
        return get<1>(chain.back());
    }

    string& operator[](int key) {
        int index = hashFunction(key);
        auto& chain = intTable_[index];
        for (auto& node : chain) {
            if (get<0>(node) == key) {
                return get<1>(node);
            }
        }
        chain.emplace_back(key, "\"default\"");
        count_++;
        return get<1>(chain.back());
    }

private:
    int capacity_;
    int count_;
    vector<list<tuple<int, string>>> intTable_;
    vector<list<tuple<string, int>>> stringTable_;

    int hashFunction(int key) const {
        return abs(key) % capacity_;
    }

    int hashFunction(const string& key) const {
        int sum = 0;
        for (char c : key) {
            sum += c;
        }
        return sum % capacity_;
    }
};

bool test() 
{
    HashTable ht(10);
    // Insert using integer and string keys
    ht.insert(1, "apple");
    ht.insert(2); // Insert with default value
    ht.insert("banana", 100);
    ht.insert("cherry");
    // Insert colliding values to test linked lists
    ht.insert(11, "pear"); // Same bucket as 1
    ht.insert("orange", 200); // Same bucket as "banana"
    // ethans note: it doesnt collide with banana bc different ascii sums
    // Display hash table with table iterators
    ht.display();
    // Search function uses find_if to search
    cout << "Searching for key 2: ";
    auto result1 = ht.search(2);
    if (result1)
        cout << "(" << *result1 << ")\n";
    else
        cout << "Not Found\n";

    // Search for string key
    cout << "Searching for key 'banana': ";
    auto result2 = ht.search("banana");
    if (result2)
        cout << "(" << *result2 << ")\n";
    else
        cout << "Not Found\n";
    // Delete a colliding element and verify bucket remains intact
    ht.erase(11);
    ht.display();
    return true;

}

int main() {
    test();
    return 0;
}
