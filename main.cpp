// main code
#include <fstream>
#include <iostream> //importing libraries needed for the program
#include "quiz_system.h"
#include "user_system.h"
#include "add_question.h"

using namespace std;

int main() {
    UserSystem users;   // user system object
    QuizSystem quiz;    // quiz system object
    string questionsFile = "questions.txt"; // file to load questions from
    string resultsFile = "results.txt";     // file to save results to

    quiz.loadFromFile(questionsFile); // load questions from file

    int choice;   //variable to hold user choice
    while (true) {  //main loop
        cout << "\n=== Quiz System ===" << endl; //print menu header
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Add Question\n"; 
        cout << "4. Take Quiz\n";
        cout << "5. Leaderboard\n";
        cout << "6. Exit\n";
        cout << "Choice: ";     // print menu
        cin >> choice;          // get user choice

        if (choice == 1) {  //register new user
            string username, password;  //variables to hold username and password
            cout << "Username: ";   //prompt for username
            cin >> username;    //get username
            cout << "Password: ";   //prompt for password
            cin >> password;    //get password
            if (users.registerUser(username, password)) {
                cout << "Registered successfully.\n";
            }else {
                cout << "Failed to register user.\n";
            }
        }
        else if (choice == 2) { //login existing user
            string username, password;  //variables to hold username and password
            cout << "Username: ";    //prompt for username
            cin >> username;    //get username
            cout << "Password: ";   //prompt for password
            cin >> password;    //get password
            if (users.login(username, password)) {   // attempt login
                cout << "Login successful!" << endl;  }  //print success message
            else cout << "Login failed!" << endl;    // login failed
        }
        else if (choice == 3) {             // add new question
            quiz.addingQuestion(questionsFile);   // calls addQuestion function from add_question.cpp
            quiz.loadFromFile(questionsFile); // reload questions after adding new one
        }

        else if (choice == 4) { //take the quiz
            string currentUser = users.getCurrentUser();
            if (currentUser.empty()) { cout << "Login first.\n"; continue; }
            
            int score = quiz.takeQuiz(resultsFile, currentUser);    //take quiz and get score
            users.updateHighScore(score);    
        }
        else if (choice == 5) { //show leaderboard
            users.showLeaderboard();  //display leaderboard
        }
        else if (choice == 6) break; //exit program 
        else cout << "Invalid option chosen. Please try again." << endl; // invalid choice message
    }
    return 0;
}   //end main
//end of file
//FINAL ITERATION COUNT OF JAMIE (23/10/25)-(Current): 26
//FINAL ITERATION COUNT OF JACK (23/10/25)-(Current): -
//FINAL ITERATION COUNT OF RUBEN (23/10/25)-(Current): -

// current problems to fix:
// savestates for users and questions not loading on program start
////save states not loaded across different logins from a user (when program is ran again) 