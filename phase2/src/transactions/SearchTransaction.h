#pragma once

#include "Transaction.h"

#include <string>

// Client change request: lists every game for sale and every user whose
// name contains the search text. A non-admin never sees the name of an
// admin account that has no game for sale. Available to every account
// type; does not write a record to the Daily Transaction File.
class SearchTransaction : public Transaction {
public:
    // Returns the command used to select this transaction.
    std::string code() const override;

    // Prompts for the search text, then displays the matching games
    // and the matching usernames.
    void execute(
        Session& session,
        Console& console,
        DailyTransactionWriter& dtfWriter
    ) override;

private:
    // Returns true when the text is empty or contains only spaces and tabs.
    static bool isBlank(const std::string& text);
};
