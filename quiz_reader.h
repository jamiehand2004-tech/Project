#ifndef QUIZ_READER_H
#define QUIZ_READER_H

// Small helper header that declares the Question type and a loader
#include <vector>   // std::vector for holding multiple options
#include <string>   // std::string for text fields

using namespace std; // bring common std names into global namespace for brevity

// Represents a single multiple-choice question
struct Question {
    string text;               // the question text shown to the user
    vector<string> options;    // list of option strings (answers)
    int correctAnswer;         // index (0-based) of the correct option
};

// Load questions from a text file and return them as a vector
vector<Question> loadQuestions(const string & filename);

#endif