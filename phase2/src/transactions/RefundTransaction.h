#pragma once

#include "Transaction.h"

#include <string>

// Admin-only transaction that refunds credit from a seller
// account to a buyer account.
class RefundTransaction : public Transaction {
public:
    // Returns the command used to select this transaction.
    std::string code() const override;

    // Returns true only for administrator accounts.
    bool isPermittedFor(UserType type) const override;

    // Prompts for buyer, seller, and amount, validates the refund,
    // transfers credit, and records a 05 DTF entry.
    void execute(
        Session& session,
        Console& console,
        DailyTransactionWriter& dtfWriter
    ) override;

private:
    // Validates both accounts and the refund amount.
    // Returns an error message, or an empty string when valid.
    std::string validateInput(
        Session& session,
        const std::string& buyerUsername,
        const std::string& sellerUsername,
        const std::string& amountText,
        long long& amountCents
    ) const;
};