//
// Created by Fatima Kammona on 5/21/23.
//

#include "Slave.h"
#include <iostream>
#include <mutex>
using namespace std;

extern vector<int> buffer;
extern mutex bufferMutex;

void Slave(int id) {
    lock_guard<mutex> lock(bufferMutex);  // Automatically locks the mutex
    buffer.push_back(id);                          // Write to the buffer
    cout << "Slave " << id << " has written to buffer." << endl;
    // Mutex is automatically released when lock goes out of scope
}