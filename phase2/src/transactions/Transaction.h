#pragma once

#include <string>

#include "../session/UserType.h"

class Session;
class Console;
class DailyTransactionWriter;

// Abstract base class for all Front End transactions.
// It defines the common interface used by FrontEnd to identify,
// authorize, and execute transactions.
class Transaction {
public:
    // Allows transaction subclasses to be deleted safely
    // through a Transaction pointer.
    virtual ~Transaction() = default;

    // Returns the command word used to select this transaction.
    virtual std::string code() const = 0;

    // Returns whether a user must be logged in before this transaction can run.
    virtual bool requiresLogin() const;

    // Returns whether the given account type is allowed to use this transaction.
    virtual bool isPermittedFor(UserType type) const;

    // Performs the transaction using the current session, console,
    // and Daily Transaction File writer.
    virtual void execute(
        Session& session,
        Console& console,
        DailyTransactionWriter& dtfWriter
    ) = 0;
};