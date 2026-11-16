"""Control: one overnight batch run."""
from __future__ import annotations

from control.file_set import FileSet
from fileio.master_file_reader import MasterFileReader
from fileio.master_file_writer import MasterFileWriter
from fileio.transaction_file_reader import TransactionFileReader
from state.system_state import SystemState
from transactions.transaction import Transaction
from utilities.error_log import ErrorLog
from utilities.fatal_input_error import FatalInputError

EXIT_OK = 0
EXIT_FATAL = 1


class BackEnd:
    """Runs one overnight batch: loads the old master files, applies every transaction of the merged daily transaction file in order, logs each failed constraint, and writes the new master files."""

    def __init__(self, files: FileSet, error_log: ErrorLog) -> None:
        """Keeps the file names and the error log, and creates the reader and writer objects the run will use."""
        self._files = files
        self._error_log = error_log
        self._master_reader = MasterFileReader()
        self._transaction_reader = TransactionFileReader()
        self._master_writer = MasterFileWriter()

    def run(self) -> int:
        """Performs the whole batch and returns the exit status: 0 when it completes, 1 when a fatal input error stops it before any new file is written."""
        try:
            state = self._load_state()
            transactions = self._transaction_reader.read(self._files.merged_transactions)
        except FatalInputError as error:
            self._error_log.fatal(error.description, error.file_name)
            return EXIT_FATAL
        self._apply_all(transactions, state)
        self._write_state(state)
        return EXIT_OK

    def _load_state(self) -> SystemState:
        """Reads the three old master files and returns them as one SystemState."""
        raise NotImplementedError

    def _apply_all(self, transactions: list[Transaction], state: SystemState) -> None:
        """Validates and applies each transaction in file order; one that fails a constraint is logged with its record and skipped, and the batch continues."""
        raise NotImplementedError

    def _write_state(self, state: SystemState) -> None:
        """Writes the accounts, listings and collection of the state to the three new master files."""
        raise NotImplementedError
