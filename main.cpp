#include <iostream>
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
double range_of_cycles;
double ideal_Cycles;

void findNumberOfCycles(double frequency, double ideal_delay_time){
    double oneCycle = 1.00 / frequency;
    ideal_Cycles = ideal_delay_time / oneCycle;
    cout << ideal_Cycles << endl;
}

int main() {
    double frequency, ideal_delay_time;

    cout << "Enter the Frequency: ";
    cin >>  frequency;

    cout << "Enter Ideal Delay: ";
    cin >> ideal_delay_time;

    findNumberOfCycles(frequency, ideal_delay_time);

    cout << "Enter Range of Cycles: ";
    cin >> range_of_cycles;
    cout << endl;
    
    for (int i = 0; i <= 65534; ++i) {
        numberQueue.push(i);
    }

    run();
    cout << "Total numbers divisible by 37: " << total_options_found << endl;

    return 0;
}