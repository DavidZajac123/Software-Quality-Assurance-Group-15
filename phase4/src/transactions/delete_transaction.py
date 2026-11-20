"""Transaction 02: delete a user account."""
from __future__ import annotations

from state.system_state import SystemState
from transactions.transaction import Transaction


class DeleteTransaction(Transaction):
    """Record 02: removes an existing account together with its games for sale and its collection entries (Phase 2 decision D25)."""

    CODE = "02"

    def __init__(self, record: str, username: str) -> None:
        """Keeps the record and the username to delete."""
        super().__init__(record)
        self._username = username

    def code(self) -> str:
        """Returns "02"."""
        return self.CODE

    def validate(self, state: SystemState) -> str:
        """Fails when no account with this username exists."""
        if state.find_account(self._username) is None:
            return f"User '{self._username}' does not exist."
        return ""

    def apply(self, state: SystemState) -> None:
        """Removes the account, its listings and its owned games from the state."""
        state.remove_account(self._username)
