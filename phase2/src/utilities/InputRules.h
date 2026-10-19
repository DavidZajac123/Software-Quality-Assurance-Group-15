#pragma once

#include <string>

#include "FixedWidthFormat.h"

// Holds shared Front End limits and validates typed usernames and game names.
class InputRules {
public:
    static constexpr std::size_t MAX_USERNAME_LENGTH =
        FixedWidthFormat::USERNAME_WIDTH;

    static constexpr std::size_t MAX_GAME_NAME_LENGTH =
        FixedWidthFormat::GAME_NAME_WIDTH;

    static constexpr long long MAX_PRICE_CENTS = 99999;
    static constexpr long long MAX_CREDIT_ADDED_PER_SESSION_CENTS = 100000;
    static constexpr long long MAX_BALANCE_CENTS = 99999999;

    // Returns true when the username is 1 to 15 characters long
    // and does not begin or end with a space.
    static bool isValidUsername(const std::string& username);

    // Returns true when the game name is 1 to 26 characters long
    // and does not begin or end with a space.
    static bool isValidGameName(const std::string& gameName);
};