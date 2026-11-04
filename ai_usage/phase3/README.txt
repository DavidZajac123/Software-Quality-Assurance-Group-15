Phase 3 AI Usage

Generative AI was used during Phase 3 of the CSCI 3060U Software Quality Assurance project.

Each group member is responsible for adding the record of their own AI use. Entries are marked with the group member's name, for example [David], so that each member's work can be told apart.

[David] Tools used

- Claude (Claude Code, using the Claude Opus 5.5 model), during Phase 3 work from 1 to 3 November 2026. This use is recorded in prompt_response_history.txt.
- ChatGPT. David also used ChatGPT during Phase 3. Its prompt and response record will be added separately.

[David] Claude was used to assist with:

- auditing the repository, the Phase 1 tests, the shared test data and fixtures, and the Phase 2 source against the Phase 2 design document, without changing any files;
- preparing a Phase 3 repair and test plan, including open requirement questions for the group and the client;
- writing phase1/scripts/run_tests.sh and the run_tests.bat wrapper, and testing them against a stand-in program before they were used on the Front End;
- adding .gitattributes and .gitignore, and fixing test-folder structure problems (a misplaced logout_02 expected file, an empty stray buy_11 folder and a folder name containing a space);
- analysing the first full test run, which David ran, and confirming the observed sell_15 and refund_15 DTF mismatches;
- diagnosing sell_15 and refund_15 as test-design problems, and splitting each into two single-session tests with fixtures standing in for the Back End;
- starting the Phase 3 failure-log draft (phase3/Phase3_Failure_Log_Draft.md) and updating it;
- writing the first nine sample terminal expected-output files;
- reviewing the group's phase3/message_catalogue.md;
- writing the terminal expected-output files for David's assigned categories (addcredit, buy, invalid_input, login, logout and transaction_output), 71 files in six reviewed batches;
- analysing buy_13 and adding a fixture that makes Seller1 full-standard, so that the test reaches the own-game rule it is meant to verify;
- preparing this Phase 3 AI-use record.

[David] What Claude did not do

- Claude did not write expected output by copying the Front End's actual output. Expected files were derived from each test's input, its prose expected result, its data files and the message catalogue.
- Claude did not write phase3/message_catalogue.md.
- Claude did not change the Front End source code.
- Claude did not run the full test suite; David ran it.
- Claude did not stage, commit or push anything. David reviewed and approved each batch before staging or committing the work.

[David] Advice from Claude that has not been applied to the repository

- An analysis of a possible overflow in Money::parse for very large amounts, with a proposed fix and a proposed test.
- A proposed set of list_accounts tests.
- A draft SearchTransaction class and a list of possible SEARCH tests. Raihan is responsible for SEARCH.

[David] Programs run by Claude outside the full test suite

- The runner was tested against a stand-in program on a temporary copy of the tests.
- A copy of Money.cpp was compiled with a small test program outside the repository.
- The Front End was run directly on sell_15a, sell_15b, refund_15a, refund_15b and buy_13 to check only their Daily Transaction Files, with output written to a temporary folder. These runs were not used to write any expected output.

AI-assisted test and implementation work was reviewed against the applicable Phase 1 test intent, Phase 2 design document and/or the group's message catalogue before being incorporated into the project.

The file prompt_response_history.txt contains a condensed record of David's Claude use during Phase 3. Both the prompts and responses are summarized rather than reproduced verbatim. The summaries preserve the purpose of each request, the important constraints, the project areas affected, and the substantive AI contributions.