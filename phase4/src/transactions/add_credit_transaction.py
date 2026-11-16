"""Transaction 06: add credit to an account."""
from __future__ import annotations

from state.system_state import SystemState
from transactions.transaction import Transaction


class AddCreditTransaction(Transaction):
    """Record 06: adds an amount of credit to an existing account; the record holds the amount added, as our Front End writes it (Phase 2 decision D15)."""

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
        raise NotImplementedError

    def apply(self, state: SystemState) -> None:
        """Adds the amount to the account's credit."""
        raise NotImplementedError
