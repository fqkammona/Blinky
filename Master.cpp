//
// Created by Fatima Kammona on 5/21/23.
//

#include "Master.h"
#include <thread>
#include "slave.h"
using namespace std;

void run() {
    vector<thread> threads;

    // Master thread creates 10 slave threads
    for (int i = 0; i < 10; ++i) {
        threads.push_back(thread(Slave, i));   // Create a new thread that runs slave()
    }

    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }
}
