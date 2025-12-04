#include <iostream>
#include <string>
#include <vector>
#include "auth.h"
#include "Process.h"
#include "Scheduler.h"
#include "VirtualMemory.h"

using namespace std;

int main() {
    cout << "[OS] // Booting up this may take a few seconds...\n";

    if (authenticateuser()) {
        cout << "[OS] // Access granted. Welcome to the OS shell.\n\n";
    } else {
        cout << "Access Denied.\n----------------------\nShutting down.\n";
        return 1;
    }

    // =======================
    // 1. SIMPLE PROCESS SIM
    // =======================
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

    // ==========================
    // 2. CPU SCHEDULING SIM
    // ==========================
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

    // ==========================
    // 3. VIRTUAL MEMORY SIM
    // ==========================
    cout << "\n=== Virtual Memory Simulation ===\n";

    VirtualMemory vm;

    cout << "We simulate paged memory with:\n";
    cout << "  Pages      : " << VirtualMemory::NUM_PAGES << "\n";
    cout << "  Frames     : " << VirtualMemory::FRAME_COUNT << "\n";
    cout << "  Page size  : " << VirtualMemory::PAGE_SIZE << " bytes\n\n";

    int logicalAddress;
    while (true) {
        cout << "Enter a logical address between 0 and "
             << (VirtualMemory::NUM_PAGES * VirtualMemory::PAGE_SIZE - 1)
             << " (-1 to stop): ";
        cin >> logicalAddress;

        if (!cin) {
            cout << "Input error, exiting virtual memory demo.\n";
            break;
        }

        if (logicalAddress < 0) {
            break;
        }

        if (logicalAddress >= VirtualMemory::NUM_PAGES * VirtualMemory::PAGE_SIZE) {
            cout << "Out of range logical address.\n";
            continue;
        }

        bool fault = false;
        // Read current value
        unsigned char value = vm.readByte(static_cast<uint16_t>(logicalAddress), fault);

        cout << "Read from logical address " << logicalAddress
             << " -> value = " << static_cast<int>(value)
             << (fault ? "  [PAGE FAULT]\n" : "  [HIT]\n");

        // Now write something (for example, low 8 bits of address)
        bool fault2 = false;
        unsigned char newValue = static_cast<unsigned char>(logicalAddress % 256);
        vm.writeByte(static_cast<uint16_t>(logicalAddress), newValue, fault2);

        cout << "Wrote value " << static_cast<int>(newValue)
             << " to that same logical address"
             << (fault2 ? "  [PAGE FAULT ON WRITE]\n" : "  [NO FAULT ON WRITE]\n");
    }

    vm.printStats();

    cout << "\n[OS] // Shutting down.\n";
return 0;
}

