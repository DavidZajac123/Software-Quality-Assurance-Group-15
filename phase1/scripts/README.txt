Front End Test Scripts

run_tests.sh builds the Front End from phase2/src, runs every requirements test in phase1/tests, and compares the terminal output and each Daily Transaction File with the expected files. run_tests.bat starts it on Windows with Git Bash.

Windows:           phase1\scripts\run_tests.bat
Git Bash or Linux: bash phase1/scripts/run_tests.sh
Reuse the build:   add --no-build

Results go to phase1/results/actual (output of each test) and phase1/results/comparisons (summary.txt and a diff file for each mismatch). Both folders are emptied at the start of every run.

Exit status: 0 = every test passed, 1 = at least one failed, 2 = could not run.

Full instructions: phase3/Phase3_Failure_Log_Draft.md, section "How to run the tests".

Test files follow the naming convention:

<category>_<test number>_input.txt
<category>_<test number>_expected.txt
<category>_<test number>_terminal_expected.txt
<category>_<test number>_dtf_expected.txt   (or _session<N>_dtf_expected.txt for tests with several sessions)
