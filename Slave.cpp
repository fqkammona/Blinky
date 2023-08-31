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
extern bool found_bounds;

int cycle = 0;
std::vector<Data> dataVector; // Define dataVector
std::vector<Bounds> boundsVector; // Define dataVector

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

        double minCycle = 1000000000;
        double maxCycle = 0;
        int boundR = 1000000000;
        int minR = 0;
        for (int i = 0; i <= 256; ++i) { // 256
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
            } else if((cycle >= ideal_Cycles) & (boundR > i)) boundR = i;


            if(minCycle > cycle) minCycle = cycle;
            if(maxCycle < cycle) maxCycle = cycle;
        }

        if(!found_bounds){
            Bounds bound = {count, boundR};
            boundsVector.push_back(bound);
        }

        cout << "Max: " << maxCycle << " Min: " << minCycle << " r29: " << boundR << endl;
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

