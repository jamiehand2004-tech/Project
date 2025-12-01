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
    void saveUsers();
    void loadUsers();
    
public:
    UserSystem();
    bool registerUser(const string & username, const string & password);
    bool login(const string & username, const string & password);

    void loadUsers();
    void saveUsers();
    
    void updateHighScore(int score);
    void showLeaderboard() const;
    
    string getCurrentUser() const;
    
};

#endif