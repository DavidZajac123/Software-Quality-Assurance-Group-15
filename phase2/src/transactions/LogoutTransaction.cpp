#include "LogoutTransaction.h"

#include "../io/Console.h"
#include "../io/DailyTransactionWriter.h"
#include "../session/Session.h"

// Returns the command word that selects the logout transaction.
std::string LogoutTransaction::code() const {
    return "logout";
}

// Writes the current session's Daily Transaction File,
// then ends the session if the file write succeeds.
void LogoutTransaction::execute(
    Session& session,
    Console& console,
    DailyTransactionWriter& dtfWriter
) {
    if (!dtfWriter.writeSessionFile()) {
        console.showMessage("Error: unable to write daily transaction file.");
        return;
    }

    session.end();
    console.showMessage("Logout successful.");
}