#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <vector>
using namespace std;

struct SchedProcess {
    int pid;
    int arrival;
    int burst;
    int completion;
    int turnaround;
    int waiting;
    int remaining;
};

void fcfs(vector<SchedProcess>&);
void sjf(vector<SchedProcess>&);
void srtf(vector<SchedProcess>&);
void displayResults(const vector<SchedProcess>&);

#endif
