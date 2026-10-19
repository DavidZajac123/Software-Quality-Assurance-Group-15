#pragma once

#include "Transaction.h"

// Displays all games currently available for purchase.
// This transaction is available to any logged-in user and does not
// write a record to the Daily Transaction File.
class ListGamesTransaction : public Transaction {
public:
    // Returns the command used to select this transaction.
    std::string code() const override;

    // Displays all currently available games and their relevant information.
    void execute(
        Session& session,
        Console& console,
        DailyTransactionWriter& dtfWriter
    ) override;
};