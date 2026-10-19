#pragma once

#include <string>

#include "../session/UserType.h"

// Converts between UserType values, two-letter file codes,
// and the account-type keywords entered by users.
class UserTypeCodes {
public:
    // Converts a UserType value to its two-letter master-file code.
    static std::string toFileCode(UserType type);

    // Converts a two-letter master-file code into a UserType.
    static bool fromFileCode(
        const std::string& code,
        UserType& type
    );

    // Converts an account-type keyword entered by a user into a UserType.
    static bool fromKeyword(
        const std::string& keyword,
        UserType& type
    );
};