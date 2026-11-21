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

[Raihan] Tools used

- Claude (Claude desktop app, Cowork mode), Claude Fable 5.1, Claude Opus 5.5 and Claude Sonnet 5.5, 15–20 November 2026.

Raihan's prompt and response history is recorded in `prompt_response_history.txt` under the [Raihan] entries.

[Raihan] Claude use

Raihan's Phase 4 contribution was the plan, the design and the control and error-reporting code:
- the Phase 4 skeleton: folders, every class and method as a stub with its docstring, and the sample data;
- `phase4/design/`: the draw.io UML source, the seven figures, and `Phase_4_Design_Document.docx` and `.pdf`;
- `phase4/README.txt` (decisions B9 to B13 and known limitations L1 to L3) and the END lines of the sample data;
- `phase4/src/control/back_end.py` (the load, apply and write methods);
- `phase4/src/utilities/error_log.py`.

Claude assisted with:
- summarizing the Phase 4 handout and planning the team split and the class design;
- creating the skeleton: one class per file under phase4/src, a one-sentence docstring for every class and method, sample data and .gitignore rules;
- generating the UML class diagrams and the input/output, package and run-time figures in draw.io, and fixing Figures 1, 3 and 6 after David's review and his merged file I/O code;
- writing README decisions B1 to B13, known limitations L1 to L3, and the note under the smoke run;
- building the first full draft of the design document from the code's documentation comments, and checking later drafts against the merged code;
- reviewing David's edits to the design document and giving replacement wording;
- writing BackEnd._load_state, _apply_all and _write_state and ErrorLog.failed_constraint and fatal, following decisions B2 and B4, and checking them with the README example;
- reproducing two known failures on the merged code so they could be documented for Phase 5 (L2 and L3);
- preparing this AI-usage record.

Claude wrote the skeleton, the draw.io file, the figures and the README and sample-data changes into Raihan's local folder, and delivered the design document and all later text in the chat. Raihan reviewed every change, edited the design document in Word, pasted the code and README text himself, and added everything to the repository himself. In teammates' packages (fileio, transactions, state, Money, FixedWidthFormat) Claude only wrote the skeleton stubs and docstrings, not their code. Claude did not stage, commit, push or merge anything; Raihan made every commit and pull request.