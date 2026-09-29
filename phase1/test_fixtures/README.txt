Phase 1 Test-Specific Fixtures

The files in shared_test_data/ are the default starting state for a test.
Only the tests listed in this folder override one shared starting-state file.
All non-overridden starting-state files continue to come from shared_test_data/.

Overrides:
- buy_06/current_users.txt: FullUser starts with 20.00 credit for insufficient-credit testing.
- buy_07/current_users.txt: FullUser starts with exactly 50.00 credit.
- buy_08/game_collection.txt: FullUser already owns Minecraft.
- refund_10/current_users.txt: Seller1 starts with exactly 20.00 credit.
- refund_11/current_users.txt: Seller1 starts with 10.00 credit.
- list_games_02/available_games.txt: exactly one available game.
- list_games_03/available_games.txt: no available games other than END.
- sell_01/available_games.txt: Minecraft is absent so selling Minecraft is a valid unique-name test.
- sell_02/available_games.txt: Terraria is absent so selling Terraria is a valid unique-name test.
- sell_03/available_games.txt: Portal is absent so selling Portal is a valid unique-name test.

These overrides keep each requirements test independent and reproducible without changing the purpose of the test case.
