Transaction Output / Daily Transaction File Tests

This folder contains the Phase 1 tests for Daily Transaction File generation and formatting.

Number of test cases: 18

These tests cover transaction codes, record ordering, invalid transactions not creating records, alphabetic field padding, numeric and monetary formatting, unused fields, end-of-session records, and required field order for create, delete, sell, buy, refund, and addcredit transactions.

File naming convention:

transaction_output_XX_input.txt
transaction_output_XX_expected.txt
transaction_output_XX_dtf_expected.txt