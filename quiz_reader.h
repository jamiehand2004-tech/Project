#ifndef QUIZ_READER_H
#define QUIZ_READER_H

#include <vector>
#include <string>

using namespace std;


struct Question {
    string text;
    vector<string> options;
    int correctAnswer;
};

vector<Question> loadQuestions(const string& filename);

#endif