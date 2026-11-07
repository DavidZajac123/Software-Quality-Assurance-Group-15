#include "SellTransaction.h"

#include "../io/Console.h"
#include "../io/DailyTransactionWriter.h"
#include "../session/Session.h"
#include "../utilities/InputRules.h"
#include "../utilities/Money.h"

// Returns the command word that selects the sell transaction.
std::string SellTransaction::code() const {
    return "sell";
}

// Returns false for buy-standard accounts and true for all other account types.
bool SellTransaction::isPermittedFor(UserType type) const {
    return type != UserType::BuyStandard;
}

// Validates the game name and price.
// Returns an error message when invalid, or an empty string when valid.
std::string SellTransaction::validateInput(
    Session& session,
    const std::string& gameName,
    const std::string& priceText,
    long long& priceCents
) const {
    if (!InputRules::isValidGameName(gameName)) {
        return "Error: game name must be 1 to 26 characters, "
            "with no space at the start or end.";
    }

    if (session.isGameNameTaken(gameName)) {
        return "Error: a game named \"" + gameName + "\" is already for sale.";
    }

    if (
        !Money::parse(priceText, priceCents) ||
        priceCents > InputRules::MAX_PRICE_CENTS
    ) {
        return "Error: price must be an amount from 0.00 to 999.99.";
    }

    return "";
}

// Prompts for a game name and price, validates them,
// reserves the game name, and records the 03 DTF entry.
void SellTransaction::execute(
    Session& session,
    Console& console,
    DailyTransactionWriter& dtfWriter
) {
    std::string gameName;
    std::string priceText;

    if (!console.prompt("Enter game name:", gameName)) {
        return;
    }

    if (!console.prompt("Enter price:", priceText)) {
        return;
    }

    long long priceCents = 0;

    const std::string error =
        validateInput(session, gameName, priceText, priceCents);

    if (!error.empty()) {
        console.showMessage(error);
        return;
    }

    const std::string sellerUsername =
        session.currentUser().username;

    session.reserveGameName(gameName);

    dtfWriter.recordSell(
        gameName,
        sellerUsername,
        priceCents
    );

    console.showMessage(
        "Game listed: " + gameName + " for " +
        Money::toDisplay(priceCents) + "."
    );
}