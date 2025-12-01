/*#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "add_question.h"

using namespace std;

void addQuestion(const string & filename) {
    ofstream file(filename, ios::app);

    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "for writing. \n";
        return;
    }

    cin.ignore();
    string text; 
    cout << "Enter the question: ";
    getline(cin, text);

    int numOptions;
    cout << "Enter number of options: ";
    cin >> numOptions;
    cin.ignore();

    vector<string> options(numOptions);

    for (int i = 0; i < numOptions; i++) {
        cout << "Enter option " << i + 1 << ": ";
        getline(cin, options[i]);
    }

    int correct;
    cout << "Enter the correct option, number 1-" << numOptions <<": ";
    cin >> correct;

    file << text << "\n";
    file << numOptions << "\n";

    for (const auto& opts : options) 
        file << opts << "\n";
    
    file << correct - 1 << "\n"; //store as zero-based index

    
    cout << "Question added successfully.\n";
}*/