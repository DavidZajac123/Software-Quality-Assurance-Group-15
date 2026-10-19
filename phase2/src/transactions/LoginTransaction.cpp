#include "LoginTransaction.h"

#include "../io/Console.h"
#include "../io/MasterFileReader.h"
#include "../session/Session.h"

LoginTransaction::LoginTransaction(MasterFileReader& fileReader)
    : fileReader_(fileReader) {
}

std::string LoginTransaction::code() const {
    return "login";
}

bool LoginTransaction::requiresLogin() const {
    return false;
}

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