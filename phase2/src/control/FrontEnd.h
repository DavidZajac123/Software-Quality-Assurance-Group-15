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

// Runs the Front End transaction loop, determines whether transactions
// may run, and passes accepted transaction codes to the matching transaction.
class FrontEnd {
public:
    // Connects the Front End to the given input/output streams, copies the
    // master-file reader, initializes the DTF writer, and registers all
    // supported transactions.
    FrontEnd(
        std::istream& input,
        std::ostream& output,
        MasterFileReader fileReader,
        const std::string& dtfFilePrefix
    );

    // Reads and processes transaction codes until the input ends.
    // Returns 0 when the transaction loop finishes normally.
    int run();

private:
    // Finds the transaction for the given code and either executes it
    // or displays the reason it cannot currently run.
    void processTransactionCode(const std::string& code);

    // Returns an error message if the transaction cannot run in the
    // current session state, or an empty string if it is permitted.
    std::string rejectionReason(const Transaction& transaction) const;

    // Adds a transaction to the lookup table using its command code.
    void registerTransaction(std::unique_ptr<Transaction> transaction);

    Console console_;
    MasterFileReader fileReader_;
    DailyTransactionWriter dtfWriter_;
    Session session_;

    std::map<std::string, std::unique_ptr<Transaction>> transactions_;
};

#endif