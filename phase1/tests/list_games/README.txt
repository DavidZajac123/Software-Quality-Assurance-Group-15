List Games Requirements Tests

This folder contains the Phase 1 requirements tests for the list_games transaction.

Number of test cases: 12

These tests cover displaying multiple, single, and zero available games; verifying displayed game names, sellers, and prices; login restrictions; and access for admin, full-standard, buy-standard, and sell-standard users.

File naming convention:
list_games_XX_input.txt
list_games_XX_expected.txt
list_games_XX_dtf_expected.txt

Deadline assumption: list_games is display-only and does not create a Daily Transaction File transaction record because the requirements/client clarifications define no transaction code or DTF record format for list_games. A valid logout still produces the normal 00 end-of-session DTF record.
