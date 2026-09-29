Sell Requirements Tests

This folder contains the Phase 1 requirements tests for the sell transaction.

Number of test cases: 15

These tests cover valid selling by permitted account types, buy-standard restrictions, maximum and minimum prices, the client-clarified example-defined game-name field boundary (26 characters), duplicate game names, same-session restrictions, invalid prices, blank game names, and next-session availability.

Most tests use sell_XX_dtf_expected.txt. Sell 15 spans two sessions and therefore uses sell_15_session1_dtf_expected.txt and sell_15_session2_dtf_expected.txt.
