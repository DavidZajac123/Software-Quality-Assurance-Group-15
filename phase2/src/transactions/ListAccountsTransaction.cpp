#include "ListAccountsTransaction.h"

#include "../io/Console.h"
#include "../session/Session.h"
#include "../utilities/Money.h"
#include "../utilities/UserTypeCodes.h"

// Returns the command word that selects the list_accounts transaction.
std::string ListAccountsTransaction::code() const {
    return "list_accounts";
}

// Returns true only for administrator accounts.
bool ListAccountsTransaction::isPermittedFor(UserType type) const {
    return type == UserType::Admin;
}

// Displays every active account in username order.
// This transaction does not write a DTF record.
void ListAccountsTransaction::execute(
    Session& session,
    Console& console,
    DailyTransactionWriter& dtfWriter
) {
    (void)dtfWriter;

    const auto activeAccounts = session.accounts();

    for (const auto& entry : activeAccounts) {
        const UserAccount& account = entry.second;

        console.showMessage(
            account.username + " | " +
            UserTypeCodes::toFileCode(account.type) + " | $" +
            Money::toDisplay(account.creditCents)
        );
    }
}