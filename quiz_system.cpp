#include "quiz_system.h"
#include <iostream>
#include <fstream>
#include <limits> // for numeric_limits when clearing input

#include "quiz_system.h"
#include <iostream>
#include <fstream>
#include <limits> // used to clear and ignore bad input from cin

using namespace std;

// Loads questions from file
void QuizSystem::loadFromFile(const string & filename) {
    questions = loadQuestions(filename); // delegate to quiz_reader helper
}

// Save all questions to a file (overwrites existing file)
void QuizSystem::saveToFile(const string & filename) const {
    ofstream file(filename); // open file for writing

    // If the file couldn't be opened, report and exit the function
    if (!file.is_open()) {
        cerr << "Error: Cannot write questions.\n";
        return;
    }
    
    // Write each question's text, option count, option lines, and correct answer
    for (const auto & q : questions) {
        file << q.text << "\n";
        file << q.options.size() << "\n";
        for (const auto & opt : q.options)
            file << opt << "\n";
        file << q.correctAnswer << "\n";
    }
}
// Adds a question to the quiz
void QuizSystem::addQuestion(const Question & q) {
    questions.push_back(q);
}

// Prompt the user to create a question and append it to filename
void QuizSystem::addingQuestion(const string & filename) {
    ofstream file(filename, ios::app);
    if(!file.is_open()) {
        cerr << "Error: Could not open " << filename << " for writing.\n";
        return;
    }

    // Create a Question and read its text
    Question q;
    cout << "Enter the question text: ";
    // ensure any leftover newline is cleared before getline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, q.text);

    // Read the number of options with validation
    int numOptions;
    cout << "Enter number of options: ";
    while (!(cin >> numOptions) || numOptions <= 0) {
        cout << "Invalid input. Please enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // consume the newline left after reading the integer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    q.options.resize(numOptions);
    for (int i = 0; i < numOptions; i++) {
        cout << "Enter option " << i + 1 << ": ";
        getline(cin, q.options[i]); // read each option line
    }

    // Read and validate which option is correct (1-based input)
    int correct;
    cout << "Enter correct option number (1-" << numOptions << "): ";
    while (!(cin >> correct) || correct < 1 || correct > numOptions) {
        cout << "Invalid input. Please enter a number between 1 and " << numOptions << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    // convert to 0-based index used by Question
    q.correctAnswer = correct - 1;

    // Persist the question to the file and give feedback
    file << q.text << "\n";
    file << numOptions << "\n";
    for (auto & opt : q.options) file << opt << "\n";
    file << q.correctAnswer << "\n";

    cout << "Question added successfully.\n";
}

//Running the quiz
int QuizSystem::takeQuiz(const string & resultsFile, 
                         const string & username) {
    if (questions.empty()) {
        cout << "No questions available.\n";
        return 0;
    }

    int score = 0;
    for (const auto & q : questions) {
        cout << "\n" << q.text << "\n"; // show question text
        for (size_t i = 0; i < q.options.size(); i++) 
            cout << i + 1 << ". " << q.options[i] << endl; // list options

        int ans;
        cout << "Your answer: ";
        cin >> ans; // read user's numeric answer

        if (ans - 1 == q.correctAnswer) score++; // increment on correct answer
    }

    cout << "\nYour score: " << score << "/ " << questions.size() << "\n";

    // save result to results file
    ofstream out(resultsFile, ios::app);
    if (out.is_open()) {
        out << username << " scored " << score << "/" << questions.size() << ".\n";
    }
    return score;
}