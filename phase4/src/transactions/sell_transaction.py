"""Transaction 03: put a game up for sale."""
from __future__ import annotations

from state.system_state import SystemState
from transactions.transaction import Transaction


class SellTransaction(Transaction):
    """Record 03: adds a game, its seller and its price to the games for sale, so it can be bought from the next day on."""

    CODE = "03"

    def __init__(self, record: str, game_name: str, seller: str, price_cents: int) -> None:
        """Keeps the record, the game name, the seller's username and the price in cents."""
        super().__init__(record)
        self._game_name = game_name
        self._seller = seller
        self._price_cents = price_cents

    def code(self) -> str:
        """Returns "03"."""
        return self.CODE

    def validate(self, state: SystemState) -> str:
        """Fails when the seller has no account or a game with this name is already for sale."""
        if state.find_account(self._seller) is None:
            return f"Seller '{self._seller}' does not exist."
        if state.find_listing(self._game_name) is not None:
            return f"Game listing '{self._game_name}' already exists."
        return ""

    def apply(self, state: SystemState) -> None:
        """Adds the listing to the state."""
        temp_listing = state.add_listing.__annotations__["listing"]
        new_listing = temp_listing(
            game_name=self._game_name,
            seller=self._seller,
            price_cents=self._price_cents
        )
        state.add_listing(new_listing)