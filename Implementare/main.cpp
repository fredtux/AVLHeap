#include <iostream>
#include <vector>

using namespace std;

ostream &operator<<(ostream &out, vector<int> v) {
    for (auto x: v) {
        out << x << " ";
    }
    out << "\n";

    return out;
}

int main() {

    return 0;
}