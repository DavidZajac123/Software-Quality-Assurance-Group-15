Phase 5 AI Usage

Generative AI was used during Phase 5 of the CSCI 3060U Software Quality Assurance project. Each group member is responsible for documenting their own AI use. Entries are identified by group member name.

[David] Tools used

- Claude (Claude Code, Claude Opus 5.5), 24–27 November 2026.
- ChatGPT (GPT-5.6 Sol), 24–27 November 2026.

David's prompt and response history is recorded in `prompt_response_history.txt`, with a separate record for each tool.

[David] Phase 5 ownership and group context

In the group discussion, David agreed to take the Phase 5 unit tests for `fileio` and for `Money` and `FixedWidthFormat`:
- `phase4/src/utilities/money.py`;
- `phase4/src/utilities/fixed_width_format.py`;
- `phase4/src/fileio/master_file_reader.py`;
- `phase4/src/fileio/master_file_writer.py`;
- `phase4/src/fileio/transaction_file_reader.py`.

David's Phase 5 work also included preparing the shared pytest configuration used for his current tests.

The rest of the split was proposed by Raihan. Raihan proposed that he would take the control package (`BackEnd`), `main` in `backend.py`, `ErrorLog` and `FatalInputError`; that `BackEnd._apply_all` be used as the group's path-coverage method; that he would create the shared test-report template; and that he could take `state` from Sanjith to balance the workload. Raihan also stated that limitations L2 and L3 should be fixed during Phase 5 after the failing tests are first recorded, and reminded the group that expected values must come from the specification and design rather than from the program's current output.

David replied that he would likely be out for much of the day and would try to get the updated `main` merged by the end of the day, that the proposed split looked good, and that he would take `fileio` and `Money`/`FixedWidthFormat`. David did not decide the path-coverage method or whether L2 and L3 will be fixed; those were Raihan's proposals to the group.

In David's own work with Claude and ChatGPT, both `BackEnd.run()` and `BackEnd._apply_all()` were analysed as possible path-coverage methods. Whether the course's definition of full path coverage counts exception paths, and how it treats loops, was identified as uncertain, and no final path-coverage choice was made in that work.

[David] Claude use

Claude assisted with:
- a read-only Phase 5 readiness audit of the merged Phase 4 repository: the methods requiring tests, the absence of existing tests, methods that are hard to unit-test, a proposed test-file and fixture structure, a method-by-method statement-coverage plan, known limitations L2 and L3 as test targets, visible source issues, dependency concerns and a suggested division of work;
- analysing candidate methods for the single full-path-coverage method, including `BackEnd._apply_all()`, a path enumeration of `BackEnd.run()` and a comparison with loop-free alternatives, and identifying where the course definition is uncertain;
- proposing the shared pytest setup (`pytest.ini`, `phase5/tests/conftest.py` and a `.gitignore` entry) and explaining each setting, PyCharm test discovery and PyCharm's built-in Run with Coverage;
- analysing `Money.parse`, `Money.format`, `FixedWidthFormat.pad_right` and `FixedWidthFormat.field` and drafting a test-case table and pytest code for each;
- checking every proposal in a temporary scratchpad copy of the repository before it was shown to David, including a statement-coverage check written with the Python standard library.

What David reviewed and approved:
- David decided that statement coverage will be measured with PyCharm's built-in Run with Coverage and that neither `coverage.py` nor `pytest-cov` will be added;
- David asked Claude not to settle on `BackEnd._apply_all()` while the course's treatment of loops was unclear, and asked for a closer analysis of `BackEnd.run()`; the path-coverage choice was left open;
- David reviewed and approved the proposed `pytest.ini`, `conftest.py` and `.gitignore` entry, and then the two proposed test files, before Claude wrote each of them.

What was written into the repository (by Claude, at David's explicit request, after his approval):
- `pytest.ini` (new);
- `phase5/tests/conftest.py` (new; the `write_text` and `make_state` fixtures only);
- `.gitignore` (one line added: `.pytest_cache/`);
- `phase5/tests/unit/test_money.py` (new);
- `phase5/tests/unit/test_fixed_width_format.py` (new);
- `ai_usage/phase5/README.txt` and `ai_usage/phase5/prompt_response_history.txt` (this record), which David reviews before committing.

At David's explicit request, Claude created the local branch `phase5-utilities-tests` from `main` at commit `4832e1f`, staged only the first five files above and made one local commit. At David's request Claude then amended only that commit's message to remove the `Co-Authored-By` trailer. Claude did not push, pull, merge or rebase anything; David performs the remaining Git actions himself.

No Phase 4 source code was changed. All tests written so far pass, and no system failures have been found yet.

[David] ChatGPT use

ChatGPT was used during Phase 5 to:
- review the official Phase 5 and Phase 6 requirements with David and summarize their deadlines, deliverables and the instructor's clarifications;
- help prepare the handoff prompt that David gave Claude;
- review Claude's Phase 5 readiness audit, flag the uncertainty of using a loop-containing method for full path coverage, compare `BackEnd._apply_all()` and `BackEnd.run()` as candidates, and recommend keeping the choice provisional until the course's definition is clear;
- review the proposed shared pytest setup and recommend using no extra pytest plugins and PyCharm's built-in Run with Coverage;
- review Claude's proposed tests for `Money` and `FixedWidthFormat`;
- give Git workflow guidance, including keeping Phase 5 work off `main`, using the `phase5-utilities-tests` branch, checking the five-file commit scope, reviewing the branch before pushing, and removing the Claude `Co-Authored-By` trailer in favour of documenting AI use in `ai_usage/phase5/`;
- help draft David's messages to the group about Phase 5 ownership, his availability, the proposed testing split and keeping the path-coverage choice provisional.

ChatGPT did not directly modify repository files or Git history. ChatGPT reviewed, advised and drafted prompts and messages; David directed Claude himself and approved every repository change.

Prompts and responses in the history file are summarized rather than reproduced verbatim while preserving the purpose, constraints, affected project areas and substantive AI contribution.
