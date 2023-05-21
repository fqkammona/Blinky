//
// Created by Fatima Kammona on 5/21/23.
//

#include <thread>
#include <queue>
#include "Slave.h"
#include "Master.h"
using namespace std;

void run() {
    vector<thread> threads;

    // Master thread creates 20 slave threads
    for (int i = 0; i < 20; ++i) {
        threads.push_back(thread(Slave, i));   // Create a new thread that runs slave()
    }

    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }
}
