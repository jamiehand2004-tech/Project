#include "SavingSystem.h"
#include <iostream>
#include <string>

using namespace std;

int choice;

int main () {

    cout << "Menu" << endl;
    cout << "1.) register " << endl;
    cout << "2.) login " << endl;
    
    cin >> choice;

    if (choice == 1){
        RegisterUser();
    } else if (choice == 2){
        LoginSystem();
    } else {
        cout << "menu error" << endl;
    }

}