#include "RefundTransaction.h"

#include "../io/Console.h"
#include "../io/DailyTransactionWriter.h"
#include "../session/Session.h"
#include "../utilities/Money.h"

std::string RefundTransaction::code() const {
    return "refund";
}

bool RefundTransaction::isPermittedFor(UserType type) const {
    return type == UserType::Admin;
}

std::string RefundTransaction::validateInput(
    Session& session,
    const std::string& buyerUsername,
    const std::string& sellerUsername,
    const std::string& amountText,
    long long& amountCents
) const {
    UserAccount* buyer = session.findAccount(buyerUsername);
    UserAccount* seller = session.findAccount(sellerUsername);

    if (buyer == nullptr) {
        return "Error: buyer account does not exist.";
    }

    if (seller == nullptr) {
        return "Error: seller account does not exist.";
    }

    if (!Money::parse(amountText, amountCents)) {
        return "Error: invalid refund amount.";
    }

    if (amountCents <= 0) {
        return "Error: refund amount must be greater than zero.";
    }

    if (amountCents > seller->creditCents) {
        return "Error: seller has insufficient credit.";
    }

    return "";
}

void RefundTransaction::execute(
    Session& session,
    Console& console,
    DailyTransactionWriter& dtfWriter
) {
    std::string buyerUsername;
    std::string sellerUsername;
    std::string amountText;

    if (!console.prompt("Enter buyer username:", buyerUsername)) {
        return;
    }

    if (!console.prompt("Enter seller username:", sellerUsername)) {
        return;
    }

    if (!console.prompt("Enter refund amount:", amountText)) {
        return;
    }

    long long amountCents = 0;

    const std::string error =
        validateInput(
            session,
            buyerUsername,
            sellerUsername,
            amountText,
            amountCents
        );

    if (!error.empty()) {
        console.showMessage(error);
        return;
    }

    session.transferCredit(
        sellerUsername,
        buyerUsername,
        amountCents
    );

    dtfWriter.recordRefund(
        buyerUsername,
        sellerUsername,
        amountCents
    );

    console.showMessage("Refund completed successfully.");
}