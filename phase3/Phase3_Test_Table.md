# Phase 3 Test Table

Every Front End requirements test, with the name given to it (its folder name, as the Phase 1 feedback asked). The test ID is the file prefix: `phase1/tests/<category>/<folder>/<test id>_input.txt`. Each test has an input file, a one-line expected result (shown below), a terminal expected file and one DTF expected file per session.

Data: "Shared" means the test starts from `phase1/shared_test_data/`; a fixture replaces only the named file, from `phase1/test_fixtures/<test id>/`.

Total: 152 tests. Final run (run 6 in the failure log, on the committed code): 152 passed, 0 failed.

| Category | Tests |
|---|---|
| `addcredit` | 13 |
| `buy` | 13 |
| `create` | 11 |
| `delete` | 7 |
| `invalid_input` | 10 |
| `list_accounts` | 8 |
| `list_games` | 12 |
| `login` | 9 |
| `logout` | 10 |
| `refund` | 16 |
| `search` | 9 |
| `sell` | 16 |
| `transaction_output` | 18 |

## addcredit (13)

| Test ID | Test name | Expected result | Data | Origin |
|---|---|---|---|---|
| `addcredit_01` | 01_standard_user_add_valid_amount_toself | Login accepted; 100.00 added to FullUser; logout accepted. | Shared | Phase 1 |
| `addcredit_02` | 02_admin_addcredit_to_existing_user | Admin addcredit to existing User1 accepted. | Shared | Phase 1 |
| `addcredit_03` | 03_admin_addcredit_to_nonexistent_user | Denied because user does not exist. | Shared | Phase 1 |
| `addcredit_04` | 04_user_add_exactly_100credit_in_session | Exactly $1000 accepted. | Shared | Phase 1 |
| `addcredit_05` | 05_user_add_over_1000credit_in_one_session | Denied because per-session maximum exceeded. | Shared | Phase 1 |
| `addcredit_06` | 06_user_has_multiple_additions_totaling_1000 | Both accepted; total added = 1000.00. | Shared | Phase 1 |
| `addcredit_07` | 07_user_has_multiple_additions_over_1000_credit | First accepted; second denied because total would exceed 1000.00. | Shared | Phase 1 |
| `addcredit_08` | 08_user_enters_nonnumeric_amount | Invalid amount rejected gracefully. | Shared | Phase 1 |
| `addcredit_09` | 09_user_leaves_amount_blank | Blank amount rejected gracefully. | Shared | Phase 1 |
| `addcredit_10` | 10_successful_add_updates_balance | With User1 starting at 100.00, addcredit is accepted and the resulting balance is 150.00. | Shared | Phase 1 |
| `addcredit_11` | 11_addcredit_exceeds_max_account_balance | Login accepted. Addcredit denied because adding 600.00 to the existing balance of 999500.00 would exceed the maximum account balance of 999999.99. Logout accepted. | Shared | Phase 1 |
| `addcredit_12` | 12_amount_too_large_to_store | Denied: over the 1000.00 per-session limit. The amount is too large to store, so it must be rejected by the limit check, not misread. | Shared | Phase 3 (amount parsing) |
| `addcredit_13` | 13_amount_without_leading_digit | Denied: ".5" is not a valid amount, because an amount must start with a digit. No credit is added. | Shared | Phase 3 (amount parsing) |

## buy (13)

| Test ID | Test name | Expected result | Data | Origin |
|---|---|---|---|---|
| `buy_01` | 01_fullstandard_purchase_existing_game | Purchase accepted. | Shared | Phase 1 |
| `buy_02` | 02_buystandard_purchase_game | Purchase accepted. | Shared | Phase 1 |
| `buy_03` | 03_admin_purchase_game | Purchase accepted. | Shared | Phase 1 |
| `buy_04` | 04_sellstandard_tries_to_buy | buy denied because sell-standard users cannot buy. | Shared | Phase 1 |
| `buy_05` | 05_attempt_to_buy_nonexistent_game | Denied: game does not exist. | Shared | Phase 1 |
| `buy_06` | 06_buyer_has_insufficent_credit | With buyer credit 20.00 and price 50.00: denied for insufficient credit. | Fixture: `current_users.txt` | Phase 1 |
| `buy_07` | 07_buyer_has_exact_enough_credit | With buyer credit exactly 50.00: accepted; balance becomes 0.00. | Fixture: `current_users.txt` | Phase 1 |
| `buy_08` | 08_buyer_already_owns_game | With Minecraft already in FullUser's collection: denied. | Fixture: `game_collection.txt` | Phase 1 |
| `buy_09` | 09_user_leaves_game_name_blank | Blank game name rejected gracefully. | Shared | Phase 1 |
| `buy_10` | 10_enter_wrong_seller_for_existing_game | Denied because seller does not match Minecraft's seller. | Shared | Phase 1 |
| `buy_11` | 11_update_buyer | Accepted; buyer decreases and seller increases by 50.00. | Shared | Phase 1 |
| `buy_12` | 12_success_purchase_add_game_to_buyer_collection | Accepted; purchased game added to buyer collection. | Shared | Phase 1 |
| `buy_13` | 13_seller_tries_to_buy_own_game | Denied: seller cannot buy own listed game. | Fixture: `current_users.txt` | Phase 1 |

## create (11)

| Test ID | Test name | Expected result | Data | Origin |
|---|---|---|---|---|
| `create_01` | 01_admin_create_adminaccount | Accepted; NewAdmin created at 0.00. | Shared | Phase 1 |
| `create_02` | 02_admin_create_fullstandard | Accepted. | Shared | Phase 1 |
| `create_03` | 03_admin_create_buystandard | Accepted. | Shared | Phase 1 |
| `create_04` | 04_admin_create_sellstandard | Accepted. | Shared | Phase 1 |
| `create_05` | 05_non-admin_user_create_user | Denied because create is admin-only. | Shared | Phase 1 |
| `create_06` | 06_admin_create_duplicate_username | Denied: duplicate username. | Shared | Phase 1 |
| `create_07` | 07_admin_create_15char_username | Accepted; exactly 15 chars. | Shared | Phase 1 |
| `create_08` | 08_admin_create_username_greater_15char | Denied; 16 chars. | Shared | Phase 1 |
| `create_09` | 09_admin_create_invalid_user_type | Denied: invalid type. | Shared | Phase 1 |
| `create_10` | 10_admin_leave_username_blank | Blank username rejected gracefully. | Shared | Phase 1 |
| `create_11` | 11_new_account_has_0_credit | Accepted; starting balance = 0.00. | Shared | Phase 1 |

## delete (7)

| Test ID | Test name | Expected result | Data | Origin |
|---|---|---|---|---|
| `delete_01` | 01_admin_delete_existing_user | David deleted. | Shared | Phase 1 |
| `delete_02` | 02_non-admin_delete_user | Denied: admin-only. | Shared | Phase 1 |
| `delete_03` | 03_admin_delete_nonexist_user | Denied: user does not exist. | Shared | Phase 1 |
| `delete_04` | 04_admin_delete_own__loggedin_account | Denied: cannot delete current user. | Shared | Phase 1 |
| `delete_05` | 05_use_deleted_user_game_inventory | Delete accepted; later attempt involving Seller1's cancelled inventory denied. | Shared | Phase 1 |
| `delete_06` | 06_admin_enter_blank_username | Blank username rejected. | Shared | Phase 1 |
| `delete_07` | 07_remove_deleted_user_game_entries | Login accepted. Delete transaction accepted. Under the documented group assumption, Game Collection entries owned by Buyer1 are removed when the account is deleted. Logout accepted. | Shared | Phase 1 |

## invalid_input (10)

| Test ID | Test name | Expected result | Data | Origin |
|---|---|---|---|---|
| `invalid_input_01` | 01_user_enters_invalid_transaction_name | banana rejected; program continues; login/logout work. | Shared | Phase 1 |
| `invalid_input_02` | 02_user_enters_blank_transaction | Blank transaction rejected; program continues. | Shared | Phase 1 |
| `invalid_input_03` | 03_user_enters_letters_for_price | Nonnumeric price rejected gracefully. | Shared | Phase 1 |
| `invalid_input_04` | 04_user_enters_letters_for_credit | Nonnumeric credit rejected. | Shared | Phase 1 |
| `invalid_input_05` | 05_user_enters_letters_for_refund | Nonnumeric refund amount rejected. | Shared | Phase 1 |
| `invalid_input_06` | 06_user_enters_excessive_text | Excessive field rejected; no crash. | Shared | Phase 1 |
| `invalid_input_07` | 07_user_enters_valid_transaction_after_invalid | Invalid input rejected; later valid login succeeds. | Shared | Phase 1 |
| `invalid_input_08` | 08_invalid_input_followed_by_valid_transaction_in_same_session | Invalid transaction rejected; valid following transaction succeeds. | Shared | Phase 1 |
| `invalid_input_09` | 09_long_transaction_command | Long command rejected gracefully; program continues. | Shared | Phase 1 |
| `invalid_input_10` | 10_special_characters_in_transaction_input | Special-character command rejected; program continues. | Shared | Phase 1 |

## list_accounts (8)

| Test ID | Test name | Expected result | Data | Origin |
|---|---|---|---|---|
| `list_accounts_01` | 01_admin_lists_all_active_accounts | Admin sees every active account with type and credit, in username order. | Shared | Phase 3 (list_accounts, Week 4 change) |
| `list_accounts_02` | 02_full_standard_user_denied | Denied for full-standard. | Shared | Phase 3 (list_accounts, Week 4 change) |
| `list_accounts_03` | 03_buy_standard_user_denied | Denied for buy-standard. | Shared | Phase 3 (list_accounts, Week 4 change) |
| `list_accounts_04` | 04_sell_standard_user_denied | Denied for sell-standard. | Shared | Phase 3 (list_accounts, Week 4 change) |
| `list_accounts_05` | 05_denied_before_login | Denied before login; later login and logout work. | Shared | Phase 3 (list_accounts, Week 4 change) |
| `list_accounts_06` | 06_includes_account_created_this_session | An account created earlier in the session is listed with 0.00 credit. | Shared | Phase 3 (list_accounts, Week 4 change) |
| `list_accounts_07` | 07_excludes_account_deleted_this_session | An account deleted earlier in the session is not listed. | Shared | Phase 3 (list_accounts, Week 4 change) |
| `list_accounts_08` | 08_shows_credit_added_this_session | Credit added earlier in the session shows in the listed balance. | Shared | Phase 3 (list_accounts, Week 4 change) |

## list_games (12)

| Test ID | Test name | Expected result | Data | Origin |
|---|---|---|---|---|
| `list_games_01` | 01_user_requsets_list_when_games_are_available | All available games/relevant information displayed. | Shared | Phase 1 |
| `list_games_02` | 02_only_one_game_available | With one-game fixture, exactly one game displayed. | Fixture: `available_games.txt` | Phase 1 |
| `list_games_03` | 03_no_games_available | With empty fixture, reports no games available. | Fixture: `available_games.txt` | Phase 1 |
| `list_games_04` | 04_verify_game_names | Displayed game names match Available Games File. | Shared | Phase 1 |
| `list_games_05` | 05_verify_seller_names | Seller usernames match. | Shared | Phase 1 |
| `list_games_06` | 06_verify_prices | Prices match. | Shared | Phase 1 |
| `list_games_07` | 07_user_tries_list_before_login | Denied before login; later login/logout work. | Shared | Phase 1 |
| `list_games_08` | 08_user_tries_list_after_logout | list_games after logout denied. | Shared | Phase 1 |
| `list_games_09` | 09_admin_user_uses_listgames | Accepted for admin. | Shared | Phase 1 |
| `list_games_10` | 10_full_standard_user_uses_listgames | Accepted for full-standard. | Shared | Phase 1 |
| `list_games_11` | 11_buy_standard_user_uses_listgames | Accepted for buy-standard. | Shared | Phase 1 |
| `list_games_12` | 12_sell_standard_user_uses_listgames | Accepted for sell-standard. | Shared | Phase 1 |

## login (9)

| Test ID | Test name | Expected result | Data | Origin |
|---|---|---|---|---|
| `login_01` | 01_existing_admin_username | Admin login accepted. | Shared | Phase 1 |
| `login_02` | 02_existing_fullstandard_username | Full-standard login accepted. | Shared | Phase 1 |
| `login_03` | 03_existing_buystandard_username | Buy-standard login accepted. | Shared | Phase 1 |
| `login_04` | 04_existing_sellstandard_username | Sell-standard login accepted. | Shared | Phase 1 |
| `login_05` | 05_nonexisting_username | First login denied; later valid login succeeds. | Shared | Phase 1 |
| `login_06` | 06_transaction_before_login | buy before login denied; later login works. | Shared | Phase 1 |
| `login_07` | 07_login_while_logged_in | First login accepted; second login denied; logout works. | Shared | Phase 1 |
| `login_08` | 08_login_after_logout | Second session login accepted after first logout. | Shared | Phase 1 |
| `login_09` | 09_blank_username | Blank username rejected; later valid login succeeds. | Shared | Phase 1 |

## logout (10)

| Test ID | Test name | Expected result | Data | Origin |
|---|---|---|---|---|
| `logout_01` | 01_logout_while_logged_in | Logout accepted; DTF written. | Shared | Phase 1 |
| `logout_02` | 02_logout_while_not_logged_in | First logout denied; later valid session/logout succeeds. | Shared | Phase 1 |
| `logout_03` | 03_buy_after_logout | buy after logout denied. | Shared | Phase 1 |
| `logout_04` | 04_sell_after_logout | sell after logout denied. | Shared | Phase 1 |
| `logout_05` | 05_create_after_logout | create after logout denied. | Shared | Phase 1 |
| `logout_06` | 06_delete_after_logout | delete after logout denied. | Shared | Phase 1 |
| `logout_07` | 07_addcredit_after_logout | addcredit after logout denied. | Shared | Phase 1 |
| `logout_08` | 08_refund_after_logout | refund after logout denied. | Shared | Phase 1 |
| `logout_09` | 09_login_after_logout | New session accepted. | Shared | Phase 1 |
| `logout_10` | 10_list_games_after_logout | list_games after logout denied. | Shared | Phase 1 |

## refund (16)

| Test ID | Test name | Expected result | Data | Origin |
|---|---|---|---|---|
| `refund_01` | 01_admin_performs_valid_refund | Accepted; 20.00 transferred seller→buyer. | Shared | Phase 1 |
| `refund_02` | 02_non_admin_attempts_refund | Denied: refund is privileged. | Shared | Phase 1 |
| `refund_03` | 03_buyer_username_doesnt_exist | Denied: buyer doesn't exist. | Shared | Phase 1 |
| `refund_04` | 04_seller_username_doesnt_exist | Denied: seller doesn't exist. | Shared | Phase 1 |
| `refund_05` | 05_neither_buyer_nor_seller_exists | Denied. | Shared | Phase 1 |
| `refund_06` | 06_buyer_field_blank | Blank buyer rejected. | Shared | Phase 1 |
| `refund_07` | 07_seller_field_blank | Blank seller rejected. | Shared | Phase 1 |
| `refund_08` | 08_refund_amount_not_numeric | Invalid amount rejected. | Shared | Phase 1 |
| `refund_09` | 09_valid_refund_updates_both_account_balances | Accepted; both balances updated correctly. | Shared | Phase 1 |
| `refund_10` | 10_seller_has_exactly_enough_credit_for_refund | Accepted; seller becomes 0.00. | Fixture: `current_users.txt` | Phase 1 |
| `refund_11` | 11_seller_doesnt_have_enough_credit | Denied: seller insufficient credit. | Fixture: `current_users.txt` | Phase 1 |
| `refund_12` | 12_refund_amount_is_0 | Denied. | Shared | Phase 1 |
| `refund_13` | 13_refund_amount_is_negative | Denied. | Shared | Phase 1 |
| `refund_14` | 14_successful_refund_remove_game_from_buyer | Login accepted. Refund transaction accepted. 20.00 is transferred from Seller1 to Buyer1. Under the client clarification, the refunded game leaves Buyer1's Game Collection when the Back End applies the refund (open question R4). This Front End test checks only the credit transfer and the 05 record. Logout accepted. | Shared | Phase 1 |
| `refund_15a` | 15a_refund_session1 | Session 1 of the original refund_15: AdminUser refunds 20.00 from Seller1 to Buyer1. Refund accepted and recorded (05); under the client clarification the refunded game leaves Buyer1's collection when the Back End applies the refund (open question R4); logout accepted. The repurchase in a later session is tested by refund_15b. | Shared | Phase 3 (split from refund_15) |
| `refund_15b` | 15b_repurchase_session2 | Session 2 of the original refund_15: Buyer1 buys Minecraft from Seller1 again for 50.00. Purchase accepted and recorded (04); logout accepted. The fixture removes Minecraft from Buyer1's collection, standing in for the Back End after refund_15a (open question R4). | Fixture: `game_collection.txt` | Phase 3 (split from refund_15) |

## search (9)

| Test ID | Test name | Expected result | Data | Origin |
|---|---|---|---|---|
| `search_01` | 01_full_standard_finds_game_by_partial_name | Shows Minecraft; no user name contains the text. | Shared | Phase 3 (SEARCH, client change) |
| `search_02` | 02_buy_standard_finds_users_by_partial_name | Shows Seller1, Seller2 and Seller3; no game name contains the text. | Shared | Phase 3 (SEARCH, client change) |
| `search_03` | 03_sell_standard_finds_game_and_user | Shows ExistingGame and ExistingUser. | Shared | Phase 3 (SEARCH, client change) |
| `search_04` | 04_non_admin_cannot_see_admin_not_selling | AdminUser sells nothing, so a non-admin search does not show it. | Shared | Phase 3 (SEARCH, client change) |
| `search_05` | 05_admin_sees_admin_account | An admin search shows AdminUser. | Shared | Phase 3 (SEARCH, client change) |
| `search_06` | 06_non_admin_sees_admin_who_is_selling | With the fixture, AdminSeller is selling Zelda, so it is shown; AdminUser is not. | Fixture: `available_games.txt`, `current_users.txt` | Phase 3 (SEARCH, client change) |
| `search_07` | 07_blank_search_text_rejected | Blank search text is rejected. | Shared | Phase 3 (SEARCH, client change) |
| `search_08` | 08_denied_before_login | Denied before login; later login and logout work. | Shared | Phase 3 (SEARCH, client change) |
| `search_09` | 09_matching_is_case_sensitive | Lowercase text does not match Minecraft. | Shared | Phase 3 (SEARCH, client change) |

## sell (16)

| Test ID | Test name | Expected result | Data | Origin |
|---|---|---|---|---|
| `sell_01` | 01_full_standadrd_user_sells_valid_game | Accepted. | Fixture: `available_games.txt` | Phase 1 |
| `sell_02` | 02_sell_stanard_user_sells_valid_game | Accepted | Fixture: `available_games.txt` | Phase 1 |
| `sell_03` | 03_admin_sells_valid_game | Accepted. | Fixture: `available_games.txt` | Phase 1 |
| `sell_04` | 04_buy_stanadrd_user_attempts_sell | Denied because buy-standard cannot sell. | Shared | Phase 1 |
| `sell_05` | 05_user_lists_game_for_999.99 | Accepted. | Shared | Phase 1 |
| `sell_06` | 06_user_lists_game_more_than_999.99 | Denied. | Shared | Phase 1 |
| `sell_07` | 07_user_enters_game_name_exactly_26_characters | Login accepted. Sell transaction accepted. The 26-character game name is accepted because it matches the example-defined maximum field length. Logout accepted. | Shared | Phase 1 |
| `sell_08` | 08_user_enters_game_longer_than_26_characters | Login accepted. Sell transaction denied because the game name exceeds the example-defined maximum field length. Logout accepted. | Shared | Phase 1 |
| `sell_09` | 09_user_sells_game_whose_name_already_exists | With ExistingGame already listed: denied. | Shared | Phase 1 |
| `sell_10` | 10_user_use_new_game_in_same_session | Sale accepted; same-session attempted use denied. | Shared | Phase 1 |
| `sell_11` | 11_user_enters_letters_instead_of_price | Invalid price rejected. | Shared | Phase 1 |
| `sell_12` | 12_user_leaves_game_name_blank | Blank game name rejected. | Shared | Phase 1 |
| `sell_13` | 13_user_enters_price_of_0 | Accepted at 0.00. | Shared | Phase 1 |
| `sell_14` | 14_user_enters_negative_price | Denied. | Shared | Phase 1 |
| `sell_15a` | 15a_newly_listed_game_session1 | Session 1 of the original sell_15: FullUser lists NextSessionGame for 25.00. Sale accepted and recorded (03); logout accepted. The purchase in a later session is tested by sell_15b. | Shared | Phase 3 (split from sell_15) |
| `sell_15b` | 15b_newly_listed_game_session2 | Session 2 of the original sell_15: BuyUser buys NextSessionGame from FullUser for 25.00. Purchase accepted and recorded (04); logout accepted. The fixture lists the game, standing in for the Back End after sell_15a. | Fixture: `available_games.txt` | Phase 3 (split from sell_15) |

## transaction_output (18)

| Test ID | Test name | Expected result | Data | Origin |
|---|---|---|---|---|
| `transaction_output_01` | 01_valid_create_transaction | Create/logout succeed. | Shared | Phase 1 |
| `transaction_output_02` | 02_valid_delete_transaction | Delete/logout succeed. | Shared | Phase 1 |
| `transaction_output_03` | 03_valid_sell_transaction | Sell/logout succeed. | Shared | Phase 1 |
| `transaction_output_04` | 04_valid_buy_transaction | Buy/logout succeed. | Shared | Phase 1 |
| `transaction_output_05` | 05_valid_refund_transaction | Refund/logout succeed. | Shared | Phase 1 |
| `transaction_output_06` | 06_valid_addcredit_transaction | Accepted. | Shared | Phase 1 |
| `transaction_output_07` | 07_several_valid_transactions | All accepted. | Shared | Phase 1 |
| `transaction_output_08` | 08_failed_transaction_omitted_from_dtf | Login accepted. Addcredit transaction accepted. Buy transaction denied because the game does not exist. Logout accepted. | Shared | Phase 1 |
| `transaction_output_09` | 09_verify_userame_length_alphabet_alignment | Create transaction accepted. The username field in the generated Daily Transaction File is exactly 15 characters long. The username is left-justified and unused positions are padded with spaces. | Shared | Phase 1 |
| `transaction_output_10` | 10_verify_monetary_formatting | Accepted. | Shared | Phase 1 |
| `transaction_output_11` | 11_verify_end_of_session_record | Logout succeeds. | Shared | Phase 1 |
| `transaction_output_12` | 12_verify_unused_numeric_fields | Accepted. | Shared | Phase 1 |
| `transaction_output_13` | 13_verify_unused_alphabetic_fields | Accepted. | Shared | Phase 1 |
| `transaction_output_14` | 14_verify_sell_record_field_order | Accepted. | Shared | Phase 1 |
| `transaction_output_15` | 15_verify_buy_record_field_order | Accepted. | Shared | Phase 1 |
| `transaction_output_16` | 16_verify_refund_record_field_order | Accepted. | Shared | Phase 1 |
| `transaction_output_17` | 17_verify_create_delete_addcredit_record_field_order | All accepted. | Shared | Phase 1 |
| `transaction_output_18` | 18_verify_all_valid_transactions_recorded_once | All accepted. | Shared | Phase 1 |
