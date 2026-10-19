#pragma once

#include "Transaction.h"

// Ends the current user's session and writes the accumulated
// Daily Transaction File for that session.
class LogoutTransaction : public Transaction {
public:
    // Returns the command used to select this transaction.
    std::string code() const override;

    // Writes the session transaction file and ends the current session.
    void execute(
        Session& session,
        Console& console,
        DailyTransactionWriter& dtfWriter
    ) override;
};