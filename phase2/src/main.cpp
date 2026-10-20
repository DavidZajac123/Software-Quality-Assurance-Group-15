#include "control/FrontEnd.h"
#include "io/MasterFileReader.h"

#include <iostream>

/*
This program runs the Front End of a digital game distribution system.
It allows users to log in and perform the following transactions:

- Login (start a Front End session)
- Logout (end the current session and write its Daily Transaction File)
- Create (create a new user account)
- Delete (delete an existing user account)
- Sell (list a game for sale)
- Buy (purchase an available game)
- Refund (transfer credit from a seller back to a buyer)
- Add Credit (add credit to an account)
- List Games (display games currently available for purchase)
- List Accounts (admin-only display of all active accounts)

Input files:
- Current User Accounts File
- Available Games File
- Game Collection File

Output:
- One Daily Transaction File per successfully logged-out session,
  named <dtf prefix>_session<N>.txt.

The program expects four command-line arguments:
frontend <users file> <games file> <collection file> <dtf prefix>

Example compilation from the phase2 directory in PowerShell:
g++ -std=c++17 (Get-ChildItem .\src -Recurse -Filter *.cpp).FullName -o frontend.exe

Example run:
.\frontend.exe ..\phase1\shared_test_data\current_users.txt ..\phase1\shared_test_data\available_games.txt ..\phase1\shared_test_data\game_collection.txt daily
*/

// Checks the command-line arguments and master files,
// creates the Front End, runs it, and returns its exit status.
int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr
            << "Error: expected four arguments.\n"
            << "Usage: " << argv[0]
            << " <users file> <games file> <collection file> <dtf prefix>\n";

        return 1;
    }

    MasterFileReader fileReader(
        argv[1],
        argv[2],
        argv[3]
    );

    if (!fileReader.canOpenAllFiles()) {
        std::cerr
            << "Error: cannot open one or more master files.\n";

        return 1;
    }

    FrontEnd frontEnd(
        std::cin,
        std::cout,
        fileReader,
        argv[4]
    );

    return frontEnd.run();
}