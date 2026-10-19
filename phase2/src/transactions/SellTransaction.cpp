#include "SellTransaction.h"

#include "../io/Console.h"
#include "../io/DailyTransactionWriter.h"
#include "../session/Session.h"
#include "../utilities/InputRules.h"
#include "../utilities/Money.h"

std::string SellTransaction::code() const {
    return "sell";
}

bool SellTransaction::isPermittedFor(UserType type) const {
    return type != UserType::BuyStandard;
}

std::string SellTransaction::validateInput(
    Session& session,
    const std::string& gameName,
    const std::string& priceText,
    long long& priceCents
) const {
    if (!InputRules::isValidGameName(gameName)) {
        return "Error: invalid game name.";
    }

    if (session.isGameNameTaken(gameName)) {
        return "Error: game name already exists.";
    }

    if (!Money::parse(priceText, priceCents)) {
        return "Error: invalid price.";
    }

    if (priceCents < 0 || priceCents > InputRules::MAX_PRICE_CENTS) {
        return "Error: price must be between 0.00 and 999.99.";
    }

    return "";
}

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

    console.showMessage("Game listed successfully.");
}