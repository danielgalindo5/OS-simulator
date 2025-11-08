#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <string>
using namespace std;

enum ProcessState { NEW, READY, RUNNING, WAITING, TERMINATED };

class Process {
private:
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    ProcessState state;

public:
    Process(int id, int arrival, int burst);

    int getPID();
    int getArrivalTime();
    int getBurstTime();
    int getRemainingTime();
    ProcessState getState();

    void setState(ProcessState s);
    void runOneCycle();
    bool isFinished();
    void showInfo();
};

#endif
