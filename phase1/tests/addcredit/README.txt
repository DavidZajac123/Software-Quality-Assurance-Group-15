Addcredit Requirements Tests

This folder contains the Phase 1 requirements tests for the addcredit transaction.

Number of test cases: 11

Each test uses the following file naming convention:

addcredit_XX_input.txt
- Complete console input stream for the test session.

addcredit_XX_expected.txt
- Expected terminal behaviour/output for the test.

addcredit_XX_dtf_expected.txt
- Expected Daily Transaction File contents for the test session.

These tests cover standard-user and admin addcredit behaviour, invalid users, the $1000 per-session limit, cumulative additions, invalid amounts, balance updates, and account-balance overflow.

All tests are based on the Front End requirements and client/TA clarifications received for Phase 1.