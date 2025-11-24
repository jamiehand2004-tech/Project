#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "add_question.h"

using namespace std;

void addQuestion(const string& filename) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "for writing. \n";
        return;
    }

    cin.ignore();
    string text; 
    cout << "Enter the question: ";
    getline(cin, text);

    int optionCount;
    cout << "Enter number of options: ";
    cin >> optionCount;
    cin.ignore();

    vector<string> options(optionCount);

    for (int i = 0; i < optionCount; i++) {
        cout << "Enter option " << i + 1 << ": ";
        getline(cin, options[i]);
    }

    int correct;
    cout << "Enter the correct option, number 1-" << optionCount <<": ";
    cin >> correct;

    file << text << "\n";
    file << optionCount << "\n";

    for (const auto& opt : options) 
        file << opt << "\n";
    
    file << correct - 1 << "\n"; //store as zero-based index

    
    cout << "Question added successfully.\n";
}