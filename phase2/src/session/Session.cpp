#include "Session.h"

#include <utility>

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

void Session::end() {
    loggedIn_ = false;
    currentUsername_.clear();

    accounts_.clear();
    listings_.clear();
    collection_.clear();

    gamesListedThisSession_.clear();
    creditAddedThisSession_.clear();
}

bool Session::isLoggedIn() const {
    return loggedIn_;
}

UserAccount Session::currentUser() const {
    auto account = accounts_.find(currentUsername_);

    if (account != accounts_.end()) {
        return account->second;
    }

    return UserAccount{};
}

UserAccount* Session::findAccount(const std::string& username) {
    auto account = accounts_.find(username);

    if (account == accounts_.end()) {
        return nullptr;
    }

    return &account->second;
}

std::map<std::string, UserAccount> Session::accounts() const {
    return accounts_;
}

void Session::addAccount(const UserAccount& account) {
    accounts_[account.username] = account;
}

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

long long Session::creditAddedThisSession(
    const std::string& username
) const {
    auto amount = creditAddedThisSession_.find(username);

    if (amount == creditAddedThisSession_.end()) {
        return 0;
    }

    return amount->second;
}

GameListing* Session::findListing(const std::string& gameName) {
    auto listing = listings_.find(gameName);

    if (listing == listings_.end()) {
        return nullptr;
    }

    return &listing->second;
}

std::map<std::string, GameListing> Session::listings() const {
    return listings_;
}

bool Session::isGameNameTaken(const std::string& gameName) const {
    return listings_.find(gameName) != listings_.end()
        || gamesListedThisSession_.find(gameName)
            != gamesListedThisSession_.end();
}

void Session::reserveGameName(const std::string& gameName) {
    gamesListedThisSession_.insert(gameName);
}

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

void Session::addOwnedGame(
    const std::string& username,
    const std::string& gameName
) {
    OwnedGame ownedGame;
    ownedGame.ownerUsername = username;
    ownedGame.gameName = gameName;

    collection_.push_back(ownedGame);
}