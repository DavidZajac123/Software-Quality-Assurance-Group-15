Phase 4 AI Usage

Generative AI was used during Phase 4 of the CSCI 3060U Software Quality Assurance project. Each group member is responsible for documenting their own AI use. Entries are identified by group member name.

[David] Tools used

- Claude (Claude Code, Claude Opus 5.5), 15–16 November 2026.
- ChatGPT (GPT-5.6 Sol), 16 November 2026.

David's prompt and response history for both tools is recorded in `prompt_response_history.txt`, which includes both David's Claude record and David's ChatGPT record, as a separate record for each tool.

[David] Claude use

David's Phase 4 contribution was limited to the Back End file input/output portion:
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
- implementing the five files listed above, one at a time, with David reviewing each before the next was started;
- reviewing edge cases and compatibility decisions, including LF/CRLF input, bare versus space-padded `END` lines, valid `00` layouts, the `06` money field being the amount added, the `02` type and credit fields that the Back End ignores (decision B11), and a merged file that does not end with a `00` transaction;
- running temporary scratchpad checks outside the repository after each file;
- building Front End B from its source into a scratchpad folder and confirming that it could read master files produced by the new writer;
- identifying that Front End B does not recognise the new `AM` (Account Manager) account type.

Decisions on unresolved behaviour (for example, exact record widths, a missing final `00` transaction, and how `00` lines are validated) were made by David; Claude implemented them as instructed and flagged the remaining open group decisions.

Claude did not modify Front End B, did not change any file outside David's five assigned files and this AI-usage folder, did not create a committed automated test suite (testing belongs to Phase 5), and did not stage, commit, push or merge anything.

[David] ChatGPT use

ChatGPT was used during Phase 4 to review and interpret the official project requirements and FrontEnd B compatibility details, compare the working Phase 4 project against FrontEnd B, review Claude-assisted implementations of David's assigned file-I/O code, identify edge cases and malformed-input behavior, guide Git/branch workflow, and help prepare the Phase 4 AI-usage documentation.

ChatGPT did not directly modify repository source files, FrontEnd B, or Git history. David reviewed the recommendations and performed repository and Git actions himself.

AI-assisted code was reviewed against the Phase 4 requirements, the group's Phase 4 skeleton and recorded decisions, and Front End B's file formats before being incorporated into the project.

`prompt_response_history.txt` contains a condensed record of David's relevant prompts and AI responses, with both David's Claude record and David's ChatGPT record included. Prompts and responses are summarized rather than reproduced verbatim while preserving the purpose, constraints, affected project areas and substantive AI contribution.
