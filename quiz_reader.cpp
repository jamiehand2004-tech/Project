#include "quiz_reader.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


vector<Question> loadQuestions(const string& filename) {
    vector<Question> questions;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << "\n";
        return questions;   // Failure to open file.
    }

    while (true) {
        Question q;
        if (!getline(file, q.text)) break;
        if (q.text.empty()) continue;       // Skip empty lines

        int optionCount = 0;
        file >> optionCount;
        file.ignore();

        if (optionCount <= 0) break;

        q.options.clear();
        for (int i = 0; i < optionCount; i++) {
            string opt;
            getline(file, opt);
            q.options.push_back(opt);
        }
        file >> q.correctAnswer;
        file.ignore();
        
        questions.push_back(q);
    }

    return questions;
}