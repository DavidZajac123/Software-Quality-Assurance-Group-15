#include "ListGamesTransaction.h"

#include "../io/Console.h"
#include "../session/Session.h"
#include "../utilities/Money.h"

std::string ListGamesTransaction::code() const {
    return "list_games";
}

void ListGamesTransaction::execute(
    Session& session,
    Console& console,
    DailyTransactionWriter& dtfWriter
) {
    (void)dtfWriter;

    const auto availableGames = session.listings();

    for (const auto& entry : availableGames) {
        const GameListing& listing = entry.second;

        console.showMessage(
            listing.gameName + " | " +
            listing.sellerUsername + " | $" +
            Money::toDisplay(listing.priceCents)
        );
    }
}