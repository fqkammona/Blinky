#include <iostream>
#include <vector>
#include <mutex>
#include "Master.h"
using namespace std;

vector<int> buffer;
mutex bufferMutex;

int main() {
    run();

    // Print out the buffer
    cout << "Buffer: ";
    for (auto i : buffer) {
        cout << i << " ";
    }
    cout << std::endl;

    return 0;
}