Phase 1 Front End Requirements Tests

Total test cases: 131

Categories:
- addcredit: 11
- buy: 13
- create: 11
- delete: 7
- invalid_input: 10
- list_games: 12
- login: 9
- logout: 10
- refund: 15
- sell: 15
- transaction_output: 18

Each ordinary test has a literal line-by-line console input stream, expected terminal behaviour, and an exact Daily Transaction File expectation. Tests that span two sessions use separate session-specific DTF expected files because each valid logout writes a separate DTF.

The default starting-state files are in ../shared_test_data/. Tests requiring a different starting state use an override from ../test_fixtures/ as documented there.
