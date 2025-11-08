<<<<<<< HEAD
#include <iostream>
#include <string>
#include <vector>
#include "auth.h"
#include "Process.h"
#include "Scheduler.h"
using namespace std;

int main() {
    cout << "[OS] // Booting up this may take a few seconds...\n";

    if (authenticateuser()) {
        cout << "[OS] // Access granted. Welcome to the OS shell.\n\n";
    } else {
        cout << "Access Denied.\n----------------------\nShutting down.\n";
        return 1;
    }

    cout << "\n=== Process Simulation ===\n";

    Process p1(1, 0, 4);
    Process p2(2, 2, 3);

    p1.setState(READY);
    p2.setState(NEW);

    p1.showInfo();
    p2.showInfo();

    cout << "\nRunning p1...\n";
    p1.setState(RUNNING);

    while (!p1.isFinished()) {
        p1.runOneCycle();
        p1.showInfo();
    }

    cout << "p1 finished!\n";

    cout << "\n=== CPU Scheduling Simulation ===\n";

    vector<SchedProcess> schedProcs = {
        {1, 0, 8, 0, 0, 0, 8},
        {2, 1, 4, 0, 0, 0, 4},
        {3, 2, 9, 0, 0, 0, 9},
        {4, 3, 5, 0, 0, 0, 5}
    };

    cout << "Choose a scheduling algorithm:\n";
    cout << "1. FCFS\n2. SJF\n3. SRTF\n> ";

    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            fcfs(schedProcs);
            cout << "\n=== FCFS Scheduling Results ===\n";
            break;
        case 2:
            sjf(schedProcs);
            cout << "\n=== SJF Scheduling Results ===\n";
            break;
        case 3:
            srtf(schedProcs);
            cout << "\n=== SRTF Scheduling Results ===\n";
            break;
        default:
            cout << "Invalid choice!" << endl;
            return 0;
    }

    displayResults(schedProcs);

    return 0;
}
=======
using namespace std;
#include <iostream>;
#include <string>;
#include "auth.h"
int main(){
    cout << "[OS] // Booting up this make take a few seconds...\n";

    if (authenticateuser())
    {
        cout << "[OS] // Access granted. Welcome to the OS shell \n\n" << endl;
    } else {
        cout << "Access Denied.\n" << "----------------------\n" << "Shutting down.\n" << endl;
        return 1;
    }
    return 0;

}
>>>>>>> 9d13fff37fd8f0c0e7dc5b72725d194def3c881d
