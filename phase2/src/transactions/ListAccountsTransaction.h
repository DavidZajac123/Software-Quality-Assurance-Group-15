#pragma once

#include "Transaction.h"

#include <string>

// Admin-only transaction that displays every active user account
// with its account type and current credit balance.
class ListAccountsTransaction : public Transaction {
public:
    // Returns the command used to select this transaction.
    std::string code() const override;

    // Returns true only for administrator accounts.
    bool isPermittedFor(UserType type) const override;

    // Displays every active account in username order.
    // This transaction does not write a DTF record.
    void execute(
        Session& session,
        Console& console,
        DailyTransactionWriter& dtfWriter
    ) override;
};