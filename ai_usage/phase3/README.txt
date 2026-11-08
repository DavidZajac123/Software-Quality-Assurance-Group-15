Phase 3 AI Usage

Generative AI was used during Phase 3 of the CSCI 3060U Software Quality Assurance project. Each group member is responsible for documenting their own AI use. Entries are identified by group member name.

[David] Tools used

- Claude (Claude Code, Claude Opus 5.5), 1–7 November 2026.
- ChatGPT, during Phase 3 review, planning, documentation and Git/submission support.

David's prompt and response history for both tools is recorded in `prompt_response_history.txt`.

[David] Claude use

Claude assisted with:
- auditing the Phase 1 tests, Phase 2 Front End, fixtures and repository structure;
- planning and creating the automated Phase 3 test infrastructure;
- diagnosing and correcting the `sell_15`, `refund_15` and `buy_13` test-design issues;
- creating David's terminal expected-output files for addcredit, buy, invalid_input, login, logout and transaction_output;
- reviewing the message catalogue, failure log, later team changes, SEARCH, amount-parsing changes and final repository state;
- running the final Run 6 verification on commit `fdb0ce8`, which passed 152/152 tests with all 154 DTF outputs matching;
- assisting with Phase 3 documentation and status summaries.

Claude did not copy actual Front End output into expected-output files, did not write the final Front End source changes, did not create teammates' AI records, and did not stage, commit or push repository changes.

Some ideas proposed by Claude, including Money parsing, list_accounts and SEARCH work, were later implemented by Raihan, not by Claude.

[David] ChatGPT use

ChatGPT was used primarily to:
- review Claude-assisted Phase 3 work and test corrections;
- interpret the Phase 3 requirements;
- advise on Git branching, merging and pull-request workflow;
- review and condense AI-use documentation;
- interpret team updates and final test results;
- help plan final verification, documentation and submission packaging.

ChatGPT did not directly edit repository files, run the Front End, or perform Git history-changing actions.

AI-assisted testing, analysis and documentation work was reviewed against the applicable Phase 1 test intent, Phase 2 design document and/or the group's message catalogue before being incorporated into the project.

`prompt_response_history.txt` contains a condensed record of David's relevant prompts and AI responses. Prompts and responses are summarized rather than reproduced verbatim while preserving the purpose, constraints, affected project areas and substantive AI contribution.

[Raihan] Tools used
 
- Claude (Anthropic), in the Claude desktop app (Cowork), 1-7 November 2026. Claude Opus 5.5 did the work. Claude Sonnet 5.5 answered two messages: the explanation on 3 November and the question about this record's git commands on 7 November.
 
Raihan's record is in prompt_response_history.txt, in the entries marked [Raihan]. Each entry has Raihan's message to Claude, the files Claude read, Claude's reply in the chat, and the files Claude helped to edit. Messages and replies are word for word, except where an entry says otherwise. Claude's tool calls and background actions are not listed.
 
[Raihan] Claude use
 
Claude produced:
- phase3/message_catalogue.md: the exact terminal wording and order of checks, taken from the group's Phase 2 design document and the messages in the code. The group used it as the reference for the terminal expected files.
- The terminal expected files for the 12 list_games tests, the 8 new list_accounts tests and the 9 new SEARCH tests (with the search_06 fixture). A Python script wrote them from the catalogue and the test data. None was copied from Front End output.
- The rewrite of 50 terminal expected files (create, delete, refund and sell, including sell_10) from the catalogue, after run 2 showed that they followed the Front End's wording instead of the catalogue.
- Every Front End source change in commit fdb0ce8: the catalogue wording in all transactions, the list_games and list_accounts formats, the new SearchTransaction, and the Money::parse fix. Claude wrote these files pasted from Raihan's copy of the repository, and Raihan committed and pushed them under his account.
- Two new tests, addcredit_12 and addcredit_13, for the amount-parsing fault (F12).
- Test runs 2 to 5, on a Linux copy of the repository, and the evidence folders phase3/run2_evidence to phase3/run5_evidence (rebuilt from the saved logs of those runs).
- The failure log (run history, rows F1 to F12, "How to run the tests", and the open questions with a plan for each), the corrections David asked for on 7 November, and its PDF copy.
- phase3/Phase3_Test_Table.md, which lists every test by its full name (TA feedback).
- A script that models the catalogue rules. It checked all 152 terminal expected files and compared the program's output with the model on 6,000 random sessions. It never wrote an expected file from program output.
- Step-by-step plans, plain explanations, Discord messages and a private planning document ("Ray's Phase 3 Playbook") for Raihan.
 
The scripts Claude used to write and check files ran in Claude's own workspace and are not in the repository.
 
What Raihan did:
- Set the scope and the working rules: Claude plans and leads, Raihan runs every git command and posts every message, documents are for him only, and replies are kept short.
- Passed on the Phase 3 handout, the client's SEARCH change, the TA's Phase 1 feedback and David's and Sanjith's updates, and posted the SEARCH questions to the client on Slack.
- Pulled the repository for Claude each time and reported what his teammates had pushed.
- Stopped the work once (3 November) to ask for a plain explanation of the expected-file work before going on.
- Made commits 9ef686a, 21725f8 and fdb0ce8 and the final Phase 3 commit, merged pull request #7, and pushed.
- Posted the updates to the group on Discord, including the note to Sanjith about the rewritten files.
 
Claude did not stage, commit, push or merge anything. Before each batch of files was committed, Claude ran the whole test suite on a copy of the repository (152 of 152 passed for the final code). Run 6 was then run on David's machine by Claude Code at David's request (152 of 152, and all 154 DTFs match).
