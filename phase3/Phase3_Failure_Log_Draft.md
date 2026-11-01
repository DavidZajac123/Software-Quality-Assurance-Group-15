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

## Predicted, not yet observed (remove from the final log)

| Test | Prediction | Why |
|---|---|---|
| `buy_01`, `sell_10` | `TERMINAL_DIFF` on the seller prompt | Expected files use the Figure 6 prompt `Enter seller's username:`; the source prints `Enter seller username:` (R1) |
| `buy_13` | Own-game rule not reached | Design Table 8 notes that it stops at the permission check |
| New overflow test | Very large amount accepted | Found by reading `Money.cpp` and probing a copy |

## Source of terminal expected wording

Line sequences come from the test input, the prose expected result, and design Tables 3, 5 and 6. None were copied from Front End output.

**Exact wording from the design**

| Text | Source |
|---|---|
| `Error: "<code>" is not a valid transaction code.` | Table 5 |
| `Error: please log in before using "<code>".` | Table 5 |
| `Error: your account type cannot use "<code>".` | Table 5 |
| `Enter game name:` (buy) | Figure 6, step 7 |
| `Enter seller's username:` | Figure 6, step 9 |
| `Logout successful.` | Figure 6, step 32 |

**Wording from the current message catalogue (not yet ratified by the group)**

The design defines the behaviour but not the words. This text matches the current source strings, so these lines cannot catch poor wording.

| Text | Used for |
|---|---|
| `Enter username:` | Login prompt |
| `Login successful.` | Login accepted |
| `Error: account does not exist.` | Login with an unknown account |
| `Enter game name:` (sell), `Enter price:`, `Game listed successfully.` | Sell |
| `Game purchased successfully.` | Buy accepted; **conflicts with the Figure 6 label, see R1** |
| `Error: game is not available.` | Buy of a game not for sale |
| `Enter amount:`, `Credit added successfully.`, `Error: session credit limit exceeded.` | Addcredit |
| `<name> \| <seller> \| $<price>` | `list_games` line; separators and `$` are not in the design, see R3 |

## Open requirement questions

| ID | Question | Who decides | Affects |
|---|---|---|---|
| R1 | Prompt: Figure 6 says `Enter seller's username:`, source says `Enter seller username:`. Confirmation: Figure 6 shows only `Purchase successful ...`, source says `Game purchased successfully.` Which is correct? | Group | Every test that runs `buy` |
| R2 | Is the current message catalogue approved? | Group | All catalogue lines |
| R3 | What is the `list_games` line format? | Group or TA | `list_games_*` |
| R4 | A refund names no game. Which game leaves the buyer's collection, and is that the Back End's job? | Client or TA | `refund_14`, `refund_15b` fixture |
