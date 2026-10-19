#include "DeleteTransaction.h"

#include "../io/Console.h"
#include "../io/DailyTransactionWriter.h"
#include "../session/Session.h"

std::string DeleteTransaction::code() const {
    return "delete";
}

bool DeleteTransaction::isPermittedFor(UserType type) const {
    return type == UserType::Admin;
}

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