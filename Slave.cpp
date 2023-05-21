//
// Created by Fatima Kammona on 5/21/23.
//

#include <iostream>
#include <queue>
#include <mutex>
#include "Slave.h"

using namespace std;

extern vector<int> buffer;
extern mutex bufferMutex;
extern mutex queueMutex;
extern queue<int> numberQueue;
extern int total_options_found;
extern mutex divisibleBy37CountMutex;

void Slave(int id) {
    while (true) {
        queueMutex.lock();   // Lock access to the queue
        if (numberQueue.empty()) {
            queueMutex.unlock(); // Unlock access to the queue
            break;
        }
        int count = numberQueue.front();
        numberQueue.pop();
        queueMutex.unlock(); // Unlock access to the queue

        lock_guard<mutex> lock(bufferMutex);  // Automatically locks the mutex
        buffer.push_back(count);                          // Write to the buffer

        delayLong(count, id);

        /*for (int i = 0; i <= 256; ++i) {
            delayLong(count, id, i);
        }*/
    }
}

void delayLong(int count, int id){
    if (count % 37 == 0) {
        cout << "Slave " << id << " found a number divisible by 37: " << count << endl;
        lock_guard<mutex> lock(divisibleBy37CountMutex); // Lock access to the counter
        ++total_options_found;
    }
}

