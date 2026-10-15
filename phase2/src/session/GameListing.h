#pragma once

#include <string>

// Represents one record from the Available Games File.
// Monetary values are stored as whole cents.
struct GameListing {
    std::string gameName;
    std::string sellerUsername;
    long long priceCents = 0;
};
