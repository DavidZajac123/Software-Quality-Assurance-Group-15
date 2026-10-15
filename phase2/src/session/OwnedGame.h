#pragma once

#include <string>

// Represents one record from the Game Collection File.
struct OwnedGame {
    std::string gameName;
    std::string ownerUsername;
};
