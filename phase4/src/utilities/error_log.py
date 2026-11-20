"""Terminal error reporting."""
from __future__ import annotations


class ErrorLog:
    """Writes every Back End error to the terminal in the form ERROR: <msg> and counts them."""

    FAILED_CONSTRAINT = "Failed constraint"
    FATAL = "Fatal input error"

    def __init__(self) -> None:
        """Starts with no errors logged."""
        self._count = 0

    def failed_constraint(self, description: str, record: str) -> None:
        """Prints ERROR: Failed constraint: <description> (transaction: <record>) and counts it."""
        print(f"ERROR: {self.FAILED_CONSTRAINT}: {description} (transaction: {record})")
        self._count += 1

    def fatal(self, description: str, file_name: str) -> None:
        """Prints ERROR: Fatal input error: <description> (file: <file_name>) and counts it."""
        print(f"ERROR: {self.FATAL}: {description} (file: {file_name})")
        self._count += 1

    def count(self) -> int:
        """Returns how many errors have been logged in this run."""
        return self._count
