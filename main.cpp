#include <iostream>
#include <iomanip>
#include <vector>
#include <mutex>
#include <queue>
#include "Master.h"
#include "Slave.h"

using namespace std;

vector<int> buffer;
mutex bufferMutex;
mutex queueMutex;
queue<int> numberQueue;
int total_options_found = 0;
mutex divisibleBy37CountMutex;
double ideal_Cycles;
bool found_bounds;

void findNumberOfCycles(double ideal_delay_time){
    found_bounds = false;
    double oneCycle = 1.00 / 16000000;
    ideal_Cycles = ideal_delay_time / oneCycle;
    cout << "Cycles: ";
    std::cout << std::fixed << std::setprecision(0) << ideal_Cycles << std::endl;
}



int main() {
    double ideal_delay_time;

    cout << "Enter Ideal Delay: ";
    cin >> ideal_delay_time;

    findNumberOfCycles(ideal_delay_time);
    cout << endl;

    // finding the bounds
    for (int i = 0; i <= 65534; i += 1000) { // 65534
        numberQueue.push(i);
    }
// 100 - Max: 102811 Min: 511
// 1000 - Max: 1028011 Min: 5011
// 5000 - Max: 5140011 Min: 25011
// 7000 - Max: 7196011 Min: 35011
// 8000 - Max: 8225039 Min: 40016 - Here
// 8500 - Max: 8738011 Min: 42511
// 10000 - Max: 10280011 Min: 50011 Max r29: 216
// 20000 - Max: 20560011 Min: 100011 Max r29: 108
// 30000 - Max: 30840011 Min: 150011 Max r29: 72
// 40000 - Max: 41120011 Min: 200011 Max r29: 54
// 50000 - Max: 51400011 Min: 250011 Max r29: 43
// 60000 - Max: 61680011 Min: 300011 Max r29: 36

    run();

    found_bounds = true;
    for (const auto& bound : boundsVector) {
        std::cout << "Count: " << bound.count << ", MaxR29: " << bound.maxR29 << std::endl;
    }


    for (int i = 20000; i <= 65534; i++) {
        numberQueue.push(i);
    }

    run();

    cout << "Total Options Found: " << total_options_found << endl;

    return 0;
}



