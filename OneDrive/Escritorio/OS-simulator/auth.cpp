using namespace std;
#include "auth.h"
#include <iostream>
#include <string>

bool authenticateuser(){
    const string username = "admin";
    const string password = "password123";
    string user , pass;

    cout << "Username: ";
    getline(cin, user);
    cout << "Password: ";
    getline(cin, pass);


    if(user == username && pass == password){
        cout << "Authentication successfull. Welcome!" << endl;
        return true;
    }else{
        cout << "Username or Password incorrect. " << endl;
        return false;
    }
}