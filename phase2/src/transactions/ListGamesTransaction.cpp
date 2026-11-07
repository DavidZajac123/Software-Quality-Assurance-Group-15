#include "ListGamesTransaction.h"

#include "../io/Console.h"
#include "../session/Session.h"
#include "../utilities/FixedWidthFormat.h"
#include "../utilities/Money.h"

// Returns the command word that selects the list_games transaction.
std::string ListGamesTransaction::code() const {
    return "list_games";
}

// Formats one game for sale: the name padded to 26 characters, the seller
// padded to 15 characters and the price, separated by single spaces.
std::string ListGamesTransaction::formatListing(const GameListing& listing) {
    return FixedWidthFormat::padRight(
               listing.gameName, FixedWidthFormat::GAME_NAME_WIDTH
           ) + " " +
           FixedWidthFormat::padRight(
               listing.sellerUsername, FixedWidthFormat::USERNAME_WIDTH
           ) + " " +
           Money::toDisplay(listing.priceCents);
}

// Displays a header, then every game currently available for purchase
// in name order.
// This transaction does not write a DTF record.
void ListGamesTransaction::execute(
    Session& session,
    Console& console,
    DailyTransactionWriter& dtfWriter
) {
    (void)dtfWriter;

    const auto availableGames = session.listings();

    if (availableGames.empty()) {
        console.showMessage("No games are available for purchase.");
        return;
    }

    console.showMessage("Games available for purchase:");

    for (const auto& entry : availableGames) {
        console.showMessage(formatListing(entry.second));
    }
}