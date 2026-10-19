#pragma once

#include "Transaction.h"

#include <string>

// Adds credit to a user account while enforcing the per-session
// credit limit and maximum account balance.
class AddCreditTransaction : public Transaction {
public:
    // Returns the command used to select this transaction.
    std::string code() const override;

    // Prompts for the amount and, for an administrator, the target
    // username, then adds credit and records a 06 DTF entry.
    void execute(
        Session& session,
        Console& console,
        DailyTransactionWriter& dtfWriter
    ) override;

private:
    // Validates the target account and amount.
    // Returns an error message, or an empty string when valid.
    std::string validateInput(
        Session& session,
        const std::string& username,
        const std::string& amountText,
        long long& amountCents
    ) const;
};