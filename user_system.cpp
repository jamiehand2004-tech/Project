// user_system.cpp
#include "user_system.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

UserSystem::UserSystem() {
    loadUsers();
}

void UserSystem::loadUsers() {
    ifstream file("users.txt");
    if (!file.is_open()) return;

    users.clear();
    while (!file.eof()) {
        User u;
        file >> u.username >> u.password >> u.highScore;
        if (!u.username.empty())
            users[u.username] = u;
    }
    file.close();
}

void UserSystem::saveUsers() {
    ofstream file("users.txt");
    for (auto & pair : users) {
        file << pair.second.username << " "
             << pair.second.password << " "
             << pair.second.highScore << "\n";
    }
}

bool UserSystem::registerUser(const string & username, const string & password) {
    if (users.count(username)) {
        cout << "Username already exists.\n";
        return false;
    }
    users[username] = {username, password, 0};
    saveUsers();
    cout << "User registered.\n";
    return true;
}

bool UserSystem::login(const string & username, const string & password) {
    if (!users.count(username)) {
        cout << "User not found.\n";
        return false;
    }
    if (users[username].password != password) {
        cout << "Incorrect password.\n";
        return false;
    }
    currentUser = username;
    cout << "User logged in.\n";
    return true;
}

void UserSystem::updateHighScore(int score) {
    if (currentUser.empty()) return;
    if (users[currentUser].highScore < score) {
        users[currentUser].highScore = score;
        saveUsers();
    }
}

void UserSystem::showLeaderboard() const {
    vector<User> ranking;
    for (const auto & pair : users) 
        ranking.push_back(pair.second);

    sort(ranking.begin(), ranking.end(), 
        [](const User & a, const User & b) {
            return a.highScore > b.highScore;
    });

    cout << "\n=== Leaderboard ===\n";
    for (auto & user : ranking) {
        cout << user.username << ": " << user.highScore << "\n";
    }
}