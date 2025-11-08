#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

// Structures
struct Question {
    string question;
    vector<string> options;
    int correctAnswer;
};

struct User {
    string username;
    string password;
    int highScore;
};

class QuizSystem {
private:
    vector<Question> questions;
    map<string, User> users;
    string currentUser;

public:
    bool registerUser(string username, string password) {
        if (users.find(username) != users.end()) {
            cout << "Username already exists!" << endl;
            return false;
        }
        
        User newUser = {username, password, 0};
        users[username] = newUser;
        saveUsers();
        return true;
    }

    bool login(string username, string password) {
        if (users.find(username) != users.end() && users[username].password == password) {
            currentUser = username;
            return true;
        }
        return false;
    }

    void addQuestion(string question, vector<string> options, int correct) {
        Question q = {question, options, correct};
        questions.push_back(q);
        saveQuestions();
    }

    int takeQuiz() {
        if (questions.empty()) {
            cout << "No questions available!" << endl;
            return 0;
        }

        int score = 0;
        for (const auto& q : questions) {
            cout << "\n" << q.question << endl;
            for (size_t i = 0; i < q.options.size(); i++) {
                cout << i + 1 << ". " << q.options[i] << endl;
            }

            int answer;
            cout << "Your answer (1-" << q.options.size() << "): ";
            cin >> answer;

            if (answer == q.correctAnswer) {
                score++;
            }
        }

        if (users[currentUser].highScore < score) {
            users[currentUser].highScore = score;
            saveUsers();
        }

        return score;
    }

    void showLeaderboard() {
        vector<pair<string, int>> scores;
        for (const auto& user : users) {
            scores.push_back({user.first, user.second.highScore});
        }

        sort(scores.begin(), scores.end(), 
             [](const pair<string, int>& a, const pair<string, int>& b) {
                 return a.second > b.second;
             });

        cout << "\nLeaderboard:" << endl;
        for (const auto& score : scores) {
            cout << score.first << ": " << score.second << endl;
        }
    }

private:
    void saveUsers() {
        ofstream file("users.txt");
        for (const auto& user : users) {
            file << user.second.username << " " 
                 << user.second.password << " "
                 << user.second.highScore << endl;
        }
    }

    void saveQuestions() {
        ofstream file("questions.txt");
        for (const auto& q : questions) {
            file << q.question << endl;
            file << q.options.size() << endl;
            for (const auto& opt : q.options) {
                file << opt << endl;
            }
            file << q.correctAnswer << endl;
        }
    }
};

int main() {
    QuizSystem quiz;
    int choice;

    while (true) {
        cout << "\n1. Register\n2. Login\n3. Add Question\n4. Take Quiz\n"
             << "5. Show Leaderboard\n6. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            string username, password;
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;
            quiz.registerUser(username, password);
        }
        else if (choice == 2) {
            string username, password;
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;
            if (quiz.login(username, password)) {
                cout << "Login successful!" << endl;
            } else {
                cout << "Login failed!" << endl;
            }
        }
        else if (choice == 3) {
            string question;
            vector<string> options;
            int correct, numOptions;

            cout << "Enter question: ";
            cin.ignore();
            getline(cin, question);
            
            cout << "Number of options: ";
            cin >> numOptions;
            
            cin.ignore();
            for (int i = 0; i < numOptions; i++) {
                string option;
                cout << "Option " << i + 1 << ": ";
                getline(cin, option);
                options.push_back(option);
            }

            cout << "Correct answer (1-" << numOptions << "): ";
            cin >> correct;

            quiz.addQuestion(question, options, correct);
        }
        else if (choice == 4) {
            int score = quiz.takeQuiz();
            cout << "Your score: " << score << endl;
        }
        else if (choice == 5) {
            quiz.showLeaderboard();
        }
        else if (choice == 6) {
            break;
        }
    }

    return 0;
}