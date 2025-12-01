#ifndef USER_SYSTEM_H
#define USER_SYSTEM_H

#include <vector>
#include <string>
#include <map>

using namespace std;

struct User {
    string username;    // username of user
    string password;    // password of user
    int highScore = 0;      // highest score achieved by user (saved for Leaderboard)
};

class UserSystem {
private:
    map<string, User> users; // map of username to User struct
    string currentUser;  // currently logged in user
public:
    UserSystem();
    void loadUsers();
    void saveUsers();

    bool registerUser(const string & username, const string & password);
    bool login(const string & username, const string & password);
    void updateHighScore(int score);
    void showLeaderboard() const;
    
    string getCurrentUser() const { 
        return currentUser; } 
    
};

#endif