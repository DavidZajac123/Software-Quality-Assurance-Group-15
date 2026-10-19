#include "InputRules.h"

// Returns whether a username satisfies the configured length
// and leading/trailing-space rules.
bool InputRules::isValidUsername(const std::string& username) {
    if (username.empty() || username.size() > MAX_USERNAME_LENGTH) {
        return false;
    }

    return username.front() != ' ' && username.back() != ' ';
}

// Returns whether a game name satisfies the configured length
// and leading/trailing-space rules.
bool InputRules::isValidGameName(const std::string& gameName) {
    if (gameName.empty() || gameName.size() > MAX_GAME_NAME_LENGTH) {
        return false;
    }

    return gameName.front() != ' ' && gameName.back() != ' ';
}