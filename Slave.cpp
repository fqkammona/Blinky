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

extern double ideal_Cycles;
extern double range_of_cycles;

int cycle = 0;
std::vector<Data> dataVector; // Define dataVector

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

        for (int i = 0; i <= 256; ++i) {
            delayLong(count, i);

            if(cycle == ideal_Cycles){
                cout << "Slave " << id << " found count: " << count
                << " r29: " << i << " Cycle: " << cycle << endl;
                cout << "FOUND FOUND FOUND" << endl;

                // Store count, cycle and r29 in a Data instance and add it to the vector
                Data data = {count, cycle, i};
                dataVector.push_back(data);

                lock_guard<mutex> lock(divisibleBy37CountMutex); // Lock access to the counter
                ++total_options_found;
            }
        }
    }

}

void delayLong(int tempCount, int r29Temp){
    int count = tempCount;
    cycle = 12;

    while (count > 0) {
        int r29 = r29Temp;
        cycle = cycle + 1;

        /* d2 */
        while (r29 > 0) {
           cycle++;                 // nop
            r29 = r29 - 1;          // dec
            cycle++;                // clock for dec

            cycle += (r29 != 0) ? 2 : 1;    // Brne d2
        }
        count--;                    // sbiw r31:r30 - 1
        cycle = cycle + 2;          // clock for sbiw
        cycle += (count != 0) ? 2 : 1;      //Bren d1
    }
}

