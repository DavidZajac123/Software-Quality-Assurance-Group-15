Buy Requirements Tests

This folder contains the Phase 1 requirements tests for the buy transaction.

Number of test cases: 13

Each test uses the following file naming convention:

buy_XX_input.txt
- Complete console input stream for the test session.

buy_XX_expected.txt
- Expected terminal behaviour/output for the test.

buy_XX_dtf_expected.txt
- Expected Daily Transaction File contents for the test session.

These tests cover valid purchases, user-type permissions, nonexistent games, insufficient credit, exact-credit purchases, duplicate ownership, blank input, seller matching, account balance updates, game collection updates, and sellers attempting to purchase their own listed games.

All tests are based on the Front End requirements and client/TA clarifications received for Phase 1.