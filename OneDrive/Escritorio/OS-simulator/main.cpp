using namespace std;
#include <iostream>;
#include <string>;
#include "auth.h"
#include "Process.h"
int main(){
    cout << "[OS] // Booting up this make take a few seconds...\n";

    if (authenticateuser())
    {
        cout << "[OS] // Access granted. Welcome to the OS shell \n\n" << endl;
    } else {
        cout << "Access Denied.\n" << "----------------------\n" << "Shutting down.\n" << endl;
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
return 0;
}