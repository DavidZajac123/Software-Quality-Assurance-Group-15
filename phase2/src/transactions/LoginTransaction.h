#pragma once

#include "Transaction.h"

#include <string>

class MasterFileReader;

// Starts a new session for an existing user by loading fresh
// copies of the master files at login.
class LoginTransaction : public Transaction {
public:
    // Keeps a reference to the reader used to load the master files.
    explicit LoginTransaction(MasterFileReader& fileReader);

    // Returns the command used to select this transaction.
    std::string code() const override;

    // Returns false because login is used before a session exists.
    bool requiresLogin() const override;

    // Prompts for a username and starts a fresh session when
    // the account exists in the current user accounts file.
    void execute(
        Session& session,
        Console& console,
        DailyTransactionWriter& dtfWriter
    ) override;

private:
    MasterFileReader& fileReader_;
};