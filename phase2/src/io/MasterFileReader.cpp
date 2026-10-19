#include "MasterFileReader.h"

#include <fstream>

#include "../utilities/FixedWidthFormat.h"
#include "../utilities/Money.h"
#include "../utilities/UserTypeCodes.h"

MasterFileReader::MasterFileReader(
    const std::string& userAccountsPath,
    const std::string& availableGamesPath,
    const std::string& gameCollectionPath
)
    : userAccountsPath_(userAccountsPath),
      availableGamesPath_(availableGamesPath),
      gameCollectionPath_(gameCollectionPath) {
}

bool MasterFileReader::canOpenAllFiles() const {
    std::ifstream userAccountsFile(userAccountsPath_);
    std::ifstream availableGamesFile(availableGamesPath_);
    std::ifstream gameCollectionFile(gameCollectionPath_);

    return userAccountsFile.is_open()
        && availableGamesFile.is_open()
        && gameCollectionFile.is_open();
}

std::vector<std::string> MasterFileReader::readRecordLines(
    const std::string& path,
    std::size_t keyFieldWidth
) {
    std::ifstream file(path);
    std::vector<std::string> records;
    std::string line;

    while (std::getline(file, line)) {
        // Remove the carriage return from Windows-style line endings.
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        std::string keyField =
            FixedWidthFormat::extractField(
                line,
                0,
                keyFieldWidth
            );

        if (keyField == "END") {
            break;
        }

        records.push_back(line);
    }

    return records;
}

std::map<std::string, UserAccount>
MasterFileReader::readUserAccounts() {
    std::map<std::string, UserAccount> accounts;

    std::vector<std::string> lines =
        readRecordLines(
            userAccountsPath_,
            FixedWidthFormat::USERNAME_WIDTH
        );

    for (const std::string& line : lines) {
        if (line.size() != 28) {
            continue;
        }

        std::string username =
            FixedWidthFormat::extractField(
                line,
                0,
                FixedWidthFormat::USERNAME_WIDTH
            );

        std::string typeCode =
            FixedWidthFormat::extractField(
                line,
                16,
                FixedWidthFormat::TYPE_WIDTH
            );

        std::string creditText =
            FixedWidthFormat::extractField(
                line,
                19,
                FixedWidthFormat::CREDIT_WIDTH
            );

        UserType type;
        long long creditCents = 0;

        if (!UserTypeCodes::fromFileCode(typeCode, type)) {
            continue;
        }

        if (!Money::parse(creditText, creditCents)) {
            continue;
        }

        UserAccount account;
        account.username = username;
        account.type = type;
        account.creditCents = creditCents;

        accounts[username] = account;
    }

    return accounts;
}

std::map<std::string, GameListing>
MasterFileReader::readAvailableGames() {
    std::map<std::string, GameListing> listings;

    std::vector<std::string> lines =
        readRecordLines(
            availableGamesPath_,
            FixedWidthFormat::GAME_NAME_WIDTH
        );

    for (const std::string& line : lines) {
        if (line.size() != 49) {
            continue;
        }

        std::string gameName =
            FixedWidthFormat::extractField(
                line,
                0,
                FixedWidthFormat::GAME_NAME_WIDTH
            );

        std::string sellerUsername =
            FixedWidthFormat::extractField(
                line,
                27,
                FixedWidthFormat::USERNAME_WIDTH
            );

        std::string priceText =
            FixedWidthFormat::extractField(
                line,
                43,
                FixedWidthFormat::PRICE_WIDTH
            );

        long long priceCents = 0;

        if (!Money::parse(priceText, priceCents)) {
            continue;
        }

        GameListing listing;
        listing.gameName = gameName;
        listing.sellerUsername = sellerUsername;
        listing.priceCents = priceCents;

        listings[gameName] = listing;
    }

    return listings;
}

std::vector<OwnedGame>
MasterFileReader::readGameCollection() {
    std::vector<OwnedGame> collection;

    std::vector<std::string> lines =
        readRecordLines(
            gameCollectionPath_,
            FixedWidthFormat::GAME_NAME_WIDTH
        );

    for (const std::string& line : lines) {
        if (line.size() != 42) {
            continue;
        }
        
        std::string gameName =
            FixedWidthFormat::extractField(
                line,
                0,
                FixedWidthFormat::GAME_NAME_WIDTH
            );

        std::string ownerUsername =
            FixedWidthFormat::extractField(
                line,
                27,
                FixedWidthFormat::USERNAME_WIDTH
            );

        OwnedGame ownedGame;
        ownedGame.gameName = gameName;
        ownedGame.ownerUsername = ownerUsername;

        collection.push_back(ownedGame);
    }

    return collection;
}