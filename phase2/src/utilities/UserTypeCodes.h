#pragma once

#include <string>

#include "../session/UserType.h"

// Converts between UserType values, two-letter file codes,
// and the account-type keywords entered by users.
class UserTypeCodes {
public:
    static std::string toFileCode(UserType type);

    static bool fromFileCode(
        const std::string& code,
        UserType& type
    );

    static bool fromKeyword(
        const std::string& keyword,
        UserType& type
    );
};