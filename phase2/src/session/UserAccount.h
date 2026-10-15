#pragma once

#include <string>
#include "UserType.h"

// Represents one record from the Current User Accounts File.
// Monetary values are stored as whole cents.
struct UserAccount {
    std::string username;
    UserType type;
    long long creditCents = 0;
};
