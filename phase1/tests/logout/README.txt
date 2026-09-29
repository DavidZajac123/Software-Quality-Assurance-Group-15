Logout Requirements Tests

This folder contains the Phase 1 requirements tests for the logout transaction.

Number of test cases: 10

These tests cover valid logout, logout without a session, transaction attempts after logout, starting a new session after logout, and list_games behaviour after logout.

Most tests use logout_XX_dtf_expected.txt. Logout 09 spans two sessions and therefore uses logout_09_session1_dtf_expected.txt and logout_09_session2_dtf_expected.txt.
