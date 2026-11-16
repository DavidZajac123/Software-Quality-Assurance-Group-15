"""Transaction 01: create a user account."""
from __future__ import annotations

from state.system_state import SystemState
from state.user_type import UserType
from transactions.transaction import Transaction


class CreateTransaction(Transaction):
    """Record 01: adds a new account with the given username and account type and 0.00 credit, provided the username differs from every existing user (business constraint)."""

    CODE = "01"

    def __init__(self, record: str, username: str, user_type: UserType) -> None:
        """Keeps the record, the new username and the account type."""
        super().__init__(record)
        self._username = username
        self._user_type = user_type

    def code(self) -> str:
        """Returns "01"."""
        return self.CODE

    def validate(self, state: SystemState) -> str:
        """Fails when an account with this username already exists."""
        raise NotImplementedError

    def apply(self, state: SystemState) -> None:
        """Adds the account to the state with 0.00 credit."""
        raise NotImplementedError
