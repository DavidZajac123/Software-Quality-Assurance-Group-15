# Phase 3 Failure Log (Draft)

Only failures seen in a real run belong in the failure log. Predictions and open questions are kept apart.

## Run history

| Run | Date | Code version | Result | Notes |
|---|---|---|---|---|
| 1 | 2026-11-01 02:08 | `406e6df` plus uncommitted test infrastructure; `Money.cpp`, `buy_13` and SEARCH unchanged | 131 total, 0 passed, 131 failed | No `*_terminal_expected.txt` files existed yet, so terminal output was not compared in this run |

## Test-infrastructure gap (not Front End failures)

All 131 tests in run 1 reported `TERMINAL_EXPECTED_MISSING`. This means the exact terminal expected files had not been written. It says nothing about the Front End's behaviour, so these are not logged as 131 failures.

## Observed failures

| Test | What it tests | Failure observed | Root cause category | Actual cause | Fix | Status |
|---|---|---|---|---|---|---|
| `sell_15` | A game sold in one session can be bought in a later session | Run 1: `DTF_DIFF session 2`. Expected session 2 DTF had the `04` record below; actual had only the `00` record. Terminal showed `Error: game is not available.` | Test design | One Front End run cannot show the later-session effect. Each login re-reads the master files, the Front End never writes them, and the Back End that would add the game is not part of the run. Design Table 8 notes this | Split into `sell_15a` and `sell_15b`, one run per session. A `sell_15b` fixture lists the game, standing in for the Back End. Expected DTF records unchanged | Test corrected; awaiting full rerun |
| `refund_15` | A buyer can buy a refunded game again in a later session | Run 1: `DTF_DIFF session 2`. Expected session 2 DTF had the `04` record below; actual had only the `00` record. Terminal showed `Error: buyer already owns this game.` | Test design | Same limitation. The unchanged collection file still lists Buyer1 as owning Minecraft. Design Table 8 notes this | Split into `refund_15a` and `refund_15b`. A `refund_15b` fixture removes Buyer1's Minecraft, standing in for the Back End. Expected DTF records unchanged. Relies on open question R4 | Test corrected; awaiting full rerun |

### Observed DTF mismatches (run 1)

Session 1 matched for both tests. In session 2:

`sell_15`, from `sell_15_session2_dtf_diff.txt`:

```text
1d0
< 04 NextSessionGame            FullUser        BuyUser         025.00
```

`refund_15`, from `refund_15_session2_dtf_diff.txt`:

```text
1d0
< 04 Minecraft                  Seller1         Buyer1          050.00
```

## Test corrections (not observed failures)

| Test | Problem with the test | Correction | Why it is not in the failure log |
|---|---|---|---|
| `buy_13` | Meant to check that a seller cannot buy their own game, but the shared data made Seller1 sell-standard. The account-type permission check refused `buy` first, so the own-game rule was never reached. Design Table 8 notes this | Fixture `phase1/test_fixtures/buy_13/current_users.txt` makes Seller1 full-standard; all other data is shared. Input and expected DTF unchanged. Expected terminal error: `Error: you cannot buy your own game.` | Run 1 passed its DTF check and had no terminal comparison, so no failure was ever observed |

## Predicted, not yet observed (remove from the final log)

| Test | Prediction | Why |
|---|---|---|
| Every test with a terminal expected file | `TERMINAL_DIFF` wherever the source wording differs from `phase3/message_catalogue.md`, for example the login line (`Login successful.` instead of `Login successful. Welcome, <user> (<type>).`) | Found by comparing source strings with the catalogue, not by a run |
| Tests that run `buy`, such as `buy_01` | `TERMINAL_DIFF` on the seller prompt and the success line | The catalogue uses `Enter seller's username:` and `Purchase successful: <game> from <seller> for <price>.`; the source prints `Enter seller username:` and `Game purchased successfully.` |
| New overflow test | Very large amount accepted | Found by reading `Money.cpp` and probing a copy |

## Source of terminal expected wording

Every `*_terminal_expected.txt` file is written from the test's input, its prose expected result, the data files it runs with (shared data or its fixture), and `phase3/message_catalogue.md`. The catalogue was adopted by the group on 3 November 2026 and is the reference for all terminal wording and the order of checks. No expected file was copied from Front End output.

**Wording taken directly from the Phase 2 design** (the catalogue repeats it unchanged)

| Text | Design source |
|---|---|
| `Error: "<code>" is not a valid transaction code.` | Table 5 |
| `Error: please log in before using "<code>".` | Table 5 |
| `Error: already logged in. Log out before logging in again.` | Table 5 |
| `Error: your account type cannot use "<code>".` | Table 5 |
| `Enter game name:` (buy) | Figure 6, step 7 |
| `Enter seller's username:` | Figure 6, step 9 |
| `Logout successful.` | Figure 6, step 32 |

**Wording adopted by the group in the catalogue**

The design defines the behaviour (the prompts, their order and the checks) but not these words. Examples:

| Text | Used for |
|---|---|
| `Login successful. Welcome, <username> (<type>).` | Login accepted |
| `Error: "<username>" is not a registered user.` | Unknown account |
| `Purchase successful: <game> from <seller> for <price>.` | Buy accepted. Figure 6 shows only the start, `Purchase successful ...`; the catalogue completes it |
| `Enter amount of credit to add:`, `Credit added: <amount> to <username>.` | Addcredit |
| `Games available for purchase:`, then fixed-width lines | `list_games` |

See the catalogue for the full list. An empty value is shown as `""`, for example `Error: "" is not a registered user.` (group decision, 3 November 2026).

## Resolved by the message catalogue

| Former question | Resolution |
|---|---|
| Seller prompt: design `Enter seller's username:` or source `Enter seller username:` | `Enter seller's username:`, as in the design |
| Buy success text, which Figure 6 shows only in part | `Purchase successful: <game> from <seller> for <price>.` |
| Approval of the terminal wording | The catalogue was adopted by the group on 3 November 2026 |
| `list_games` line format | Header line, then name padded to 26, seller padded to 15, then the price |

Where the source still prints different wording, that remains a prediction until a run shows it (see "Predicted, not yet observed").

## Open requirement questions

| ID | Question | Who decides | Affects |
|---|---|---|---|
| R4 | A refund names no game. Which game leaves the buyer's collection, and is that the Back End's job? | Client or TA | `refund_14`, `refund_15b` fixture |
