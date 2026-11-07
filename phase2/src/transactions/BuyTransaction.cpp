#include "BuyTransaction.h"

#include "../io/Console.h"
#include "../io/DailyTransactionWriter.h"
#include "../session/Session.h"
#include "../utilities/Money.h"

// Returns the command word that selects the buy transaction.
std::string BuyTransaction::code() const {
    return "buy";
}

// Returns false for sell-standard accounts and true for all other account types.
bool BuyTransaction::isPermittedFor(UserType type) const {
    return type != UserType::SellStandard;
}

// Validates the requested purchase and provides the listing price.
// Returns an error message when invalid, or an empty string when valid.
std::string BuyTransaction::validateInput(
    Session& session,
    const std::string& gameName,
    const std::string& sellerUsername,
    long long& priceCents
) const {
    GameListing* listing = session.findListing(gameName);

    // A game listed this session, or sold by an account deleted this
    // session, is not in the listings, so it is not for sale either.
    if (
        listing == nullptr ||
        listing->sellerUsername != sellerUsername ||
        session.findAccount(sellerUsername) == nullptr
    ) {
        return "Error: \"" + gameName + "\" is not for sale by \"" +
            sellerUsername + "\".";
    }

    const UserAccount buyer = session.currentUser();

    if (buyer.username == sellerUsername) {
        return "Error: you cannot buy your own game.";
    }

    if (session.ownsGame(buyer.username, gameName)) {
        return "Error: you already own \"" + gameName + "\".";
    }

    priceCents = listing->priceCents;

    if (buyer.creditCents < priceCents) {
        return "Error: not enough credit to buy \"" + gameName + "\".";
    }

    return "";
}

// Prompts for the game and seller, validates the purchase,
// transfers credit, records ownership, and writes the 04 DTF entry.
void BuyTransaction::execute(
    Session& session,
    Console& console,
    DailyTransactionWriter& dtfWriter
) {
    std::string gameName;
    std::string sellerUsername;

    if (!console.prompt("Enter game name:", gameName)) {
        return;
    }

    if (!console.prompt("Enter seller's username:", sellerUsername)) {
        return;
    }

    long long priceCents = 0;

    const std::string error =
        validateInput(
            session,
            gameName,
            sellerUsername,
            priceCents
        );

    if (!error.empty()) {
        console.showMessage(error);
        return;
    }

    const std::string buyerUsername =
        session.currentUser().username;

    session.transferCredit(
        buyerUsername,
        sellerUsername,
        priceCents
    );

    session.addOwnedGame(
        buyerUsername,
        gameName
    );

    dtfWriter.recordBuy(
        gameName,
        sellerUsername,
        buyerUsername,
        priceCents
    );

    console.showMessage(
        "Purchase successful: " + gameName + " from " + sellerUsername +
        " for " + Money::toDisplay(priceCents) + "."
    );
}