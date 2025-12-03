#ifndef USER_SYSTEM_H
#define USER_SYSTEM_H

#include <vector>
#include <string>
#include <map>

using namespace std;
// User structur
struct User {
    string username;    // the user's login name
    string password;    // the user's password
    int highScore = 0;  // user's highest quiz score
};

// Manages users: loading/saving, registering, login, and leaderboard
class UserSystem {
private:
    map<string, User> users; // maps a username -> User struct for quick lookup
    string currentUser;      // the username of whoever is currently logged in (empty if none)
public:
    UserSystem();            // constructor: set up the system (often loads users from file)
    void loadUsers();        // read users from persistent storage into `users`
    void saveUsers();        // write the `users` map back to persistent storage

    bool registerUser(const string & username, const string & password); // add a new user, returns true on success
    bool login(const string & username, const string & password);       // check inputs and sets the `currentUser` if valid
    void updateHighScore(int score);     // update the logged-in user's high score if their `score` is higher
    void showLeaderboard() const;        // print or display users highscores
    
    // Return the username of the currently logged-in user (or empty string if none)
    string getCurrentUser() const { 
        return currentUser; }
    
};

#endif