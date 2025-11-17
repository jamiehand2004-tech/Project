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

void registerFlow (){ ///  "register function" named registerflow
    User newUser; /// struct user, new paramter variable newUser that will contain registration details
    cout << "create username" ; /// output this to get input
    cin >> newUser.username;/// new member
    cout << "create password";/// output this to get input
    cin >> newUser.password;/// member
    /// computer memory should reserve all 3 members inside my variable

    saveUser(newUser); /// using function saveUser save the new struct paramtere varaible 

}

void loginFlow(){ /// function called for logging 
    string u, p; ///declaring 2 varaiblse that i will be using to contain the inputs for later comparison, ie checking if u == username saved
    cout << "Username"; /// telling the user to put in username
    cin >> u; /// inputed username is saved in u
    cout << "password"; /// telling user to put it password
    cin >> p;/// password stored in p 

    User saved = loadUser(); /// calling trhe loading user data function, saved is a paramter variable using struct User, im saving the loaded info into it, its a temporary variable
    if(saved.username.empty() && saved.password.empty()){ /// if var saved contains nothing, hence empty() then no user found
        cout <<"no user found" << endl;/// output if if statement is through
        return;
    }

    if(u == saved.username && p == saved.password){/// comparing if var saved structure if they match saved username and password
        cout << "login success, current score: " << saved.score << endl;/// successful output
    cout << "successful load in of user"<< endl;}
    else if (u != saved.username && p != saved.password){
        cout <<"unsuccessful load in of user"<< endl;
    } 
    else {
        cout << "loading error" << endl;
    }
        
    }


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
    else if(choice == 1)/// register
        registerFlow();
    else if (choice == 2 ) /// login
        loginFlow();
    else 
        cout<< "no comprehendo" << endl; /// if anything else occurs output this
   }

   cout << "exiting program......bye"<< endl;/// end of program statement
   return 0;

   }
   ///____________________________________________________________vip system plan ___________________________________________________
/*system as of rn can only store one person, i need to add in multiple user save. this is not fully integrated into the main system as of now
it is 23:39 so i aint doing this till the weekend. also small problem when an error occurs it displays user data succesffully loaded, not major
i could live with that

13/11 - ive done a small change changing the int score to highScore to better suit the main.cpp code, im trying to figure out how im going to integrate this intot th emain system,

the list of things that are currently compatible are:

1. the User struct is the exact same, perfect
2.
3.

i will add a register check system to check if the username already exists. Jamie already has a system so ill be checking his one and seeing if its integratable
note that jamies code is using a constructor class system to register, my one works purely off of a single struct with a bunch of functions. i could probably modify the class and remove the parts not needed then mod 
the main function to use my system, only problem is the highScore system.

priority list
1. adding in multiple users using map and vectors most probs.

game plan : finish and integration test, after which split of the functions from the main segment adding the the main funciton to the main.cpp file and creating a sep file for the code as a SaveRegLoginSystem.h file, 
use #includes in the main file and boom job done. plan to ge thtis done this weekend week 10. 


*/


   ///_____________________________________________________________if u didnt write this underneath code dont bothered wt it______________________________________________________________________________________
   
   
   /// greened out separate old structure (keep)

   
    /*User player; ///Remember User is the struct, player is a va of User, im creating a new var"player" and reserving space for its members
    cout << "enter username" << endl; 
    cin >> player.username; /// taking in data (username)
    cout << "enter password" << endl;
    cin >> player.password; /// taking in data (password)
    player.score = 10; /// predetermined player score

    /// so far im creating a user data and instantly getting the login
    /// create a separate system, where user is created and login in option comes afterwards separatley
    /// 
    saveUser(player); /// saveUser "premade function for save" will save all data members to userdata.txt file


    cout << "please enter username" << endl;
    cin >> user.username;
    cout << " enter password" << endl;
    cin >> user.password;

    //cout << "\nNow loading user data... \n";


    //User loaded = loadUser();

   // cout << "Username: " << loaded.username << endl;
   // cout << "Password: " << loaded.password<< endl;
    //cout << "Score: " << loaded.score << endl; */

    


