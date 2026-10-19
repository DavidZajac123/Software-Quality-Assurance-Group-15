#include "DailyTransactionWriter.h"

#include <fstream>
#include <string>

#include "../utilities/FixedWidthFormat.h"
#include "../utilities/Money.h"
#include "../utilities/UserTypeCodes.h"

DailyTransactionWriter::DailyTransactionWriter(
    const std::string& filePrefix
)
    : filePrefix_(filePrefix),
      nextSessionNumber_(1) {
}

void DailyTransactionWriter::recordCreate(
    const std::string& username,
    UserType type
) {
    addAccountRecord(
        "01",
        username,
        UserTypeCodes::toFileCode(type),
        0
    );
}

void DailyTransactionWriter::recordDelete(
    const std::string& username
) {
    addAccountRecord("02", username, "", 0);
}

void DailyTransactionWriter::recordSell(
    const std::string& gameName,
    const std::string& sellerUsername,
    long long priceCents
) {
    std::string record = "03 ";
    record += FixedWidthFormat::padRight(
        gameName, FixedWidthFormat::GAME_NAME_WIDTH
    );
    record += ' ';
    record += FixedWidthFormat::padRight(
        sellerUsername, FixedWidthFormat::USERNAME_WIDTH
    );
    record += ' ';
    record += Money::toFileField(
        priceCents, FixedWidthFormat::PRICE_WIDTH
    );

    records_.push_back(record);
}

void DailyTransactionWriter::recordBuy(
    const std::string& gameName,
    const std::string& sellerUsername,
    const std::string& buyerUsername,
    long long priceCents
) {
    std::string record = "04 ";
    record += FixedWidthFormat::padRight(
        gameName, FixedWidthFormat::GAME_NAME_WIDTH
    );
    record += ' ';
    record += FixedWidthFormat::padRight(
        sellerUsername, FixedWidthFormat::USERNAME_WIDTH
    );
    record += ' ';
    record += FixedWidthFormat::padRight(
        buyerUsername, FixedWidthFormat::USERNAME_WIDTH
    );
    record += ' ';
    record += Money::toFileField(
        priceCents, FixedWidthFormat::PRICE_WIDTH
    );

    records_.push_back(record);
}

void DailyTransactionWriter::recordRefund(
    const std::string& buyerUsername,
    const std::string& sellerUsername,
    long long amountCents
) {
    std::string record = "05 ";
    record += FixedWidthFormat::padRight(
        buyerUsername, FixedWidthFormat::USERNAME_WIDTH
    );
    record += ' ';
    record += FixedWidthFormat::padRight(
        sellerUsername, FixedWidthFormat::USERNAME_WIDTH
    );
    record += ' ';
    record += Money::toFileField(
        amountCents, FixedWidthFormat::CREDIT_WIDTH
    );

    records_.push_back(record);
}

void DailyTransactionWriter::recordAddCredit(
    const std::string& username,
    long long amountCents
) {
    addAccountRecord("06", username, "", amountCents);
}

void DailyTransactionWriter::addAccountRecord(
    const std::string& transactionCode,
    const std::string& username,
    const std::string& typeCode,
    long long creditCents
) {
    std::string record = transactionCode;
    record += ' ';
    record += FixedWidthFormat::padRight(
        username, FixedWidthFormat::USERNAME_WIDTH
    );
    record += ' ';
    record += FixedWidthFormat::padRight(
        typeCode, FixedWidthFormat::TYPE_WIDTH
    );
    record += ' ';
    record += Money::toFileField(
        creditCents, FixedWidthFormat::CREDIT_WIDTH
    );

    records_.push_back(record);
}

std::string DailyTransactionWriter::makeEndRecord() const {
    std::string record = "00 ";
    record += FixedWidthFormat::padRight(
        "", FixedWidthFormat::USERNAME_WIDTH
    );
    record += ' ';
    record += FixedWidthFormat::padRight(
        "", FixedWidthFormat::TYPE_WIDTH
    );
    record += ' ';
    record += Money::toFileField(0, FixedWidthFormat::CREDIT_WIDTH);

    return record;
}

bool DailyTransactionWriter::writeSessionFile() {
    const std::string filePath =
        filePrefix_ + "_session" +
        std::to_string(nextSessionNumber_) + ".txt";

    std::ofstream file(filePath);
    if (!file.is_open()) {
        return false;
    }

    for (const std::string& record : records_) {
        file << record << '\n';
        if (!file) {
            file.close();
            return false;
        }
    }

    file << makeEndRecord() << '\n';
    if (!file) {
        file.close();
        return false;
    }

    file.close();
    if (!file) {
        return false;
    }

    records_.clear();
    ++nextSessionNumber_;
    return true;
}
