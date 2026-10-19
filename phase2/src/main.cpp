#include "control/FrontEnd.h"
#include "io/MasterFileReader.h"

#include <iostream>

/*
This program is intended to run a front end of a Games Distribution system, similar to a program named "Steam". This program allows the user to login to an account and perform the following transactions: 
- Login (Start Front End session)
- Logout (End Front End session)
- Create (Create new user)
- Delete (Cancel games or remove user account)
- Sell (Put a game up for sale)
- Buy (Purchase a game)
- Refund (Issue credit to buyers account from sellers)
- Add credit (Add credit into system for the purchase of accounts)

The input files are current_users.txt, available_games.txt, and game_collection.txt.

The output file is a Daily Transaction File, storing the successful transaction from that session (daily_session<N>.txt)

To compile the program, run both of these commandlines in the terminal: 
g++ -std=c++17 (Get-ChildItem .\src -Recurse -Filter *.cpp).FullName -o frontend.exe
.\frontend.exe ..\phase1\shared_test_data\current_users.txt ..\phase1\shared_test_data\available_games.txt ..\phase1\shared_test_data\game_collection.txt daily
*/
int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Error: expected four arguments.\n"
                  << "Usage: " << argv[0]
                  << " <users file> <games file> <collection file> <dtf prefix>\n";
        return 1;
    }

    MasterFileReader fileReader(argv[1], argv[2], argv[3]);

    if (!fileReader.canOpenAllFiles()) {
        std::cerr << "Error: cannot open one or more master files.\n";
        return 1;
    }

    FrontEnd frontEnd(std::cin, std::cout, fileReader, argv[4]);
    return frontEnd.run();
}
