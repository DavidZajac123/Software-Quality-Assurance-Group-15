#ifndef DAILY_TRANSACTION_WRITER_H
#define DAILY_TRANSACTION_WRITER_H

#include <string>
#include <vector>

#include "../session/UserType.h"

class DailyTransactionWriter {
public:
    explicit DailyTransactionWriter(const std::string& filePrefix);

    void recordCreate(
        const std::string& username,
        UserType type
    );

    void recordDelete(const std::string& username);

    void recordSell(
        const std::string& gameName,
        const std::string& sellerUsername,
        long long priceCents
    );

    void recordBuy(
        const std::string& gameName,
        const std::string& sellerUsername,
        const std::string& buyerUsername,
        long long priceCents
    );

    void recordRefund(
        const std::string& buyerUsername,
        const std::string& sellerUsername,
        long long amountCents
    );

    void recordAddCredit(
        const std::string& username,
        long long amountCents
    );

    bool writeSessionFile();

private:
    std::string filePrefix_;
    unsigned int nextSessionNumber_;
    std::vector<std::string> records_;

    void addAccountRecord(
        const std::string& transactionCode,
        const std::string& username,
        const std::string& typeCode,
        long long creditCents
    );

    std::string makeEndRecord() const;
};

#endif
