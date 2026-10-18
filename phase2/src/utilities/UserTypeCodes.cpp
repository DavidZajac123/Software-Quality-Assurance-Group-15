#include "UserTypeCodes.h"

#include <algorithm>
#include <cctype>

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