#ifndef QUIZ_SYSTEM_H
#define QUIZ_SYSTEM_H

// Basic includes and types used by the quiz system
#include <string>              // for std::string
#include <vector>              // for std::vector to hold questions
#include "quiz_reader.h"     // defines Question and file helpers

using namespace std;

// operations to load/save questions, add new ones, and run the quiz.
class QuizSystem {
private:
    vector<Question> questions;     // list of available quiz questions
    
public:
    // Load questions from file
    void loadFromFile(const string & filename);

    // Save the questions the file
    void saveToFile(const string & filename) const;

    // Add Question object to the in-memory list
    void addQuestion(const Question & q);

    // Prompt user to add a question and add it to the file
    void addingQuestion(const string & filename);

    // Run the quiz and return the score
    int takeQuiz(const string & resultsFile, 
                 const string & username);

};

#endif