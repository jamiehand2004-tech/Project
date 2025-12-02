#include "SavingSystem.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void UserSaveSystem::RegisterUser(){

    cout << "Please enter username: " << endl;
    string u;
    cin >> u;

    cout << "Please enter a password: " << endl;
    string p;
    cin >> p;
    
    fstream myFile;
    myFile.open("userDetails.txt", ios::app); // writing in txt file
    if(myFile.is_open()){
        myFile << u << endl;
        myFile << p << endl;
    myFile.close();
    } else {
        cout << "error opening the file" << endl;
    }
    
}




void UserSaveSystem::LoginSystem(){
    
    cout << "Please enter your login details: " << endl;

    cout << "username: " << endl;
    string un;
    cin >> un;

    cout << "password: " << endl;
    string pn;
    cin >> pn;

    fstream myFile;
    myFile.open("userDetails.txt", ios::in);// read mode
    if(myFile.is_open()){    
        string fileUser;
        string filePassword;
        int checker_variable = 0;
        while(getline(myFile, fileUser)){
        getline(myFile, filePassword);
        if((un == fileUser)&&(pn == filePassword)){
                checker_variable=1;
                break; }}

        if (checker_variable == 1){
            cout <<"user had been successfully logged in" << endl; 
        } else {
            cout << "error with login" << endl;
        }
        myFile.close();
            
}

}
