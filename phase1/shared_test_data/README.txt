Shared Test Data

This folder contains common starting-state data used by the Phase 1 test cases.

The files in this folder provide known users, balances, available games, sellers, and game ownership information so that test cases can be executed from a predictable starting state.

Files:

current_users.txt
- Contains user accounts used throughout the Phase 1 tests.
- Includes admin, full-standard, buy-standard, and sell-standard accounts.
- Includes users with specific balances needed for boundary and transaction tests.

available_games.txt
- Contains games currently available for purchase.
- Includes the game name, seller username, and price.
- Provides known games for buy and list_games tests.

game_collection.txt
- Contains existing game ownership information.
- Used for tests such as attempting to purchase a game already owned by a user.

Individual tests may require a modified starting state. Where this occurs, the required starting condition is described in the corresponding expected-output file or test-case documentation.