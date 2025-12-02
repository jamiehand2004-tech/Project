#include "quiz_system.h"
#include <iostream>
#include <fstream>

using namespace std;

// Loads questions from file
void QuizSystem::loadFromFile(const string & filename) {
    questions = loadQuestions(filename);
}

// Saves questions to file
void QuizSystem::saveToFile(const string & filename) const {
    ofstream file(filename);

    if (!file.is_open())
        cout << "Error: Cannot write questions.\n";
        return;
    
    for (const auto & q : questions) {
        file << q.text << "\n";
        file << q.options.size() << "\n";
        for (const auto & opt : q.options)
            file << opt << "\n";
        file << q.correctAnswer << "\n";
    }
}
// Adds a question to the quiz
void QuizSystem::addQuestion(const Question & q) {
    questions.push_back(q);
}

// User adds questions
void QuizSystem::addingQuestion(const string & filename) {
    ofstream file(filename, ios::app);
    if(!file.is_open()) {
        cerr << "Error: Could not open " << filename << " for writing.\n";
        return;
    }
    cin.ignore();
    Question q;
    cout << "Enter the question text: ";
    getline(cin, q.text);

    int numOptions;
    cout << "Enter number of options: ";
    cin >> numOptions;
    cin.ignore();

    q.options.resize(numOptions);

    for (int i = 0; i < numOptions; i++) {
        cout << "Enter option " << i + 1 << ": ";
        getline(cin, q.options[i]);
    }

    int correct;
    cout << "Enter correct option number (1-" << numOptions << "): ";
    cin >> correct;

    q.correctAnswer = correct - 1;

    file << q.text << "\n";
    file << numOptions << "\n";
    for (auto & opt : q.options) file << opt << "\n";
    file << q.correctAnswer << "\n";

    cout << "Question added successfully.\n";
}

//Running the quiz
int QuizSystem::takeQuiz(const string & resultsFile, 
                         const string & username) {
    if (questions.empty()) {
        cout << "No questions available.\n";
        return 0;
    }

    int score = 0;
    for (const auto & q : questions) {
        cout << "\n" << q.text << "\n";
        for (size_t i = 0; i < q.options.size(); i++) 
            cout << i + 1 << ". " << q.options[i] << endl;

        int ans;
        cout << "Your answer: ";
        cin >> ans;

        if (ans - 1 == q.correctAnswer) score++;
    }

    cout << "\nYour score: " << score << "/ " << questions.size() << "\n";

    ofstream out(resultsFile, ios::app);
    if (out.is_open()) {
        out << username << " scored " << score << "/" << questions.size() << ".\n";
    }
    return score;
}