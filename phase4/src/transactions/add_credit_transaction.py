"""Transaction 06: add credit to an account."""
from __future__ import annotations

from state.system_state import SystemState
from transactions.transaction import Transaction


class AddCreditTransaction(Transaction):
    """Record 06: adds an amount of credit to an existing account; the credit field of the record is the amount added (decision B9)."""

    CODE = "06"

    def __init__(self, record: str, username: str, amount_cents: int) -> None:
        """Keeps the record, the username and the amount in cents."""
        super().__init__(record)
        self._username = username
        self._amount_cents = amount_cents

    def code(self) -> str:
        """Returns "06"."""
        return self.CODE

    def validate(self, state: SystemState) -> str:
        """Fails when no account with this username exists."""
        if state.find_account(self._username) is None:
            return f"User '{self._username}' does not exist."
        return ""

    def apply(self, state: SystemState) -> None:
        """Adds the amount to the account's credit."""
        state.change_credit(self._username, self._amount_cents)
