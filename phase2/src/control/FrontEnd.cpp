#include "FrontEnd.h"

#include <utility>

#include "../transactions/LoginTransaction.h"
#include "../transactions/LogoutTransaction.h"
#include "../transactions/CreateTransaction.h"
#include "../transactions/DeleteTransaction.h"
#include "../transactions/SellTransaction.h"
#include "../transactions/BuyTransaction.h"
#include "../transactions/RefundTransaction.h"
#include "../transactions/AddCreditTransaction.h"
#include "../transactions/ListGamesTransaction.h"
#include "../transactions/ListAccountsTransaction.h"

// Connects the Front End to its input/output streams and file handlers,
// then registers all ten supported transaction objects.
FrontEnd::FrontEnd(
    std::istream& input,
    std::ostream& output,
    MasterFileReader fileReader,
    const std::string& dtfFilePrefix
)
    : console_(input, output),
      fileReader_(std::move(fileReader)),
      dtfWriter_(dtfFilePrefix),
      session_() {
    registerTransaction(std::make_unique<LoginTransaction>(fileReader_));
    registerTransaction(std::make_unique<LogoutTransaction>());
    registerTransaction(std::make_unique<CreateTransaction>());
    registerTransaction(std::make_unique<DeleteTransaction>());
    registerTransaction(std::make_unique<SellTransaction>());
    registerTransaction(std::make_unique<BuyTransaction>());
    registerTransaction(std::make_unique<RefundTransaction>());
    registerTransaction(std::make_unique<AddCreditTransaction>());
    registerTransaction(std::make_unique<ListGamesTransaction>());
    registerTransaction(std::make_unique<ListAccountsTransaction>());
}

// Reads transaction codes until input ends and processes each one.
int FrontEnd::run() {
    std::string code;

    while (console_.readLine(code)) {
        processTransactionCode(code);
    }

    return 0;
}

// Finds the requested transaction and either executes it
// or displays the reason it cannot currently run.
void FrontEnd::processTransactionCode(const std::string& code) {
    auto found = transactions_.find(code);

    if (found == transactions_.end()) {
        console_.showMessage(
            "Error: \"" + code + "\" is not a valid transaction code."
        );
        return;
    }

    Transaction& transaction = *found->second;

    const std::string reason = rejectionReason(transaction);

    if (!reason.empty()) {
        console_.showMessage(reason);
        return;
    }

    transaction.execute(
        session_,
        console_,
        dtfWriter_
    );
}

// Returns an error explaining why the transaction cannot run,
// or an empty string when it is allowed.
std::string FrontEnd::rejectionReason(
    const Transaction& transaction
) const {
    if (!session_.isLoggedIn()) {
        if (transaction.requiresLogin()) {
            return "Error: please log in before using \"" +
                transaction.code() + "\".";
        }

        return "";
    }

    if (!transaction.requiresLogin()) {
        return "Error: already logged in. Log out before logging in again.";
    }

    const UserAccount user = session_.currentUser();

    if (!transaction.isPermittedFor(user.type)) {
        return "Error: your account type cannot use \"" +
            transaction.code() + "\".";
    }

    return "";
}

// Stores a transaction in the command lookup table under its command code.
void FrontEnd::registerTransaction(
    std::unique_ptr<Transaction> transaction
) {
    if (!transaction) {
        return;
    }

    const std::string code = transaction->code();
    transactions_[code] = std::move(transaction);
}