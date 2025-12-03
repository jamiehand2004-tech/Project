// main code for the Quiz System application
#include <fstream>
#include <iostream> // input/output (cout, cin, cerr)
#include "quiz_system.h" // quiz functionality and types
#include "user_system.h" // user registration/login and leaderboard

using namespace std;

int main() {
    UserSystem users;   // manages user accounts and scores
    QuizSystem quiz;    // manages questions and running quizzes
    string questionsFile = "questions.txt"; // file where questions are stored
    string resultsFile = "results.txt";     // file where quiz results are appended

    // Load questions from disk into memory at startup
    quiz.loadFromFile(questionsFile);

    int choice;   // hold the user's menu selection
    while (true) {  // main menu loop
        cout << "\n=== Quiz System ===" << endl; // menu header
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Add Question\n";
        cout << "4. Take Quiz\n";
        cout << "5. Leaderboard\n";
        cout << "6. Exit\n";
        cout << "Choice: ";     // prompt for choice
        cin >> choice;          // read numeric choice

        if (choice == 1) {  // Register a new user
            string username, password;
            cout << "Username: ";
            cin >> username;    // read username
            cout << "Password: ";
            cin >> password;    // read password
            if (users.registerUser(username, password)) { // try to register
                cout << "Registered successfully.\n"; // success message
            } else {
                cout << "Failed to register user.\n"; // failure message
            }
        }
        else if (choice == 2) { // Login existing user
            string username, password;
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;
            if (users.login(username, password)) { // attempt login
                cout << "Login successful!" << endl; // success
            } else {
                cout << "Login failed!" << endl; // failure
            }
        }
        else if (choice == 3) { // Add a new question interactively
            quiz.addingQuestion(questionsFile); // prompt user and append to file
            quiz.loadFromFile(questionsFile);   // reload questions into memory
        }
        else if (choice == 4) { // Take the quiz (requires login)
            string currentUser = users.getCurrentUser();
            if (currentUser.empty()) { // no one logged in
                cout << "Login first.\n";
                continue; // back to menu
            }

            int score = quiz.takeQuiz(resultsFile, currentUser); // run quiz and get score
            users.updateHighScore(score); // update stored high score if needed
        }
        else if (choice == 5) { // Show leaderboard
            users.showLeaderboard();  // display top scores
        }
        else if (choice == 6) { // Exit the program
            break;
        }
        else { // Invalid menu choice
            cout << "Invalid option chosen. Please try again." << endl;
        }
    }

    return 0; // normal exit
}