Phase 1 Test Scripts

This folder contains the planned scripts used to execute the Front End requirements tests.

During Phase 1, the Front End implementation does not yet exist. Therefore, these scripts document the intended automated testing process that will be used once the Front End is available.

The planned test process is:

1. Select a test input file.
2. Run the Front End using the test input file as redirected console input.
3. Save the terminal output to the results/actual folder.
4. Save the generated Daily Transaction File output.
5. Compare the actual terminal output against the corresponding expected-output file.
6. Compare the actual Daily Transaction File against the corresponding expected DTF file.
7. Store comparison results in results/comparisons.

Test files follow the naming convention:

<category>_<test number>_input.txt
<category>_<test number>_expected.txt
<category>_<test number>_dtf_expected.txt

Example:

buy_01_input.txt
buy_01_expected.txt
buy_01_dtf_expected.txt