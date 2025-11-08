#include "Scheduler.h"
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

void fcfs(vector<SchedProcess>& p) {
    sort(p.begin(), p.end(), [](auto &a, auto &b) {
        return a.arrival < b.arrival;
    });
    int time = 0;
    for (auto &proc : p) {
        if (time < proc.arrival)
            time = proc.arrival;
        time += proc.burst;
        proc.completion = time;
        proc.turnaround = proc.completion - proc.arrival;
        proc.waiting = proc.turnaround - proc.burst;
    }
}

void sjf(vector<SchedProcess>& processes) {
    int n = processes.size();
    vector<bool> completed(n, false);
    int completedCount = 0;
    int currentTime = 0;
    while (completedCount < n) {
        int idx = -1;
        int minBurst = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (!completed[i] && processes[i].arrival <= currentTime) {
                if (processes[i].burst < minBurst) {
                    minBurst = processes[i].burst;
                    idx = i;
                }
            }
        }
        if (idx == -1) {
            currentTime++;
            continue;
        }
        currentTime += processes[idx].burst;
        processes[idx].completion = currentTime;
        processes[idx].turnaround = processes[idx].completion - processes[idx].arrival;
        processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;
        completed[idx] = true;
        completedCount++;
    }
}

void srtf(vector<SchedProcess>& processes) {
    int n = processes.size();
    int completed = 0, currentTime = 0;
    while (completed < n) {
        int idx = -1;
        int minRemaining = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrival <= currentTime && processes[i].remaining > 0) {
                if (processes[i].remaining < minRemaining) {
                    minRemaining = processes[i].remaining;
                    idx = i;
                }
            }
        }
        if (idx == -1) {
            currentTime++;
            continue;
        }
        processes[idx].remaining--;
        currentTime++;
        if (processes[idx].remaining == 0) {
            processes[idx].completion = currentTime;
            processes[idx].turnaround = processes[idx].completion - processes[idx].arrival;
            processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;
            completed++;
        }
    }
}

void displayResults(const vector<SchedProcess>& processes) {
    float avgTurnaround = 0, avgWaiting = 0;
    cout << "\nPID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (auto &p : processes) {
        avgTurnaround += p.turnaround;
        avgWaiting += p.waiting;
        cout << p.pid << "\t"
             << p.arrival << "\t"
             << p.burst << "\t"
             << p.completion << "\t\t"
             << p.turnaround << "\t\t"
             << p.waiting << endl;
    }
    avgTurnaround /= processes.size();
    avgWaiting /= processes.size();
    cout << "\nAverage Turnaround Time: " << avgTurnaround;
    cout << "\nAverage Waiting Time: " << avgWaiting << endl;
}

