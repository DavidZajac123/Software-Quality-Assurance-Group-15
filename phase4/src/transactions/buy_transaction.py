"""Transaction 04: buy a game that is for sale."""
from __future__ import annotations

from state.system_state import SystemState
from transactions.transaction import Transaction


class BuyTransaction(Transaction):
    """Record 04: moves the price from the buyer to the seller and adds the game to the buyer's collection, provided the buyer's balance cannot go negative (business constraint)."""

    CODE = "04"

    def __init__(self, record: str, game_name: str, seller: str, buyer: str, price_cents: int) -> None:
        """Keeps the record, the game name, the seller's and buyer's usernames and the price in cents."""
        super().__init__(record)
        self._game_name = game_name
        self._seller = seller
        self._buyer = buyer
        self._price_cents = price_cents

    def code(self) -> str:
        """Returns "04"."""
        return self.CODE

    def validate(self, state: SystemState) -> str:
        """Fails when the buyer or the seller has no account, the buyer already owns the game, or the buyer's credit is less than the price."""
        raise NotImplementedError

    def apply(self, state: SystemState) -> None:
        """Subtracts the price from the buyer, adds it to the seller, and adds the game to the buyer's collection."""
        raise NotImplementedError
