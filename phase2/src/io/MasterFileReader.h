#pragma once

#include <cstddef>
#include <map>
#include <string>
#include <vector>

#include "../session/GameListing.h"
#include "../session/OwnedGame.h"
#include "../session/UserAccount.h"

class MasterFileReader {
private:
    std::string userAccountsPath_;
    std::string availableGamesPath_;
    std::string gameCollectionPath_;

    std::vector<std::string> readRecordLines(
        const std::string& path,
        std::size_t keyFieldWidth
    );

public:
    MasterFileReader(
        const std::string& userAccountsPath,
        const std::string& availableGamesPath,
        const std::string& gameCollectionPath
    );

    bool canOpenAllFiles() const;

    std::map<std::string, UserAccount> readUserAccounts();
    std::map<std::string, GameListing> readAvailableGames();
    std::vector<OwnedGame> readGameCollection();
};