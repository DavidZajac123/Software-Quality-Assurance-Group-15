# Phase 3 Message Catalogue

The exact text the Front End prints on standard output. Every `*_terminal_expected.txt` file is written from this file, the test's input file, and the data files the test runs with (shared data, or its fixture). Never copy an expected file from the program's output: where the program prints something different, that is a failure to log and fix.

Source: the Phase 2 design (Table 5 gates, Table 6 order of checks, Figure 6) and the design's message list. Adopted by the group on 3 November 2026. SEARCH was added for the client's change request.

## Rules for writing an expected file

1. Each prompt is printed on its own line, exactly as written below. The program does not echo what the user types, so input values never appear unless a message quotes them.
2. A transaction asks for all of its fields first. Then it applies its checks in the order listed and prints only the first one that fails. If every check passes, it prints its success line.
3. If the input ends during a transaction's prompts, nothing more is printed for that transaction.
4. `<...>` is replaced by the real value. Amounts are printed with two decimals and no leading zeros: `50.00`, `0.00`, `1000.00`, `999500.00`.
5. A valid amount is digits, optionally followed by a point and one or two digits (`5`, `5.5`, `5.50`). Blank text, letters, a sign, two points or three decimals are not valid amounts.

## Before any transaction runs (every input line)

| Situation | Printed |
| --- | --- |
| The line is not a transaction code (including a blank line) | `Error: "<code>" is not a valid transaction code.` |
| Nobody is logged in and the code is not `login` | `Error: please log in before using "<code>".` |
| Someone is logged in and the code is `login` | `Error: already logged in. Log out before logging in again.` |
| The account type may not use the transaction | `Error: your account type cannot use "<code>".` |

No prompt is shown in any of these cases. Who may use what:

| Transaction | Allowed account types |
| --- | --- |
| create, delete, refund, list_accounts | admin (AA) only |
| sell | admin, full-standard, sell-standard (not buy-standard) |
| buy | admin, full-standard, buy-standard (not sell-standard) |
| logout, addcredit, list_games, search | every type |

## Transactions

### login

- Prompt: `Enter username:`
- Check: the username belongs to an account in the accounts file (a blank username never does) -> `Error: "<username>" is not a registered user.`
- Success: `Login successful. Welcome, <username> (<AA|FS|BS|SS>).`

### logout

- Success: `Logout successful.`
- Only if the transaction file cannot be written: `Error: could not write the daily transaction file.`

### create (admin)

- Prompts: `Enter new username:` then `Enter account type (admin, full-standard, buy-standard, sell-standard):`
- Checks, in order:
    1. `Error: username must be 1 to 15 characters, with no space at the start or end.`
    2. `Error: username "<username>" already exists.`
    3. `Error: "<type>" is not a valid account type.`
- Success: `Account created: <username> (<AA|FS|BS|SS>) with 0.00 credit.`

### delete (admin)

- Prompt: `Enter username to delete:`
- Checks, in order:
    1. `Error: "<username>" is not a registered user.`
    2. `Error: you cannot delete your own account.`
- Success: `Account deleted: <username>.`

### sell (not buy-standard)

- Prompts: `Enter game name:` then `Enter price:`
- Checks, in order:
    1. `Error: game name must be 1 to 26 characters, with no space at the start or end.`
    2. `Error: a game named "<game>" is already for sale.` (also when it was listed earlier this session)
    3. `Error: price must be an amount from 0.00 to 999.99.`
- Success: `Game listed: <game> for <price>.`

### buy (not sell-standard)

- Prompts: `Enter game name:` then `Enter seller's username:`
- Checks, in order:
    1. `Error: "<game>" is not for sale by "<seller>".` (also for games listed this session, and games of accounts deleted this session)
    2. `Error: you cannot buy your own game.`
    3. `Error: you already own "<game>".`
    4. `Error: not enough credit to buy "<game>".`
- Success: `Purchase successful: <game> from <seller> for <price>.`

### refund (admin)

- Prompts: `Enter buyer's username:`, then `Enter seller's username:`, then `Enter refund amount:`
- Checks, in order:
    1. Buyer has no account: `Error: "<buyer>" is not a registered user.`
    2. Seller has no account: `Error: "<seller>" is not a registered user.`
    3. `Error: "<text>" is not a valid amount.`
    4. `Error: refund amount must be greater than 0.00.`
    5. `Error: seller "<seller>" does not have enough credit for this refund.`
- Success: `Refund successful: <amount> moved from <seller> to <buyer>.`

### addcredit (every type)

- Prompts: `Enter amount of credit to add:` then, for an admin only, `Enter username to credit:`
- Checks, in order:
    1. `Error: "<text>" is not a valid amount.`
    2. `Error: amount must be greater than 0.00.`
    3. Admin only, no such account: `Error: "<username>" is not a registered user.`
    4. `Error: at most 1000.00 can be added to an account in one session.`
    5. `Error: the balance cannot exceed 999999.99.`
- Success: `Credit added: <amount> to <username>.` (a non-admin always credits their own account)

### list_games (every type)

- Prints `Games available for purchase:` then one line per game for sale, in name order: the game name padded with spaces to 26 characters, one space, the seller padded to 15 characters, one space, the price.
- No games for sale: `No games are available for purchase.`

### list_accounts (admin)

- Prints `Active accounts:` then one line per account in this session, in username order: the username padded to 15 characters, one space, the type code, one space, the credit.
- Accounts created this session are included; accounts deleted this session are not.

### search (every type)

Client change: "Add a new transaction SEARCH that outputs all items and all users whose name contain the search query. If the user is not an administrator, this transaction should not output any names of administrators who are not selling games."

- Prompt: `Enter search text:`
- Check: blank text -> `Error: search text cannot be blank.`
- Prints `Games matching "<text>":` then every game for sale whose name contains the text, in the list_games line format and name order. If no game matches, it prints only `No games match "<text>".`
- Then prints `Users matching "<text>":` then every username that contains the text, one per line, in username order. If no user matches, it prints only `No users match "<text>".`
- A non-admin never sees the name of an admin account that has no game for sale. An admin sees every match.
- Writes nothing to the daily transaction file.
- Pending the client's answers: "items" means games for sale, and matching is case-sensitive.

## Worked examples

`buy_01` (FullUser buys Minecraft from Seller1):

```text
Enter username:
Login successful. Welcome, FullUser (FS).
Enter game name:
Enter seller's username:
Purchase successful: Minecraft from Seller1 for 50.00.
Logout successful.
```

`list_games_01` (FullUser lists the shared games):

```text
Enter username:
Login successful. Welcome, FullUser (FS).
Games available for purchase:
ExistingGame               Seller1         25.00
Minecraft                  Seller1         50.00
Portal                     Seller2         40.00
Terraria                   Seller3         30.00
Logout successful.
```
