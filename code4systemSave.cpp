/// code4saveSystem
#include <iostream> 
#include <fstream>
#include <string>
using namespace std;

struct User {
    string username;
    string password;
    int highScore;

};

void saveUser(const User& user) { /// read only the struct User reference and this is stored in parameter variable user
    ofstream outFile("userdata.txt"); /// this vip writes text in a file, outFile is a variable used for storing data,  userdata.txt is the txt file storing this information
    if (outFile.is_open()){ /// outFile is open and can be modified!
        outFile << user.username << endl; /// outFile << sending user(parameter variable). data member to file.
        outFile << user.password << endl;
        outFile << user.highScore << endl;
        outFile.close();
        cout << "Save was successful" << endl;
    } else{
        cout << "error with saving the file" << endl;
    }
}

User loadUser(){/// calling struct User, function name loadUser for loading from file
    User user; /// User is my struct, user is paramter var
    ifstream inFile("userdata.txt"); /// opens file for reading, inFile is the op of outFile, variable for releasing data from file
    if (inFile.is_open()){ /// file allows exit/ reading of data
        getline(inFile, user.username);/// getline instruction gets parameter variable member from txt file, inFile aprameter var that stores the released data
        getline(inFile, user.password);
        inFile >> user.highScore; /// output score
        inFile.close();
        cout << "user data successfully loaded" << endl;
    } else { 
        cout << "user data did not load" << endl;
    }
    return user;
}


void loginUser(){
    


int main(){ /// main function for this test
   
   while(true){/// this loops the main loop forever so long as a break has not occurred
    cout << "=====Menu=====" << endl;
    cout << "please select one of the below options" << endl;
    cout << "press 1 to register"<<endl;
    cout << "press 2 to login"<<endl;
    cout << "press 3 to add a question" << endl;
    cout << "press 4 to take quiz" << endl; // nu e pt mine,va fi pt programul central
    cout << "press 5 to show leaderboard" << endl; // nu e pt mine
    cout << "press 0 to exit program"<<endl; // nu e pt mine

    
    int choice; /// integer variable choice ie whatever option from up above is inputted, stored innit
    if(!(cin >> choice))break;/// cin the var choice, if choice is inputted as anything else, exit loop and program as a consequence
    ///used in this format cin is saying that if the input of choice i snot an integer we exit the program

    if(choice == 0)/// exit program
        break;
    
   }

   cout << "exiting program......bye"<< endl;/// end of program statement
   return 0;

   }
   ///____________________________________________________________vip system plan ___________________________________________________
/*

13/11 - ive done a small change changing the int score to highScore to better suit the main.cpp code, im trying to figure out how im going to integrate this intot th emain system,

i will add a register check system to check if the username already exists. Jamie already has a system so ill be checking his one and seeing if its integratable
note that jamies code is using a constructor class system to register, my one works purely off of a single struct with a bunch of functions. i could probably modify the class and remove the parts not needed then mod 
the main function to use my system, only problem is the highScore system.

priority list
1. adding in multiple users using map and vectors most probs.

game plan : finish and integration test, after which split of the functions from the main segment adding the the main funciton to the main.cpp file and creating a sep file for the code as a SaveRegLoginSystem.h file, 
use #includes in the main file and boom job done. plan to ge thtis done this weekend week 10. 

*/

