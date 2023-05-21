#include <iostream>
#include <vector>
#include <mutex>
#include <queue>
#include "Master.h"
using namespace std;

vector<int> buffer;
mutex bufferMutex;
mutex queueMutex;
queue<int> numberQueue;
int divisibleBy37Count = 0;
mutex divisibleBy37CountMutex;

int main() {
    // Load up the queue with numbers 0-65534
    for (int i = 0; i <= 65534; ++i) {
        numberQueue.push(i);
    }

    run();

    cout << "Total numbers divisible by 37: " << divisibleBy37Count << endl;

    return 0;
}