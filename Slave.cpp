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
extern int top_bound;
extern int bottom_bound;

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

        int minCycle = 1000000000;
        int maxCycle = 0;
        int boundR = 1000000000;
        int minBoundR = 1000000000;
        int temp = ideal_Cycles - 1000000;

        if(found_bounds){
            if(count % 500 == 0){
                top_bound = findTopBound(count);
                bottom_bound = findBottomBound(count);
                if(top_bound == 1000000000 || top_bound == -1) top_bound = 256;
                if(bottom_bound == 1000000000 || bottom_bound == -1) bottom_bound = 0;
            }
        }else {
            top_bound = 256;
            bottom_bound = 0;
        }

        cout << "Count " << count << " Top Bound: " << top_bound << " Bottom Bound: " << bottom_bound << endl;
        int pastMinCycle = 0;
        for (int i = bottom_bound; i <= top_bound; ++i) { // 256
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
            } else if((cycle >= ideal_Cycles) & (boundR > i)) {
                boundR = i;
                top_bound = boundR;
            }else if((cycle < temp) & (cycle > pastMinCycle)) {
                pastMinCycle = cycle;
                minBoundR = i;
               // if(minBoundR == 1000000000) min = 256;
            }

            if(minCycle > cycle){
                minCycle = cycle;
               // minBoundR = i;
            }
            if(maxCycle < cycle) maxCycle = cycle;
        }

        if(!found_bounds){
            if(boundR == 1000000000) boundR = 256;

            Bounds bound = {count, maxCycle, boundR, minBoundR};
            boundsVector.push_back(bound);
        }

        cout << "Max: " << maxCycle << " Min: " << pastMinCycle
            << " r29: " << boundR << " Min Bound R: " << minBoundR << endl;
    }
}

int findBottomBound(int searchCount) {
    for (const auto& bound : boundsVector) {
        if (bound.count == searchCount) {
            return bound.minR29;
        }
    }
    return -1; // Return -1 if not found
}

int findTopBound(int searchCount) {
    for (const auto& bound : boundsVector) {
        if (bound.count == searchCount) {
            return bound.maxR29;
        }
    }
    return -1; // Return -1 if not found
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

