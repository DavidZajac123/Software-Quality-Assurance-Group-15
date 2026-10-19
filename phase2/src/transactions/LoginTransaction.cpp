#include "LoginTransaction.h"

#include "../io/Console.h"
#include "../io/MasterFileReader.h"
#include "../session/Session.h"

// Stores the master-file reader used to load fresh data at login.
LoginTransaction::LoginTransaction(MasterFileReader& fileReader)
    : fileReader_(fileReader) {
}

// Returns the command word that selects the login transaction.
std::string LoginTransaction::code() const {
    return "login";
}

// Returns false because login is the transaction used
// before any session has been established.
bool LoginTransaction::requiresLogin() const {
    return false;
}

// Loads fresh master-file data, prompts for a valid username,
// and starts a new session when the account exists.
void LoginTransaction::execute(
    Session& session,
    Console& console,
    DailyTransactionWriter& dtfWriter
) {
    (void)dtfWriter;

    const auto accounts = fileReader_.readUserAccounts();

    std::string username;

    if (!console.prompt("Enter username:", username)) {
        return;
    }

    if (accounts.find(username) == accounts.end()) {
        console.showMessage("Error: account does not exist.");
        return;
    }

    const auto listings =
        fileReader_.readAvailableGames();

    const auto collection =
        fileReader_.readGameCollection();

    session.begin(
        username,
        accounts,
        listings,
        collection
    );

    console.showMessage("Login successful.");
}