#include "ListAccountsTransaction.h"

#include "../io/Console.h"
#include "../session/Session.h"
#include "../utilities/FixedWidthFormat.h"
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

// Displays a header, then every active account in username order:
// the username padded to 15 characters, the type code and the credit.
// This transaction does not write a DTF record.
void ListAccountsTransaction::execute(
    Session& session,
    Console& console,
    DailyTransactionWriter& dtfWriter
) {
    (void)dtfWriter;

    const auto activeAccounts = session.accounts();

    console.showMessage("Active accounts:");

    for (const auto& entry : activeAccounts) {
        const UserAccount& account = entry.second;

        console.showMessage(
            FixedWidthFormat::padRight(
                account.username, FixedWidthFormat::USERNAME_WIDTH
            ) + " " +
            UserTypeCodes::toFileCode(account.type) + " " +
            Money::toDisplay(account.creditCents)
        );
    }
}