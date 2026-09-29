Refund Requirements Tests

This folder contains the Phase 1 requirements tests for the refund transaction.

Number of test cases: 15

These tests cover admin-only access, valid and invalid buyer/seller usernames, blank input, nonnumeric refund amounts, balance transfers, sufficient and insufficient seller credit, zero/negative refund amounts, removal of the corresponding refunded game from the buyer's collection, and re-purchasing a refunded game.

Most tests use refund_XX_dtf_expected.txt. Refund 15 spans two sessions and therefore uses refund_15_session1_dtf_expected.txt and refund_15_session2_dtf_expected.txt.
