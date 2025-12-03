// user_system.cpp
#include "user_system.h" // header that declares UserSystem and User
#include <iostream>      // for input/output (cout)
#include <fstream>       // for file read/write (ifstream/ofstream)
#include <algorithm>     // for std::sort

using namespace std;     // shorten common std:: names like string, cout

// Constructor: when a UserSystem is created, load users from disk
UserSystem::UserSystem() {
    loadUsers(); // loads users from "users.txt"
}

// Read users from the file "users.txt" into the `users` map
void UserSystem::loadUsers() {
    ifstream file("users.txt");     // open file for reading
    if (!file.is_open()) return;      // if file doesn't exist or can't open, do nothing

    users.clear();                    // clear any existing users in memory
    while (!file.eof()) {             // while there's more to read
        User u;                       // temp User to read into
        file >> u.username >> u.password >> u.highScore; // read fields separated by whitespace
        if (!u.username.empty())      // if a username was read (file line wasn't blank)
            users[u.username] = u;    // store the user in the map keyed by username
    }
    file.close();                     // close the file when done
}

// Write all users from the `users` map to "users.txt"
void UserSystem::saveUsers() {
    ofstream file("users.txt");     // open file for writing (overwrites existing file)
    for (auto & pair : users) {      // iterate over each map entry
        // write username, password, and highScore separated by blank spaces
        file << pair.second.username << " "
             << pair.second.password << " "
             << pair.second.highScore << "\n";
    }
}

// Create a new user if the username doesn't already exist
bool UserSystem::registerUser(const string & username, const string & password) {
    if (users.count(username)) {             // check if username already in map
        cout << "Username already exists.\n"; // report failure to user
        return false;                         // registration failed
    }
    users[username] = {username, password, 0}; // add new User with highScore 0
    saveUsers();                              // persist change to disk
    cout << "User registered.\n";           // give feedback
    return true;                              // success
}

// Authenticate existing user by username and password
bool UserSystem::login(const string & username, const string & password) {
    if (!users.count(username)) {             // username not in map
        cout << "User not found.\n";        // inform caller
        return false;                         // login failed
    }
    if (users[username].password != password) { // password mismatch
        cout << "Incorrect password.\n";    // inform caller
        return false;                         // login failed
    }
    currentUser = username;                   // set the logged-in user
    cout << "User logged in.\n";            // give feedback
    return true;                              // success
}

// Update the current user's high score if the new score is higher
void UserSystem::updateHighScore(int score) {
    if (currentUser.empty()) return;          // no user logged in -> nothing to do
    if (users[currentUser].highScore < score) { // new score is better
        users[currentUser].highScore = score; // save new high score in memory
        saveUsers();                           // persist the updated score
    }
}

// Display all users sorted by their high score (descending)
void UserSystem::showLeaderboard() const {
    vector<User> ranking;                    // temporary list to sort users
    for (const auto & pair : users)          // copy users from map into vector
        ranking.push_back(pair.second);

    // sort users so highest score comes first
    sort(ranking.begin(), ranking.end(), 
        [](const User & a, const User & b) {
            return a.highScore > b.highScore; // descending order by highScore
    });

    cout << "\n=== Leaderboard ===\n";       // header for leaderboard output
    for (auto & user : ranking) {            // print each username and score
        cout << user.username << ": " << user.highScore << "\n";
    }
}