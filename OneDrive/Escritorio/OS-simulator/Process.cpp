#include "Process.h"
using namespace std;

Process::Process(int id, int arrival, int burst) {
    pid = id;
    arrivalTime = arrival;
    burstTime = burst;
    remainingTime = burst;
    state = NEW;
}

int Process::getPID() { return pid; }
int Process::getArrivalTime() { return arrivalTime; }
int Process::getBurstTime() { return burstTime; }
int Process::getRemainingTime() { return remainingTime; }
ProcessState Process::getState() { return state; }

void Process::setState(ProcessState s) {
    state = s;
}

void Process::runOneCycle() {
    if (remainingTime > 0) {
        remainingTime--;
        if (remainingTime == 0)
            state = TERMINATED;
    }
}

bool Process::isFinished() {
    return remainingTime == 0;
}

void Process::showInfo() {
    cout << "PID: " << pid
         << " | Arrival: " << arrivalTime
         << " | Burst: " << burstTime
         << " | Remaining: " << remainingTime
         << " | State: " << state << endl;
}
