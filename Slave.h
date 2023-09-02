//
// Created by Fatima Kammona on 5/21/23.
//

#ifndef BLINKY_SLAVE_H
#define BLINKY_SLAVE_H

#include <vector>

struct Data {
    int count;
    int cycle;
    int r29;
};

struct Bounds {
    int count;
    int maxCycle;
    int maxR29;
};

extern std::vector<Data> dataVector; // Declare dataVector as extern
extern std::vector<Bounds> boundsVector;

void Slave(int id);
void delayLong(int number, int r29);
int findTopBound(int searchCount);

extern int cycle;

#endif //BLINKY_SLAVE_H
