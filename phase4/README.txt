Phase 4 - Back End Rapid Prototype - Group 15 (Raihan Mosharrof, David Zajac, Sanjith Krishnamoorthy)

Status: first version. It is meant to run on the sample data and nothing more; testing is Phase 5.

How to run: see the comment at the top of src/backend.py.

Folders
  src/            Python 3 source: one class per file, one folder per package
                  (control, transactions, state, fileio, utilities)
  sample_data/    one set of old master files and one merged daily transaction file for the smoke run
  design/         the design document and its figures
  sample_output/  where the example command writes the new master files (not committed)

Who owns what (each package is one branch and one pull request)
  Raihan   control, utilities/error_log.py, utilities/fatal_input_error.py, design document
  David    fileio, utilities/money.py, utilities/fixed_width_format.py
  Sanjith  transactions, state

Rule for the skeleton: declarations, constants, constructors and one-line methods are written;
every method with real logic raises NotImplementedError until its owner fills it in.

Decisions of this first version
  B1  Money is handled in whole cents (int), never floating point (as the Front End does).
  B2  A transaction that fails a constraint is reported as
      ERROR: Failed constraint: <description> (transaction: <record>)
      and skipped; the batch continues with the next record.
  B3  A record that names a user or game that does not exist is a failed constraint, not a fatal error (to confirm with the TA).
  B4  A malformed line, an unknown code or a missing END line is fatal:
      ERROR: Fatal input error: <description> (file: <name>), exit status 1, no new file written.
  B5  delete removes the account, its games for sale and its collection entries (Phase 2 decision D25).
  B6  refund moves credit only; the collection is unchanged until the TA answers R4 (phase3/Phase3_Failure_Log.md).
  B7  Account type AM (Account Manager, client change of 10 November 2026) is accepted wherever a type is read or written.
  B8  The field widths of the daily transaction file live in TransactionFileReader only (game 26, username 15),
      so another group's Front End is a one-class change.
  B9  The credit field of a 06 record is the amount added, as our Front End writes it (Phase 2 decision D15) and as
      Front End B writes it (checked in its FileManager.cpp).
  B10 The new master files end with a bare END line, as the Front End B files do; the reader accepts END alone or
      padded with spaces to the record width (our Phase 1 data pads it).
  B11 The 2-character type field of the 02, 06 and 00 records is read but never used or compared with the account: the
      specification and Front End B write the account type there, our Front End leaves it blank, and the Back End finds
      the account by username. Only 01 uses its type (AA, FS, BS, SS or AM).
  B12 The credit field of a 02 record is read but never used: our Front End writes 000000.00 and Front End B writes the
      deleted user's balance; the Back End deletes the account whatever the field holds.
  B13 Input files may end their lines with LF or CRLF; the new master files are written with LF only.

Known limitations of this first version
  L1  Account type AM: the Back End reads, keeps and writes it (B7), but Front End B does not recognize it yet;
      the Front End update is planned for Phase 5.

Smoke run: expected result of the example command, written before the code (the oracle is not the program)
  Terminal (two lines):
    ERROR: Failed constraint: buyer Buyer1 has 20.00, price is 50.00 (transaction: 04 Minecraft ... Buyer1 ... 050.00)
    ERROR: Failed constraint: username FullUser already exists (transaction: 01 FullUser ... BS 000000.00)
  New accounts:  AdminUser AA 1000.00; FullUser FS 200.00; Buyer1 BS 50.00; NewUser FS 0.00  (Seller1 deleted)
  New games:     Terraria FullUser 10.00; Portal FullUser 20.00  (Minecraft removed with Seller1)
  New collection: Terraria Buyer1
  Exit status 0.
