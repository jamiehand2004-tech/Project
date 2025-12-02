#pragma once
#include <iostream>
#include <string>

using namespace std;

struct User {
    string username;
    string password;
    int highScore = 0;
};

class UserSaveSystem {
    public: 
        void RegisterUser();
        void LoginSystem();
        

};
