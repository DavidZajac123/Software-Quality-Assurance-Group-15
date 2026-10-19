#include "DeleteTransaction.h"

#include "../io/Console.h"
#include "../io/DailyTransactionWriter.h"
#include "../session/Session.h"

// Returns the command word that selects the delete transaction.
std::string DeleteTransaction::code() const {
    return "delete";
}

// Returns true only for administrator accounts.
bool DeleteTransaction::isPermittedFor(UserType type) const {
    return type == UserType::Admin;
}

// Validates that the target account exists and is not
// the currently logged-in account.
std::string DeleteTransaction::validateInput(
    Session& session,
    const std::string& username
) const {
    if (session.findAccount(username) == nullptr) {
        return "Error: account does not exist.";
    }

    if (session.currentUser().username == username) {
        return "Error: cannot delete the currently logged-in account.";
    }

    return "";
}

// Prompts for the target username, validates the deletion,
// removes the account, and records the 02 DTF entry.
void DeleteTransaction::execute(
    Session& session,
    Console& console,
    DailyTransactionWriter& dtfWriter
) {
    std::string username;

    if (!console.prompt("Enter username:", username)) {
        return;
    }

    const std::string error = validateInput(session, username);

    if (!error.empty()) {
        console.showMessage(error);
        return;
    }

    session.removeAccount(username);
    dtfWriter.recordDelete(username);

    console.showMessage("Account deleted successfully.");
}