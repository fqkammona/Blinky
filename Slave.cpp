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
extern int divisibleBy37Count;
extern mutex divisibleBy37CountMutex;

void Slave(int id) {
    while (true) {
        queueMutex.lock();   // Lock access to the queue
        if (numberQueue.empty()) {
            queueMutex.unlock(); // Unlock access to the queue
            break;
        }
        int number = numberQueue.front();
        numberQueue.pop();
        queueMutex.unlock(); // Unlock access to the queue

        lock_guard<mutex> lock(bufferMutex);  // Automatically locks the mutex
        buffer.push_back(number);                          // Write to the buffer

        // Check if the number is divisible by 37
        if (number % 37 == 0) {
            cout << "Slave " << id << " found a number divisible by 37: " << number << endl;
            lock_guard<mutex> lock(divisibleBy37CountMutex); // Lock access to the counter
            ++divisibleBy37Count;
        }
    }
}