#pragma once

#include "Transaction.h"

#include <string>

// Admin-only transaction that creates a new user account with zero credit.
class CreateTransaction : public Transaction {
public:
    // Returns the command used to select this transaction.
    std::string code() const override;

    // Returns true only for administrator accounts.
    bool isPermittedFor(UserType type) const override;

    // Prompts for a username and account type, validates them,
    // creates the account, and records a 01 DTF entry.
    void execute(
        Session& session,
        Console& console,
        DailyTransactionWriter& dtfWriter
    ) override;

private:
    // Validates the username and account-type keyword.
    // Returns an error message, or an empty string when valid.
    std::string validateInput(
        Session& session,
        const std::string& username,
        const std::string& typeKeyword,
        UserType& type
    ) const;
};