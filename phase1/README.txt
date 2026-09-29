Phase 1 - Front End Requirements Testing Assets

Contents:
- documents/: Phase 1 test-case documentation and Test Plan.
- tests/: 131 Front End requirements tests, grouped by transaction/category.
- scripts/: planned test execution scripts.
- results/: planned actual-output and comparison locations.

Test file convention:
- *_input.txt: literal console input, one input line per line in the file.
- *_expected.txt: expected observable terminal behaviour.
- *_dtf_expected.txt: exact expected Daily Transaction File content.

For multi-session tests, session-specific DTF expected files are used because each valid logout writes a separate DTF.

Deadline assumptions adopted where no further clarification could be obtained:
1. list_games is display-only and creates no DTF transaction record because no code/record format is defined for it.
2. When an account is deleted, Game Collection entries owned by that user are removed as a documented group design decision.
3. Where a written field length conflicts with the provided example, the client-confirmed example length is used.
4. Available Games records use the example-defined 49-character line format.
5. Failed/incomplete transactions are omitted from the DTF.
