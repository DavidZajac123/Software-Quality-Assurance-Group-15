#pragma once

#include <cstddef>
#include <map>
#include <string>
#include <vector>

#include "../session/GameListing.h"
#include "../session/OwnedGame.h"
#include "../session/UserAccount.h"

// Reads the Current User Accounts, Available Games, and Game Collection
// master files and converts their fixed-width records into in-memory data.
class MasterFileReader {
private:
    std::string userAccountsPath_;
    std::string availableGamesPath_;
    std::string gameCollectionPath_;

    // Reads records from a master file until its END record is reached.
    std::vector<std::string> readRecordLines(
        const std::string& path,
        std::size_t keyFieldWidth
    );

public:
    // Stores the paths of the three master files used by the Front End.
    MasterFileReader(
        const std::string& userAccountsPath,
        const std::string& availableGamesPath,
        const std::string& gameCollectionPath
    );

    // Returns true only when all three master files can be opened.
    bool canOpenAllFiles() const;

    // Reads the Current User Accounts File into a map keyed by username.
    std::map<std::string, UserAccount> readUserAccounts();

    // Reads the Available Games File into a map keyed by game name.
    std::map<std::string, GameListing> readAvailableGames();

    // Reads the Game Collection File into a list of owned-game records.
    std::vector<OwnedGame> readGameCollection();
};