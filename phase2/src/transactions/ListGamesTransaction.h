#pragma once

#include "Transaction.h"

#include <string>

#include "../session/GameListing.h"

// Displays all games currently available for purchase.
// This transaction is available to any logged-in user and does not
// write a record to the Daily Transaction File.
class ListGamesTransaction : public Transaction {
public:
    // Returns the command used to select this transaction.
    std::string code() const override;

    // Formats one game for sale as a fixed-width line. Also used by search.
    static std::string formatListing(const GameListing& listing);

    // Displays all currently available games and their relevant information.
    void execute(
        Session& session,
        Console& console,
        DailyTransactionWriter& dtfWriter
    ) override;
};