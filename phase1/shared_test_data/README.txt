Shared Test Data

This folder contains the default starting-state data for Phase 1 requirements tests.

Files use the fixed-width formats defined by the project requirements and client clarifications:
- current_users.txt: 15-character username + space + 2-character user type + space + 9-character credit field (28 characters per line, plus newline).
- available_games.txt: 26-character game name + space + 15-character seller username + space + 6-character price field (49 characters per line, plus newline). The 26-character game-name width follows the client instruction to use the example when the written length conflicts with the example.
- game_collection.txt: 26-character game name + space + 15-character owner username (42 characters per line, plus newline). The irrelevant statement about unused numeric fields is ignored because this file has no numeric field.

Default collection state gives Buyer1 ownership of Minecraft so refund/delete collection tests have a defined starting relationship while FullUser remains able to buy Minecraft in ordinary buy tests.

Tests needing a different starting state use files from ../test_fixtures/.
