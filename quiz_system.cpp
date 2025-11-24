// cleaning up the main.cpp file

#include "quiz_system.h"
#include <iostream>
#include <fstream>

using namespace std;

bool QuizSystem::loadFromFile(const string &filename) {
    questions = loadQuestions(filename);
    return !questions.empty();
}

bool QuizSystem::saveToFile(const string &filename) {
    ofstream file(filename);
    if (!file.is_open()) 
        return false;
    
    for (const auto &q : questions) {
        file << q.text << "\n";
        file << q.options.size() << "\n";
        for (const auto &opt : q.options) file << opt << "\n";
        file << q.correctAnswer << "\n";
        }
        return true;
    }

void QuizSystem::addQuestion(const Question &q) {
    questions.push_back(q);
}

void QuizSystem::takeQuiz(const string &resultsFile) {
    if (questions.empty()) {
        cout << "No questions available." << endl;
        return;
    }

    int score = 0;

    for (const auto &q : questions) {
        cout << "zn" << q.text << endl;
        for (size_t i = 0; i < q.options.size(); i++) {
            cout << i + 1 << ". " << q.options[i] << endl;
        }

        int ans;
        cout << "Your answer: ";
        cin >> ans;

        if (ans - 1 == q.correctAnswer) score++;
    }

    cout << "\nYour score: " << score << "/ " << questions.size() << endl;

    ofstream out(resultsFile, ios::app);
    if (out.is_open()) {
        out << score << "/ " << questions.size() << "\n";
    }
} 