"""
Back End of the Digital Games Distribution System (Group 15, CSCI 3060U, Phase 4).

Intention: the overnight batch program. It reads yesterday's master files and the
merged daily transaction file, applies every transaction in order, reports every
failed business constraint on the terminal, and writes the master files for
tomorrow's Front End runs.

Input files (read only):
    1. old current user accounts file   (28-character lines, ends with END)
    2. old available games file         (49-character lines, ends with END)
    3. old game collection file         (42-character lines, ends with END)
    4. merged daily transaction file    (any number of Front End daily transaction
       files concatenated, ending with an empty one: a single 00 line)

Output files (written, replacing any existing file):
    5. new current user accounts file
    6. new available games file
    7. new game collection file

Terminal output: one line per error, in the form ERROR: <msg>.

How to run (from the repository folder):
    python phase4/src/backend.py <old users> <old games> <old collection> <merged dtf> <new users> <new games> <new collection>

Example, using the sample data:
    python phase4/src/backend.py phase4/sample_data/current_users.txt phase4/sample_data/available_games.txt phase4/sample_data/game_collection.txt phase4/sample_data/merged_daily_transactions.txt phase4/sample_output/current_users.txt phase4/sample_output/available_games.txt phase4/sample_output/game_collection.txt

Exit status:
    0  the batch ran; failed constraints, if any, were logged and skipped
    1  a fatal input error stopped the batch; no new file was written
    2  wrong command-line arguments
"""
from __future__ import annotations

import sys

from control.back_end import BackEnd
from control.file_set import FileSet
from utilities.error_log import ErrorLog

EXPECTED_ARGUMENT_COUNT = 7
EXIT_BAD_ARGUMENTS = 2
USAGE = ("usage: python backend.py <old users> <old games> <old collection> "
         "<merged dtf> <new users> <new games> <new collection>")


def main(argv: list[str]) -> int:
    """Checks that seven file names were given, then creates and runs the Back End and returns its exit status."""
    if len(argv) != EXPECTED_ARGUMENT_COUNT + 1:
        print(USAGE, file=sys.stderr)
        return EXIT_BAD_ARGUMENTS
    files = FileSet(*argv[1:])
    return BackEnd(files, ErrorLog()).run()


if __name__ == "__main__":
    sys.exit(main(sys.argv))
