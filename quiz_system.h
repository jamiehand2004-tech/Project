#ifndef QUIZ_SYSTEM_H
#define QUIZ_SYSTEM_H

#include <string>
#include <vector>
#include "quiz_reader.h"

using namespace std;

class QuizSystem {
private:
    vector<Question> questions;     // list of questions for the quiz
    
public:
    void loadFromFile(const string & filename); // load question from file
    void saveToFile(const string & filename) const;   // save questions to file

    void addQuestion(const Question & q);   // added question to file
    void addingQuestion(const string & filename);   // user added question to file

    int takeQuiz(const string & resultsFile, 
                 const string & username);  // run the quiz

};

#endif