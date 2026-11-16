"""Transaction 00: end of one Front End session."""
from __future__ import annotations

from state.system_state import SystemState
from transactions.transaction import Transaction


class EndOfSessionTransaction(Transaction):
    """Record 00: marks the end of one Front End session (and, as the last line, the end of the merged file); it changes nothing, so every record is handled the same way."""

    CODE = "00"

    def code(self) -> str:
        """Returns "00"."""
        return self.CODE

    def validate(self, state: SystemState) -> str:
        """Never fails: returns an empty string."""
        return ""

    def apply(self, state: SystemState) -> None:
        """Changes nothing."""
