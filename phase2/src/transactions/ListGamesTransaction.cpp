#include "ListGamesTransaction.h"

#include "../io/Console.h"
#include "../session/Session.h"
#include "../utilities/Money.h"

// Returns the command word that selects the list_games transaction.
std::string ListGamesTransaction::code() const {
    return "list_games";
}

// Displays every game currently available for purchase.
// This transaction does not write a DTF record.
void ListGamesTransaction::execute(
    Session& session,
    Console& console,
    DailyTransactionWriter& dtfWriter
) {
    (void)dtfWriter;

    const auto availableGames = session.listings();

    if (availableGames.empty()) {
        console.showMessage("No games available.");
        return;
    }

    for (const auto& entry : availableGames) {
        const GameListing& listing = entry.second;

        console.showMessage(
            listing.gameName + " | " +
            listing.sellerUsername + " | $" +
            Money::toDisplay(listing.priceCents)
        );
    }
}