#include <vector>
#include <memory>
#include <algorithm>
#include "Node.cpp"
using namespace std;

template <typename K, typename V>
class MinHeap : public vector<shared_ptr<Node<K, V>>> {

public:
    void buildHeap() {
        make_heap(this->begin(), this->end(), minHeapComparator);
    }

    void insert(K key, V value) {
        auto node = make_shared<Node<K, V>>(key, value);
        this->push_back(node);
        push_heap(this->begin(), this->end(), minHeapComparator);
    }
    
    shared_ptr<Node<K, V>> extractMin() {
        pop_heap(this->begin(), this->end(), minHeapComparator);
        auto min = this->back();
        this->pop_back();
        return min;
    }

    void heapify(const vector<shared_ptr<Node<K, V>>>& elements) {
        this->clear();
        for (const auto& element : elements) {
            this->push_back(make_shared<Node<K, V>>(element->getKey(), element->getValue()));
        }
        buildHeap();
    }

    void printHeap() {
        cout << "[";
        for (const auto& node : *this) {
            cout << *node << " ";
        }
        cout << "]" << endl;
    }

    void pop() {
        
    }

private:
    // since its the same comparator for all i used a function
    static bool minHeapComparator(const shared_ptr<Node<K, V>>& a, const shared_ptr<Node<K, V>>& b) {
        return *a > *b;
    }

};


void validateMixedHeap() {
    cout << "\n--- Validation Test: Mixed Key-Value Types ---\n";

    // Test 1: MinHeap with int keys and string values
    MinHeap<int, string> intStringHeap;
    intStringHeap.insert(10, "Ten");
    intStringHeap.insert(5, "Five");
    intStringHeap.insert(20, "Twenty");
    intStringHeap.insert(1, "One");
    cout << "Int-String MinHeap after insertions: ";
    intStringHeap.printHeap();
    cout << boolalpha << is_heap(intStringHeap.begin(),intStringHeap.end(), 
        [](const auto& a, const auto& b) {
            return *a > *b;
        }) << endl;
    // added lambda function comparator to check for minheap instead of maxheap
    auto minIntStringNode = intStringHeap.extractMin();
    cout << "Extracted Min (Int-String): " << *minIntStringNode << endl;

    // Test 2: MinHeap with string keys and double values
    MinHeap<string, double> stringDoubleHeap;
    stringDoubleHeap.insert("apple", 2.5);
    stringDoubleHeap.insert("banana", 3.8);
    stringDoubleHeap.insert("cherry", 1.2);
    stringDoubleHeap.insert("date", 4.7);
    cout << "\nString-Double MinHeap after insertions: ";
    stringDoubleHeap.printHeap();    
    cout << boolalpha << is_heap(stringDoubleHeap.begin(),stringDoubleHeap.end(), 
        [](const auto& a, const auto& b) {
            return *a > *b;
        }) << endl;
    auto minStringDoubleNode = stringDoubleHeap.extractMin();
    cout << "Extracted Min (String-Double): " << *minStringDoubleNode << endl;

    // Test 3: MinHeap with double keys and int values
    MinHeap<double, int> doubleIntHeap;
    doubleIntHeap.insert(10.5, 100);
    doubleIntHeap.insert(5.2, 50);
    doubleIntHeap.insert(20.8, 200);
    doubleIntHeap.insert(1.1, 10);
    cout << "\nDouble-Int MinHeap after insertions: ";
    doubleIntHeap.printHeap();
    cout << boolalpha << is_heap(doubleIntHeap.begin(),doubleIntHeap.end(), 
        [](const auto& a, const auto& b) {
            return *a > *b;
        }) << endl;
    auto minDoubleIntNode = doubleIntHeap.extractMin();
    cout << "Extracted Min (Double-Int): " << *minDoubleIntNode << endl;

    // Test 4: Handling Mid-Vector Insertions ---\n";
    MinHeap<int, string> midheap;
    midheap.insert(10, "Ten");
    midheap.insert(5, "Five");
    midheap.insert(20, "Twenty");
    midheap.insert(1, "One");
    cout << "\nHeap after initial insertions: ";
    midheap.printHeap();
    // Insert a value in a non-end position
    midheap.insert(15, "Fifteen");  // Normally, push_heap would expect it at end()
    sort(midheap.begin(), midheap.end(), [](const shared_ptr<Node<int, string>>& a, const shared_ptr<Node<int, string>>& b) {
        return *a < *b;  // Ensure correct heap ordering
    });
    make_heap(midheap.begin(), midheap.end(), [](const shared_ptr<Node<int, string>>& a, const shared_ptr<Node<int, string>>& b) {
        return *a > *b;
    });
    cout << "Heap after mid-vector insertion (15, \"Fifteen\"): ";
    midheap.printHeap();
    auto minNode = midheap.extractMin();
    cout << "Extracted Min: " << *minNode << endl;
    cout << boolalpha << is_heap(midheap.begin(),midheap.end(), 
        [](const shared_ptr<Node<int, string>>& a, const shared_ptr<Node<int, string>>& b) {
            return *a > *b;
        }) << endl;

    // Test 5:  Add a test to validate the heapify() function
    vector<shared_ptr<Node<int, string>>> unsortedElements = {
        make_shared<Node<int, string>>(8, "Eight"),
        make_shared<Node<int, string>>(3, "Three"),
        make_shared<Node<int, string>>(10, "Ten"),
        make_shared<Node<int, string>>(1, "One"),
        make_shared<Node<int, string>>(6, "Six")
    };
    MinHeap<int, string> heapifiedHeap;
    heapifiedHeap.heapify(unsortedElements);
    cout << "\nHeap after heapify(): ";
    heapifiedHeap.printHeap();
    cout << boolalpha << is_heap(heapifiedHeap.begin(), heapifiedHeap.end(), 
        [](const auto& a, const auto& b) {
            return *a > *b;
        }) << endl;
    auto minNodeHeapify = heapifiedHeap.extractMin();
    cout << "Extracted Min after heapify: " << *minNodeHeapify << endl;


    cout << "--- Validation Completed ---\n";
}

// int main() {
//     validateMixedHeap();
//     return 0;
// }