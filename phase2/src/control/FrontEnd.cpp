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

FrontEnd::FrontEnd(std::istream& input, std::ostream& output,
                   const MasterFileReader& fileReader,
                   const std::string& dtfFilePrefix)
    : console_(input, output),
      fileReader_(fileReader),
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
}

int FrontEnd::run() {
    std::string code;
    while (console_.readLine(code)) {
        processTransactionCode(code);
    }
    return 0;
}

void FrontEnd::processTransactionCode(const std::string& code) {
    auto found = transactions_.find(code);
    if (found == transactions_.end()) {
        console_.showMessage("Error: unknown transaction code.");
        return;
    }

    Transaction& transaction = *found->second;
    const std::string reason = rejectionReason(transaction);
    if (!reason.empty()) {
        console_.showMessage(reason);
        return;
    }

    transaction.execute(session_, console_, dtfWriter_);
}

std::string FrontEnd::rejectionReason(const Transaction& transaction) const {
    if (!session_.isLoggedIn()) {
        if (transaction.requiresLogin()) {
            return "Error: no user is logged in.";
        }
        return "";
    }

    if (!transaction.requiresLogin()) {
        return "Error: a user is already logged in.";
    }

    const UserAccount user = session_.currentUser();
    if (!transaction.isPermittedFor(user.type)) {
        return "Error: transaction not permitted for this account type.";
    }
    return "";
}

void FrontEnd::registerTransaction(std::unique_ptr<Transaction> transaction) {
    if (!transaction) {
        return;
    }
    const std::string code = transaction->code();
    transactions_[code] = std::move(transaction);
}
