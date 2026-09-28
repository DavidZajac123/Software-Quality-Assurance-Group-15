Phase 1 Requirements Tests

This directory contains all Front End requirements tests for Phase 1.

Tests are organized by transaction or behaviour category:

addcredit
buy
create
delete
invalid_input
list_games
login
logout
refund
sell
transaction_output

Each numbered test normally contains three files:

<category>_XX_input.txt
- Complete test-session console input stream.

<category>_XX_expected.txt
- Expected terminal behaviour/output.

<category>_XX_dtf_expected.txt
- Expected Daily Transaction File output.

Tests that contain invalid transactions still include the expected DTF result for the complete session. Invalid transactions must not create transaction records, although a later valid logout may still produce an end-of-session record.

The shared starting state used by tests is documented in:

../shared_test_data/