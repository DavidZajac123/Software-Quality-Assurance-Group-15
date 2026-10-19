#pragma once

#include "Transaction.h"

#include <string>

// Purchases an available game for the logged-in user.
// Sell-standard accounts are not permitted to buy games.
class BuyTransaction : public Transaction {
public:
    // Returns the command used to select this transaction.
    std::string code() const override;

    // Returns false for sell-standard accounts and true for all others.
    bool isPermittedFor(UserType type) const override;

    // Prompts for a game and seller, validates the purchase,
    // transfers credit, adds ownership, and records a 04 DTF entry.
    void execute(
        Session& session,
        Console& console,
        DailyTransactionWriter& dtfWriter
    ) override;

private:
    // Validates the purchase and returns the listing price in priceCents.
    // Returns an error message, or an empty string when valid.
    std::string validateInput(
        Session& session,
        const std::string& gameName,
        const std::string& sellerUsername,
        long long& priceCents
    ) const;
};