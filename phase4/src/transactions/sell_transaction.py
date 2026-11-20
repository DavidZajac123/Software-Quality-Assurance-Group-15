"""Transaction 03: put a game up for sale."""
from __future__ import annotations

from state.system_state import SystemState
from transactions.transaction import Transaction
from state.game_listing import GameListing

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
        buyer_account = state.find_account(self._buyer)
        seller_account = state.find_account(self._seller)

        if buyer_account is None:
            return f"Buyer '{self._buyer}' does not exist."
        if seller_account is None:
            return f"Seller '{self._seller}' does not exist."
        if seller_account.credit_cents < self._amount_cents:
            return f"Seller '{self._seller}' credit is less than the amount of the game."
        return ""

    def apply(self, state: SystemState) -> None:
        """Adds the listing to the state."""
        new_listing = GameListing(
            game_name=self._game_name,
            seller=self._seller,
            price_cents=self._price_cents
        )
        state.add_listing(new_listing)