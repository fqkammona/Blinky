#include <iostream>
#include <iomanip>
#include <vector>
#include <mutex>
#include <queue>
#include "Master.h"
using namespace std;

vector<int> buffer;
mutex bufferMutex;
mutex queueMutex;
queue<int> numberQueue;
int total_options_found = 0;
mutex divisibleBy37CountMutex;
double ideal_Cycles;

void findNumberOfCycles(double ideal_delay_time){
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

    for (int i = 8650; i <= 65534; ++i) {
        numberQueue.push(i);
    }

    run();

    cout << "Total Options Found: " << total_options_found << endl;

    return 0;
}



