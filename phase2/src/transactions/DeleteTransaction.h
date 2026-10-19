#pragma once

#include "Transaction.h"

#include <string>

// Admin-only transaction that deletes an existing user account,
// except for the currently logged-in administrator account.
class DeleteTransaction : public Transaction {
public:
    // Returns the command used to select this transaction.
    std::string code() const override;

    // Returns true only for administrator accounts.
    bool isPermittedFor(UserType type) const override;

    // Prompts for a username, validates the deletion,
    // removes the account, and records a 02 DTF entry.
    void execute(
        Session& session,
        Console& console,
        DailyTransactionWriter& dtfWriter
    ) override;

private:
    // Checks that the username exists and is not the currently logged-in user.
    // Returns an error message, or an empty string when valid.
    std::string validateInput(
        Session& session,
        const std::string& username
    ) const;
};