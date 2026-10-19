#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

#include "GameListing.h"
#include "OwnedGame.h"
#include "UserAccount.h"

// Holds all Front End state for one logged-in session, including
// accounts, available games, owned games, and per-session tracking data.
class Session {
private:
    bool loggedIn_ = false;
    std::string currentUsername_;

    std::map<std::string, UserAccount> accounts_;
    std::map<std::string, GameListing> listings_;
    std::vector<OwnedGame> collection_;

    std::set<std::string> gamesListedThisSession_;
    std::map<std::string, long long> creditAddedThisSession_;

public:
    // Starts a session for the given user using freshly loaded master-file data
    // and clears all per-session tracking information.
    void begin(
        const std::string& username,
        std::map<std::string, UserAccount> accounts,
        std::map<std::string, GameListing> listings,
        std::vector<OwnedGame> collection
    );

    // Ends the current session and clears its login state.
    void end();

    // Returns true while a user is logged in.
    bool isLoggedIn() const;

    // Returns the account belonging to the currently logged-in user.
    UserAccount currentUser() const;

    // Returns the account with the given username, or nullptr if it does not exist.
    UserAccount* findAccount(const std::string& username);

    // Adds a newly created account to the current session.
    void addAccount(const UserAccount& account);

    // Removes an account and cancels that user's games currently for sale.
    void removeAccount(const std::string& username);

    // Adds credit to an account and tracks the amount added during this session.
    void addCredit(
        const std::string& username,
        long long amountCents
    );

    // Transfers credit from one existing account to another.
    void transferCredit(
        const std::string& fromUsername,
        const std::string& toUsername,
        long long amountCents
    );

    // Returns how much credit has been added to an account during this session.
    long long creditAddedThisSession(const std::string& username) const;

    // Returns the available listing with the given game name,
    // or nullptr if the game is not available.
    GameListing* findListing(const std::string& gameName);

    // Returns all games currently available for purchase.
    std::map<std::string, GameListing> listings() const;

    // Returns true if the game name is already in use or was reserved this session.
    bool isGameNameTaken(const std::string& gameName) const;

    // Reserves a game name listed during this session.
    void reserveGameName(const std::string& gameName);

    // Returns true if the given user already owns the named game.
    bool ownsGame(
        const std::string& username,
        const std::string& gameName
    ) const;

    // Adds a purchased game to the user's collection for the current session.
    void addOwnedGame(
        const std::string& username,
        const std::string& gameName
    );
};