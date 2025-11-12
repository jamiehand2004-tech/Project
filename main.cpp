#include <iostream> //importing libraries needed for the program
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

// Structures
struct Question { //structure to hold the question data
    string question; //string for the question text
    vector<string> options;//all possible answers in the parameters
    int correctAnswer;//index of correct answer
};

struct User {//structure to hold user data
    string username;//username of user
    string password;//password of user
    int highScore;//highest score achieved by user (saved for leaderboard)
};

class QuizSystem {//main quiz system class
private://private members
    vector<Question> questions; //list of questions for the quiz
    map<string, User> users;    //map of username to User
    string currentUser;       //currently logged-in user

public: //public members
    bool registerUser(string username, string password) {   //register a new user  
        if (users.find(username) != users.end()) {  //check if username already exists
            cout << "Username already exists!" << endl; //if exists, print message
            return false;   //return false
        }
        
        User newUser = {username, password, 0}; //create new user
        users[username] = newUser;  //add user to map
        saveUsers();               //save users to file
        return true;               //return true
    }

    bool login(string username, string password) { //login function
        if (users.find(username) != users.end() && users[username].password == password) {  //check credentials
            currentUser = username; //set current user
            return true;         //return true
        }   
        return false;         //return false
    }

    void addQuestion(string question, vector<string> options, int correct) {    //add a new question
        Question q = {question, options, correct};  //create question object
        questions.push_back(q); //add to questions list
        saveQuestions();    //save questions to file
    }

    int takeQuiz() {    //function to take the quiz
        if (questions.empty()) {    //check if there are questions
            cout << "No questions available!" << endl;  //print message
            return 0;   //return 0
        }

        int score = 0;  //initialize score
        for (const auto& q : questions) {   //iterate through questions
            cout << "\n" << q.question << endl;    //print question
            for (size_t i = 0; i < q.options.size(); i++) {  //print options
                cout << i + 1 << ". " << q.options[i] << endl;  //print each option
            }   //end for

            int answer; //variable to hold user answer
            cout << "Your answer (1-" << q.options.size() << "): "; //prompt for answer
            cin >> answer;  //get user answer

            if (answer == q.correctAnswer) {    //check if answer is correct
                score++;    //increment score   
            }
        }

        if (users[currentUser].highScore < score) { //check for high score
            users[currentUser].highScore = score;   //update high score
            saveUsers();    //save users to file
        }

        return score;   //return final score
    }

    void showLeaderboard() {    //function to show leaderboard
        vector<pair<string, int>> scores;   //vector to hold username and score pairs
        for (const auto& user : users) {    //iterate through users
            scores.push_back({user.first, user.second.highScore});  //add username and score to vector
        }

        sort(scores.begin(), scores.end(), //sort scores in descending order
             [](const pair<string, int>& a, const pair<string, int>& b) {   //lambda function for sorting
                 return a.second > b.second;    //compare scores
             });    //end sort

        cout << "\nLeaderboard:" << endl;   //print leaderboard header
        for (const auto& score : scores) {  //iterate through sorted scores
            cout << score.first << ": " << score.second << endl;    //print username and score
        }
    }

private:    //private helper functions
    void saveUsers() {  //function to save users to file
        ofstream file("users.txt"); //open file
        for (const auto& user : users) {    //iterate through users
            file << user.second.username << " "     //write username
                 << user.second.password << " "    //write password
                 << user.second.highScore << endl;  //write high score
        }
    }

    void saveQuestions() {  //function to save questions to file
        ofstream file("questions.txt"); //open file
        for (const auto& q : questions) {   //iterate through questions
            file << q.question << endl;  //write question
            file << q.options.size() << endl;   //write number of options
            for (const auto& opt : q.options) {  //iterate through options
                file << opt << endl;    //write each option
            }
            file << q.correctAnswer << endl;    //write correct answer index
        }
    }
};  

int main() {    //main function
    QuizSystem quiz;    //create quiz system object
    int choice;   //variable to hold user choice

    while (true) {  //main loop
        cout << "\n=== Quiz System ===" << endl; //print menu header
        cout << "1. Register\n2. Login\n3. Add Question\n4. Take Quiz\n"  //prompt user for choice
             << "5. Show Leaderboard\n6. Exit"
             << "\nChoice: ";   //print menu
        cin >> choice;  //get user choice

        if (choice == 1) {  //register new user
            string username, password;  //variables to hold username and password
            cout << "Username: ";   //prompt for username
            cin >> username;    //get username
            cout << "Password: ";   //prompt for password
            cin >> password;    //get password
            quiz.registerUser(username, password);  //register user
        }
        else if (choice == 2) { //login existing user
            string username, password;  //variables to hold username and password
            cout << "Username: ";    //prompt for username
            cin >> username;    //get username
            cout << "Password: ";   //prompt for password
            cin >> password;    //get password
            if (quiz.login(username, password)) {   //attempt login
                cout << "Login successful!" << endl;    //print success message
            } else {    //login failed
                cout << "Login failed!" << endl;    //print failure message
            }
        }
        else if (choice == 3) {     //add new question
            string question;    //variable to hold question text
            vector<string> options; //vector to hold options
            int correct, numOptions;    //variables for correct answer and number of options

            cout << "Enter question: "; //prompt for question
            cin.ignore();   //clear input buffer
            getline(cin, question); //get question text
            
            cout << "Number of options: ";  //prompt for number of options
            cin >> numOptions;  //get number of options
            
            cin.ignore();   //clear input buffer
            for (int i = 0; i < numOptions; i++) {  //loop to get each option
                string option;  //variable to hold option text
                cout << "Option " << i + 1 << ": "; //prompt for option
                getline(cin, option);   //get option text
                options.push_back(option);  //add option to vector
            }

            cout << "Correct answer (1-" << numOptions << "): ";    //prompt for correct answer
            cin >> correct; //get correct answer index

            quiz.addQuestion(question, options, correct);   //add question to quiz system
        }
        else if (choice == 4) { //take the quiz
            int score = quiz.takeQuiz();    //take quiz and get score
            cout << "Your score: " << score << endl;    //print score
        }
        else if (choice == 5) { //show leaderboard
            quiz.showLeaderboard();  //display leaderboard
        }
        else if (choice == 6) { //exit program
            break; 
        }
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