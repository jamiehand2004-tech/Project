#include "quiz_reader.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Read questions from a text file and return them as a vector of Question
vector<Question> loadQuestions(const string& filename) {
    vector<Question> questions;       // result vector to return
    ifstream file(filename);          // open the file for reading

    // If opening failed, report and return empty list
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << "\n";
        return questions;   // Failure to open file.
    }

    while (true) {
        Question q;                       // temp question to fill

        // Read the question text; break if no more lines
        if (!getline(file, q.text)) break;

        // Skip blank lines between questions
        if (q.text.empty()) continue;

        int optionCount = 0;
        file >> optionCount;               // read number of options
        file.ignore();                     // discard the newline after the integer

        // If optionCount is invalid or we've reached an unexpected state, stop parsing
        if (optionCount <= 0) break;

        q.options.clear();                 // prepare options vector
        for (int i = 0; i < optionCount; i++) {
            string opt;
            getline(file, opt);            // read each option line
            q.options.push_back(opt);
        }

        file >> q.correctAnswer;           // read the correct option index (0-based expected)
        file.ignore();                     // discard newline after the integer
        
        questions.push_back(q);           // add the parsed question to the list
    }

    return questions;                    // return all parsed questions
}