#include "Session.h"

#include <utility>

// Starts a new logged-in session using fresh master-file data
// and clears all per-session tracking information.
void Session::begin(
    const std::string& username,
    std::map<std::string, UserAccount> accounts,
    std::map<std::string, GameListing> listings,
    std::vector<OwnedGame> collection
) {
    loggedIn_ = true;
    currentUsername_ = username;

    accounts_ = std::move(accounts);
    listings_ = std::move(listings);
    collection_ = std::move(collection);

    gamesListedThisSession_.clear();
    creditAddedThisSession_.clear();
}

// Ends the current session and clears all stored session state.
void Session::end() {
    loggedIn_ = false;
    currentUsername_.clear();

    accounts_.clear();
    listings_.clear();
    collection_.clear();

    gamesListedThisSession_.clear();
    creditAddedThisSession_.clear();
}

// Returns whether a user is currently logged in.
bool Session::isLoggedIn() const {
    return loggedIn_;
}

// Returns the account belonging to the currently logged-in user.
UserAccount Session::currentUser() const {
    auto account = accounts_.find(currentUsername_);

    if (account != accounts_.end()) {
        return account->second;
    }

    return UserAccount{};
}

// Returns the account with the given username,
// or nullptr if that account does not exist.
UserAccount* Session::findAccount(const std::string& username) {
    auto account = accounts_.find(username);

    if (account == accounts_.end()) {
        return nullptr;
    }

    return &account->second;
}

// Returns all active accounts in username order.
std::map<std::string, UserAccount> Session::accounts() const {
    return accounts_;
}

// Adds a newly created account to the current session.
void Session::addAccount(const UserAccount& account) {
    accounts_[account.username] = account;
}

// Removes an account and cancels that user's available game listings.
void Session::removeAccount(const std::string& username) {
    accounts_.erase(username);

    for (auto listing = listings_.begin(); listing != listings_.end();) {
        if (listing->second.sellerUsername == username) {
            listing = listings_.erase(listing);
        } else {
            ++listing;
        }
    }
}

// Adds credit to an account and tracks the amount added during this session.
void Session::addCredit(
    const std::string& username,
    long long amountCents
) {
    UserAccount* account = findAccount(username);

    if (account == nullptr) {
        return;
    }

    account->creditCents += amountCents;
    creditAddedThisSession_[username] += amountCents;
}

// Transfers the specified amount of credit from one account to another.
void Session::transferCredit(
    const std::string& fromUsername,
    const std::string& toUsername,
    long long amountCents
) {
    UserAccount* fromAccount = findAccount(fromUsername);
    UserAccount* toAccount = findAccount(toUsername);

    if (fromAccount == nullptr || toAccount == nullptr) {
        return;
    }

    fromAccount->creditCents -= amountCents;
    toAccount->creditCents += amountCents;
}

// Returns the total credit added to an account during this session.
long long Session::creditAddedThisSession(
    const std::string& username
) const {
    auto amount = creditAddedThisSession_.find(username);

    if (amount == creditAddedThisSession_.end()) {
        return 0;
    }

    return amount->second;
}

// Returns the available listing with the given game name,
// or nullptr if no matching listing exists.
GameListing* Session::findListing(const std::string& gameName) {
    auto listing = listings_.find(gameName);

    if (listing == listings_.end()) {
        return nullptr;
    }

    return &listing->second;
}

// Returns all games currently available for purchase.
std::map<std::string, GameListing> Session::listings() const {
    return listings_;
}

// Returns whether a game name is already listed or was reserved this session.
bool Session::isGameNameTaken(const std::string& gameName) const {
    return listings_.find(gameName) != listings_.end()
        || gamesListedThisSession_.find(gameName)
            != gamesListedThisSession_.end();
}

// Reserves a game name so that it cannot be reused during this session.
void Session::reserveGameName(const std::string& gameName) {
    gamesListedThisSession_.insert(gameName);
}

// Returns whether the specified user already owns the named game.
bool Session::ownsGame(
    const std::string& username,
    const std::string& gameName
) const {
    for (const OwnedGame& ownedGame : collection_) {
        if (
            ownedGame.ownerUsername == username &&
            ownedGame.gameName == gameName
        ) {
            return true;
        }
    }

    return false;
}

// Adds a purchased game to the user's collection for the current session.
void Session::addOwnedGame(
    const std::string& username,
    const std::string& gameName
) {
    OwnedGame ownedGame;
    ownedGame.ownerUsername = username;
    ownedGame.gameName = gameName;

    collection_.push_back(ownedGame);
}