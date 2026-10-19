#include "UserTypeCodes.h"

#include <algorithm>
#include <cctype>

// Converts a UserType value to its two-letter master-file code.
std::string UserTypeCodes::toFileCode(UserType type) {
    switch (type) {
        case UserType::Admin:
            return "AA";

        case UserType::FullStandard:
            return "FS";

        case UserType::BuyStandard:
            return "BS";

        case UserType::SellStandard:
            return "SS";
    }

    return "";
}

// Converts a two-letter master-file account code into a UserType.
// Returns false when the code is not recognized.
bool UserTypeCodes::fromFileCode(
    const std::string& code,
    UserType& type
) {
    if (code == "AA") {
        type = UserType::Admin;
        return true;
    }

    if (code == "FS") {
        type = UserType::FullStandard;
        return true;
    }

    if (code == "BS") {
        type = UserType::BuyStandard;
        return true;
    }

    if (code == "SS") {
        type = UserType::SellStandard;
        return true;
    }

    return false;
}

// Converts a typed account-type keyword into a UserType.
// Returns false when the keyword is not recognized.
bool UserTypeCodes::fromKeyword(
    const std::string& keyword,
    UserType& type
) {
    std::string normalized = keyword;

    std::transform(
        normalized.begin(),
        normalized.end(),
        normalized.begin(),
        [](unsigned char character) {
            return static_cast<char>(std::tolower(character));
        }
    );

    if (normalized == "admin") {
        type = UserType::Admin;
        return true;
    }

    if (normalized == "full-standard") {
        type = UserType::FullStandard;
        return true;
    }

    if (normalized == "buy-standard") {
        type = UserType::BuyStandard;
        return true;
    }

    if (normalized == "sell-standard") {
        type = UserType::SellStandard;
        return true;
    }

    return false;
}