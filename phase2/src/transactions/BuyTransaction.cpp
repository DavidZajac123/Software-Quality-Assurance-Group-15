#include "BuyTransaction.h"

#include "../io/Console.h"
#include "../io/DailyTransactionWriter.h"
#include "../session/Session.h"

std::string BuyTransaction::code() const {
    return "buy";
}

bool BuyTransaction::isPermittedFor(UserType type) const {
    return type != UserType::SellStandard;
}

std::string BuyTransaction::validateInput(
    Session& session,
    const std::string& gameName,
    const std::string& sellerUsername,
    long long& priceCents
) const {
    GameListing* listing = session.findListing(gameName);

    if (listing == nullptr) {
        return "Error: game is not available.";
    }

    if (listing->sellerUsername != sellerUsername) {
        return "Error: seller does not match listing.";
    }

    if (session.findAccount(sellerUsername) == nullptr) {
        return "Error: seller account does not exist.";
    }

    const UserAccount buyer = session.currentUser();

    if (buyer.username == sellerUsername) {
        return "Error: cannot buy your own game.";
    }

    if (session.ownsGame(buyer.username, gameName)) {
        return "Error: buyer already owns this game.";
    }

    priceCents = listing->priceCents;

    if (buyer.creditCents < priceCents) {
        return "Error: insufficient credit.";
    }

    return "";
}

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

    if (!console.prompt("Enter seller username:", sellerUsername)) {
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

    console.showMessage("Game purchased successfully.");
}