#include "InputRules.h"

bool InputRules::isValidUsername(const std::string& username) {
    if (username.empty() || username.size() > MAX_USERNAME_LENGTH) {
        return false;
    }

    return username.front() != ' ' && username.back() != ' ';
}

bool InputRules::isValidGameName(const std::string& gameName) {
    if (gameName.empty() || gameName.size() > MAX_GAME_NAME_LENGTH) {
        return false;
    }

    return gameName.front() != ' ' && gameName.back() != ' ';
}