#!/usr/bin/env bash
# Builds the Front End, runs every requirements test, compares terminal and
# Daily Transaction File output against the expected files, and writes a summary.
#
# Usage (from any directory):
#   phase1/scripts/run_tests.sh              build, then run all tests
#   phase1/scripts/run_tests.sh --no-build   run all tests with the existing build
#
# Optional environment variables:
#   CXX              compiler to use (default: g++)
#   FRONTEND         program to test (default: phase2/frontend.exe)
#   TIMEOUT_SECONDS  time limit for one test (default: 10)
#
# Exit status: 0 = all tests passed, 1 = at least one failed, 2 = could not run.

set -u

# All paths below are relative to the repository root, so spaces in the
# location of the repository never reach the program's command line.
cd "$(dirname "${BASH_SOURCE[0]}")/../.." || exit 2

TESTS=phase1/tests
SHARED=phase1/shared_test_data
FIXTURES=phase1/test_fixtures
ACTUAL=phase1/results/actual
COMPARE=phase1/results/comparisons
SUMMARY="$COMPARE/summary.txt"
FRONTEND="${FRONTEND:-phase2/frontend.exe}"
TIMEOUT_SECONDS="${TIMEOUT_SECONDS:-10}"

# Compiles every source file, stopping the run if the build fails.
build_frontend() {
    local sources
    mapfile -t sources < <(find phase2/src -name '*.cpp' | LC_ALL=C sort)
    echo "Building $FRONTEND with ${CXX:-g++} ..."
    "${CXX:-g++}" -std=c++17 -Wall -Wextra "${sources[@]}" -o "$FRONTEND"
}

# Prints the test's fixture override if it has one, otherwise the shared file.
master_file() {
    local id="$1" name="$2"
    if [ -f "$FIXTURES/$id/$name" ]; then
        echo "$FIXTURES/$id/$name"
    else
        echo "$SHARED/$name"
    fi
}

# Compares one expected file with one actual file, ignoring only CR/LF
# differences. Keeps the diff file when they differ.
files_match() {
    local expected="$1" actual="$2" diff_file="$3"
    if diff --strip-trailing-cr "$expected" "$actual" > "$diff_file"; then
        rm -f "${diff_file:?}"
        return 0
    fi
    return 1
}

# Runs one test and reports each problem by adding it to the problems array.
run_test() {
    local input="$1" dir id users games collection status
    dir="$(dirname "$input")"
    id="$(basename "$input" _input.txt)"
    problems=()

    users="$(master_file "$id" current_users.txt)"
    games="$(master_file "$id" available_games.txt)"
    collection="$(master_file "$id" game_collection.txt)"

    timeout "$TIMEOUT_SECONDS" "$FRONTEND" "$users" "$games" "$collection" "$ACTUAL/$id" \
        < "$input" > "$ACTUAL/${id}_actual.txt" 2> "$ACTUAL/${id}_stderr.txt"
    status=$?

    [ -s "$ACTUAL/${id}_stderr.txt" ] || rm -f "${ACTUAL:?}/${id:?}_stderr.txt"

    if [ "$status" -eq 124 ]; then
        problems+=("TIMEOUT after ${TIMEOUT_SECONDS}s")
    elif [ "$status" -gt 128 ]; then
        problems+=("CRASH exit status $status")
    elif [ "$status" -ne 0 ]; then
        problems+=("NONZERO_EXIT status $status")
    fi

    # Terminal output: only the exact file counts; the prose file is never used.
    if [ ! -f "$dir/${id}_terminal_expected.txt" ]; then
        problems+=("TERMINAL_EXPECTED_MISSING")
    elif ! files_match "$dir/${id}_terminal_expected.txt" \
        "$ACTUAL/${id}_actual.txt" "$COMPARE/${id}_output_diff.txt"; then
        problems+=("TERMINAL_DIFF")
    fi

    compare_dtfs "$dir" "$id"
}

# Compares every expected DTF, then reports any session file nothing expected.
# An empty <id>_dtf_expected.txt means the run must not write any DTF.
compare_dtfs() {
    local dir="$1" id="$2" expected session actual
    local -A wanted=()
    local single="$dir/${id}_dtf_expected.txt"
    local sessions=("$dir/${id}"_session*_dtf_expected.txt)
    [ -f "${sessions[0]}" ] || sessions=()

    if [ -f "$single" ] && [ "${#sessions[@]}" -gt 0 ]; then
        problems+=("DTF_EXPECTED_AMBIGUOUS")
    elif [ ! -f "$single" ] && [ "${#sessions[@]}" -eq 0 ]; then
        problems+=("DTF_EXPECTED_MISSING")
    fi

    if [ -s "$single" ]; then
        wanted[1]="$single"
    fi
    for expected in ${sessions[@]+"${sessions[@]}"}; do
        session="${expected##*_session}"
        session="${session%%_*}"
        wanted[$session]="$expected"
    done

    for session in "${!wanted[@]}"; do
        actual="$ACTUAL/${id}_session${session}.txt"
        if [ ! -f "$actual" ]; then
            problems+=("DTF_MISSING session $session")
        elif ! files_match "${wanted[$session]}" "$actual" \
            "$COMPARE/${id}_session${session}_dtf_diff.txt"; then
            problems+=("DTF_DIFF session $session")
        fi
    done

    for actual in "$ACTUAL/${id}"_session*.txt; do
        [ -f "$actual" ] || continue
        session="${actual##*_session}"
        session="${session%.txt}"
        if [ -z "${wanted[$session]+set}" ]; then
            problems+=("DTF_UNEXPECTED session $session")
        fi
    done
}

# Warns about fixture folders no test uses, such as a misspelled test id.
check_fixture_folders() {
    local folder
    for folder in "$FIXTURES"/*/; do
        [ -d "$folder" ] || continue
        folder="$(basename "$folder")"
        if [ -z "$(find "$TESTS" -name "${folder}_input.txt" -print -quit)" ]; then
            echo "WARNING  fixture folder has no matching test: $folder" | tee -a "$SUMMARY"
        fi
    done
}

if [ "${1:-}" != "--no-build" ]; then
    build_frontend || { echo "Build failed; no tests were run."; exit 2; }
fi

mkdir -p "$ACTUAL" "$COMPARE"
find "$ACTUAL" "$COMPARE" -type f ! -name README.txt -delete
: > "$SUMMARY"

total=0
passed=0
declare -A seen=()

while IFS= read -r input; do
    id="$(basename "$input" _input.txt)"
    total=$((total + 1))

    if [ -n "${seen[$id]+set}" ]; then
        problems=("DUPLICATE_TEST_ID")
    else
        seen[$id]=1
        run_test "$input"
    fi

    if [ "${#problems[@]}" -eq 0 ]; then
        passed=$((passed + 1))
        echo "PASS     $id" | tee -a "$SUMMARY"
    else
        reason="$(printf '%s; ' "${problems[@]}")"
        echo "FAIL     $id: ${reason%; }" | tee -a "$SUMMARY"
    fi
done < <(find "$TESTS" -type f -name '*_input.txt' | LC_ALL=C sort)

if [ "$total" -eq 0 ]; then
    echo "No tests found under $TESTS."
    exit 2
fi

check_fixture_folders

{
    echo
    echo "Total: $total   Passed: $passed   Failed: $((total - passed))"
} | tee -a "$SUMMARY"

[ "$passed" -eq "$total" ]
