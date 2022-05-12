#include <iostream>
#include <vector>
#include <climits>

/**
 * Recapitulat de aici: https://www.geeksforgeeks.org/binary-heap/
 */

using namespace std;

vector<int> heap;

ostream &operator<<(ostream &out, vector<int> v) {
    for (auto x: v) {
        out << x << " ";
    }
    out << "\n";

    return out;
}

inline int parent(int &i){
    return i / 2;
}

inline int leftChild(int &i){
    return 2 * i + 1;
}

inline int rightChild(int &i){
    return 2 * i + 2;
}

void heapify(vector<int> &v){
    for(int &x: v){
        if(heap.size() == 0){
            heap.push_back(INT_MIN);
            heap.push_back(x);
        } else {
            heap.push_back(x);
            int i = heap.size() - 1;

            while(i != 0 && heap[parent(i)] > heap[i]){
                swap(heap[i], heap[parent(i)]);
                i = parent(i);
            }
        }
    }
}

int extractMin(){
    if(heap.size() == 0)
        return INT_MAX;

    if(heap.size() == 1){
        int result = heap[0];
        heap.pop_back();
        return result;
    }

    int root = heap[1];
    heap[1] = heap[heap.size() - 1];
    vector<int> v;
    for(int i = 1; i < heap.size(); ++i){
        v.push_back(heap[i]);
    }
    heap.clear();
    heapify(v);

    return root;
}

int main() {
    vector<int> v = {10,20,30,40,50,25};

    heapify(v);

    cout << heap;

    cout << extractMin() << "\n";
    cout << extractMin() << "\n";
    cout << extractMin() << "\n";
    cout << extractMin() << "\n";
    cout << extractMin() << "\n";
    cout << extractMin() << "\n";
    cout << extractMin() << "\n";

    return 0;
}