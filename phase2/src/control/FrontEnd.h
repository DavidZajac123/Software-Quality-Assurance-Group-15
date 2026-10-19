#ifndef FRONT_END_H
#define FRONT_END_H

#include <iosfwd>
#include <map>
#include <memory>
#include <string>

#include "../io/Console.h"
#include "../io/MasterFileReader.h"
#include "../io/DailyTransactionWriter.h"
#include "../session/Session.h"
#include "../transactions/Transaction.h"

// Controls the entire program with how it works + handles different user transactions.
class FrontEnd {
public:
    // Starts up the front end with input, output, and file handling.
    FrontEnd(std::istream& input, std::ostream& output,
             const MasterFileReader& fileReader,
             const std::string& dtfFilePrefix);

    // Runs the program
    int run();

private:
    // Processes the specific transaction that was requested.
    void processTransactionCode(const std::string& code);

    // Performs a check to see if the transaction is allowed or if it should send an error.
    std::string rejectionReason(const Transaction& transaction) const;

    // Adds specific transaction to list of commands
    void registerTransaction(std::unique_ptr<Transaction> transaction);

    Console console_;
    MasterFileReader fileReader_;
    DailyTransactionWriter dtfWriter_;
    Session session_;
    std::map<std::string, std::unique_ptr<Transaction>> transactions_;
};

#endif