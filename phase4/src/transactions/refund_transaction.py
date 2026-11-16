"""Transaction 05: refund credit from a seller to a buyer."""
from __future__ import annotations

from state.system_state import SystemState
from transactions.transaction import Transaction


class RefundTransaction(Transaction):
    """Record 05: moves an amount of credit from the seller's account to the buyer's account, provided the seller's balance cannot go negative (business constraint); the collection is left unchanged until open question R4 is answered."""

    CODE = "05"

    def __init__(self, record: str, buyer: str, seller: str, amount_cents: int) -> None:
        """Keeps the record, the buyer's and seller's usernames and the amount in cents."""
        super().__init__(record)
        self._buyer = buyer
        self._seller = seller
        self._amount_cents = amount_cents

    def code(self) -> str:
        """Returns "05"."""
        return self.CODE

    def validate(self, state: SystemState) -> str:
        """Fails when the buyer or the seller has no account, or the seller's credit is less than the amount."""
        raise NotImplementedError

    def apply(self, state: SystemState) -> None:
        """Subtracts the amount from the seller and adds it to the buyer."""
        raise NotImplementedError
