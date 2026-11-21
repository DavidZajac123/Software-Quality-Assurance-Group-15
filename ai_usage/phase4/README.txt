Phase 4 AI Usage

Generative AI was used during Phase 4 of the CSCI 3060U Software Quality Assurance project. Each group member is responsible for documenting their own AI use. Entries are identified by group member name.

[David] Tools used

- Claude (Claude Code, Claude Opus 5.5), 15–20 November 2026.
- ChatGPT (GPT-5.6 Sol), 16–20 November 2026.

David's prompt and response history for both tools is recorded in `prompt_response_history.txt`, which includes both David's Claude record and David's ChatGPT record, as a separate record for each tool.

[David] Claude use

David's primary assigned Phase 4 contribution was the Back End file input/output portion:
- `phase4/src/utilities/money.py`;
- `phase4/src/utilities/fixed_width_format.py`;
- `phase4/src/fileio/master_file_reader.py`;
- `phase4/src/fileio/master_file_writer.py`;
- `phase4/src/fileio/transaction_file_reader.py`.

Claude assisted with:
- inspecting the replacement Front End B folder (read-only) to identify the files that define its master-file and Daily Transaction File formats, and the old Phase 2/3 artifacts that should not be used for Back End work;
- identifying David's file-I/O responsibilities and the interfaces to agree with Raihan and Sanjith before coding;
- reviewing the Phase 4 skeleton created by Raihan and recommending an implementation order;
- reviewing the fixed-width master-file layouts (28, 49 and 42 characters) and the Front End B transaction layouts for codes 00 to 06;
- implementing David's five assigned file-I/O and utility files one at a time, with David reviewing each before continuing;
- reviewing edge cases and compatibility decisions, including LF/CRLF input, bare versus space-padded `END` lines, valid `00` layouts, the `06` money field being the amount added, ignored `02`, `06` and `00` fields, and a merged file that does not end with a `00` transaction;
- running temporary scratchpad checks outside the repository after each file;
- building Front End B from its source into a scratchpad folder and confirming that it could read master files produced by the new writer;
- identifying that Front End B does not recognise the new `AM` (Account Manager) account type;
- performing later read-only integration audits of the state and transaction code and identifying problems including transaction `apply()` methods that attempted to construct data classes through postponed type annotations and missing buyer/seller existence checks in refund validation;
- comparing the latest Phase 4 branches with `main` to determine whether any newer work remained unmerged;
- inspecting Raihan's final BackEnd and ErrorLog pull request and checking its behaviour using temporary scratchpad smoke runs;
- identifying remaining known limitations, including maximum-credit overflow and BUY transactions not verifying the corresponding game listing.

During the final integration period, David also made one source-code correction outside his originally assigned file-I/O package. After reviewing Sanjith's transaction pull request, David corrected `phase4/src/transactions/sell_transaction.py` so that `SellTransaction.validate()` checks that the seller exists and that the game is not already listed, rather than incorrectly referring to buyer/refund fields. David made, reviewed, tested, committed and pushed this correction himself.

Decisions on unresolved behaviour were made by David or the group; Claude provided analysis, implementation assistance for David's assigned files, read-only reviews, and temporary scratchpad checks.

Claude did not modify Front End B, did not create a committed automated test suite (comprehensive testing belongs to Phase 5), and did not stage, commit, push or merge Git changes. Repository and Git actions were performed by David.

[David] ChatGPT use

ChatGPT was used during Phase 4 to:
- review and interpret the official project requirements and Front End B compatibility details;
- compare the working Phase 4 project against Front End B;
- review Claude-assisted implementations of David's assigned file-I/O code;
- identify edge cases and malformed-input behaviour;
- guide Git, branch, pull-request and merge workflow;
- review the Phase 4 design document for consistency with the implementation;
- review Sanjith's transaction changes and identify an incorrect `SellTransaction.validate()` implementation;
- provide the corrected SELL validation logic that David manually applied, reviewed and committed;
- guide targeted CREATE, SELL, BUY and REFUND integration checks after the transaction fixes;
- review the status of Raihan's control/ErrorLog work and the later pull-request audit;
- guide the final end-to-end Back End smoke test on merged `main` and verification of the three generated master files;
- identify and document remaining known limitations;
- help reconcile and clean the final Phase 4 README and design-document wording;
- help prepare and update the Phase 4 AI-usage documentation.

ChatGPT did not directly modify repository files or Git history. Where ChatGPT supplied code or replacement text, David manually reviewed and applied it. David performed all repository edits, commands, commits, pushes and merges himself.

AI-assisted code and recommendations were reviewed against the Phase 4 requirements, the group's design decisions, Front End B's file formats, the merged implementation and the final smoke-test results before being incorporated into the project.

`prompt_response_history.txt` contains a condensed record of David's relevant prompts and AI responses, with both David's Claude record and David's ChatGPT record included. Prompts and responses are summarized rather than reproduced verbatim while preserving the purpose, constraints, affected project areas and substantive AI contribution.