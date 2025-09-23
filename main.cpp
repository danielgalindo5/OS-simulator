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