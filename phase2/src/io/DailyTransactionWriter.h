#ifndef DAILY_TRANSACTION_WRITER_H
#define DAILY_TRANSACTION_WRITER_H

#include <string>
#include <vector>

#include "../session/UserType.h"

// Stores successful transaction records for the current session
// and writes them to a Daily Transaction File at logout.
class DailyTransactionWriter {
public:
    // Creates a writer using the provided DTF file-name prefix.
    explicit DailyTransactionWriter(const std::string& filePrefix);

    // Records a successful account creation transaction.
    void recordCreate(
        const std::string& username,
        UserType type
    );

    // Records a successful account deletion transaction.
    void recordDelete(const std::string& username);

    // Records a successful sell transaction.
    void recordSell(
        const std::string& gameName,
        const std::string& sellerUsername,
        long long priceCents
    );

    // Records a successful buy transaction.
    void recordBuy(
        const std::string& gameName,
        const std::string& sellerUsername,
        const std::string& buyerUsername,
        long long priceCents
    );

    // Records a successful refund transaction.
    void recordRefund(
        const std::string& buyerUsername,
        const std::string& sellerUsername,
        long long amountCents
    );

    // Records a successful add-credit transaction.
    void recordAddCredit(
        const std::string& username,
        long long amountCents
    );

    // Writes all pending session records and the final 00 record
    // to the next Daily Transaction File.
    bool writeSessionFile();

private:
    std::string filePrefix_;
    unsigned int nextSessionNumber_;
    std::vector<std::string> records_;

    // Adds a fixed-width account transaction record to the pending records.
    void addAccountRecord(
        const std::string& transactionCode,
        const std::string& username,
        const std::string& typeCode,
        long long creditCents
    );

    // Creates the final 00 END record for a session DTF.
    std::string makeEndRecord() const;
};

#endif