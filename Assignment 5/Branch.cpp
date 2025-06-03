#include "Node.cpp"

template <typename K, typename V>
class Branch : public Node<K, V> {
public: 
    Branch(Node* n0, Node* n1) :
        

    double freq() {
        return left_.freq() + right_.freq();
    }

    string symbol() {
        return left.symbol()
    }

private:
    Node* left_;
    Node* right_;
};