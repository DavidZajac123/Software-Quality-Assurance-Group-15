#pragma once

#include "Transaction.h"

#include <string>

// Lists a game for sale by the logged-in user.
// Buy-standard accounts are not permitted to sell games.
class SellTransaction : public Transaction {
public:
    // Returns the command used to select this transaction.
    std::string code() const override;

    // Returns false for buy-standard accounts and true for all others.
    bool isPermittedFor(UserType type) const override;

    // Prompts for a game name and price, validates them,
    // reserves the game name, and records a 03 DTF entry.
    void execute(
        Session& session,
        Console& console,
        DailyTransactionWriter& dtfWriter
    ) override;

private:
    // Validates the game name and price.
    // Returns an error message, or an empty string when valid.
    std::string validateInput(
        Session& session,
        const std::string& gameName,
        const std::string& priceText,
        long long& priceCents
    ) const;
};