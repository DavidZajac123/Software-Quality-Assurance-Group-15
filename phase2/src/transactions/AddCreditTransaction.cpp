#include "AddCreditTransaction.h"

#include "../io/Console.h"
#include "../io/DailyTransactionWriter.h"
#include "../session/Session.h"
#include "../utilities/InputRules.h"
#include "../utilities/Money.h"

// Returns the command word that selects the addcredit transaction.
std::string AddCreditTransaction::code() const {
    return "addcredit";
}

// Validates the requested credit amount and target account.
// Returns an error message when invalid, or an empty string when valid.
std::string AddCreditTransaction::validateInput(
    Session& session,
    const std::string& username,
    const std::string& amountText,
    long long& amountCents
) const {
    if (!Money::parse(amountText, amountCents)) {
        return "Error: \"" + amountText + "\" is not a valid amount.";
    }

    if (amountCents <= 0) {
        return "Error: amount must be greater than 0.00.";
    }

    UserAccount* account = session.findAccount(username);

    if (account == nullptr) {
        return "Error: \"" + username + "\" is not a registered user.";
    }

    if (
        session.creditAddedThisSession(username) + amountCents >
        InputRules::MAX_CREDIT_ADDED_PER_SESSION_CENTS
    ) {
        return "Error: at most 1000.00 can be added to an account in one session.";
    }

    if (
        account->creditCents + amountCents >
        InputRules::MAX_BALANCE_CENTS
    ) {
        return "Error: the balance cannot exceed 999999.99.";
    }

    return "";
}

// Prompts for the credit amount and target account when required,
// validates the request, adds credit, and writes the 06 DTF entry.
void AddCreditTransaction::execute(
    Session& session,
    Console& console,
    DailyTransactionWriter& dtfWriter
) {
    std::string amountText;

    if (!console.prompt("Enter amount of credit to add:", amountText)) {
        return;
    }

    std::string username = session.currentUser().username;

    if (session.currentUser().type == UserType::Admin) {
        if (!console.prompt("Enter username to credit:", username)) {
            return;
        }
    }

    long long amountCents = 0;

    const std::string error =
        validateInput(session, username, amountText, amountCents);

    if (!error.empty()) {
        console.showMessage(error);
        return;
    }

    session.addCredit(username, amountCents);
    dtfWriter.recordAddCredit(username, amountCents);

    console.showMessage(
        "Credit added: " + Money::toDisplay(amountCents) +
        " to " + username + "."
    );
}