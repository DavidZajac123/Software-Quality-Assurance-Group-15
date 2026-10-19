#include "CreateTransaction.h"

#include "../io/Console.h"
#include "../io/DailyTransactionWriter.h"
#include "../session/Session.h"
#include "../session/UserAccount.h"
#include "../utilities/InputRules.h"
#include "../utilities/UserTypeCodes.h"

// Returns the command word that selects the create transaction.
std::string CreateTransaction::code() const {
    return "create";
}

// Returns true only for administrator accounts.
bool CreateTransaction::isPermittedFor(UserType type) const {
    return type == UserType::Admin;
}

// Validates the requested username and account-type keyword.
// Returns an error message when invalid, or an empty string when valid.
std::string CreateTransaction::validateInput(
    Session& session,
    const std::string& username,
    const std::string& typeKeyword,
    UserType& type
) const {
    if (!InputRules::isValidUsername(username)) {
        return "Error: invalid username.";
    }

    if (session.findAccount(username) != nullptr) {
        return "Error: username already exists.";
    }

    if (!UserTypeCodes::fromKeyword(typeKeyword, type)) {
        return "Error: invalid account type.";
    }

    return "";
}

// Prompts for new-account information, validates it,
// creates the account, and records the 01 DTF entry.
void CreateTransaction::execute(
    Session& session,
    Console& console,
    DailyTransactionWriter& dtfWriter
) {
    std::string username;
    std::string typeKeyword;

    if (!console.prompt("Enter new username:", username)) {
        return;
    }

    if (!console.prompt("Enter account type:", typeKeyword)) {
        return;
    }

    UserType type = UserType::FullStandard;

    const std::string error =
        validateInput(session, username, typeKeyword, type);

    if (!error.empty()) {
        console.showMessage(error);
        return;
    }

    UserAccount account;
    account.username = username;
    account.type = type;
    account.creditCents = 0;

    session.addAccount(account);
    dtfWriter.recordCreate(username, type);

    console.showMessage("Account created successfully.");
}