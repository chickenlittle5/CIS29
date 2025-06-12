#ifndef NODE_HIERARCHY
#define NODE_HIERARCHY

#include <iostream>
#include <memory>
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


class NodeBase {
public:
    virtual ~NodeBase() = default;
    virtual float freq() const = 0;
    virtual string symbol() const = 0;
};


class Branch : public NodeBase {
public:
    Branch(shared_ptr<NodeBase> n0 = nullptr, shared_ptr<NodeBase> n1 = nullptr) :
        left_(n0), right_(n1) {}
    float freq() const override { return left_->freq() + right_->freq(); }
    string symbol() const override { return left_->symbol() + right_->symbol(); }
    shared_ptr<NodeBase> left() { return left_; }
    shared_ptr<NodeBase> right() { return right_; }
private:
    shared_ptr<NodeBase> left_;
    shared_ptr<NodeBase> right_;
};


class Leaf: public NodeBase {
public:
    Leaf(float f, const string& s) :
        freq_(f), symbol_(s) {}
    float freq() const override { return freq_; }
    string symbol() const override { return symbol_; }
private:
    float freq_;
    string symbol_;
};

#endif