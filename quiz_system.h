

#ifndef QUIZ_SYSTEM_H
#define QUIZ_SYSTEM_H

#include <string>
#include <vector>
#include "quiz_reader.h"

using namespace std;

class QuizSystem {
private:
    vector<Question> questions;
    
public:
    bool loadFromFile(const string &filename);

    bool saveToFile(const string &filename);

    void addQuestion(const Question &q);
    
    void takeQuiz(const string &resultsFile);

    size_t count() const {
        return questions.size();
    }
};

#endif