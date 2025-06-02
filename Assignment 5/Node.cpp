#include <iostream>
using namespace std;

template <typename K, typename V>
class Node {

public:
    Node(K key = K(), V value = V()) : 
        key_(key), value_(value) {}

    Node(const Node& other) : 
        key_(other.key_), value_(other.value) {}

    Node(Node&& other) noexcept :
        key_(move(other.key_)), value_(move(other.key)) {}

    K getKey() const { return key_; }
    V getValue() const { return value_; }
    void setKey(const K& key) { key_ = key; }
    void setValue(const V& value) { value_ = value; }

    bool operator<(const Node& other) const { return this->key_ < other.key_; }
    bool operator>(const Node& other) const { return this->key_ > other.key_; }
    
    friend ostream& operator<<(ostream& os, const Node& node) {
        os << "(" << node.key_ << ", " << node.value_ << ")";
        return os;
    }

private:
    K key_;
    V value_;
    
};