#include "LogoutTransaction.h"

#include "../io/Console.h"
#include "../io/DailyTransactionWriter.h"
#include "../session/Session.h"

std::string LogoutTransaction::code() const {
    return "logout";
}

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