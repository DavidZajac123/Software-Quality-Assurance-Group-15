Phase 1 Test-Specific Fixtures

The files in shared_test_data/ are the default starting state for a test.
Only the tests listed in this folder override one shared starting-state file.
All non-overridden starting-state files continue to come from shared_test_data/.

Overrides:
- buy_06/current_users.txt: FullUser starts with 20.00 credit for insufficient-credit testing.
- buy_07/current_users.txt: FullUser starts with exactly 50.00 credit.
- buy_08/game_collection.txt: FullUser already owns Minecraft.
- buy_13/current_users.txt: Seller1 is full-standard instead of sell-standard. The original Phase 1 data made Seller1 sell-standard, so the account-type permission check refused "buy" before the own-game rule this test is meant to verify could run.
- refund_10/current_users.txt: Seller1 starts with exactly 20.00 credit.
- refund_11/current_users.txt: Seller1 starts with 10.00 credit.
- refund_15b/game_collection.txt: Buyer1 no longer owns Minecraft, standing in for the Back End applying the earlier refund.
- list_games_02/available_games.txt: exactly one available game.
- list_games_03/available_games.txt: no available games other than END.
- sell_01/available_games.txt: Minecraft is absent so selling Minecraft is a valid unique-name test.
- sell_02/available_games.txt: Terraria is absent so selling Terraria is a valid unique-name test.
- sell_03/available_games.txt: Portal is absent so selling Portal is a valid unique-name test.
- sell_15b/available_games.txt: NextSessionGame is listed, standing in for the Back End applying the earlier sale.
- search_06/current_users.txt: adds AdminSeller, a second admin account.
- search_06/available_games.txt: AdminSeller is selling Zelda, so AdminSeller is an admin who is selling games.

These overrides keep each requirements test independent and reproducible without changing the purpose of the test case.
