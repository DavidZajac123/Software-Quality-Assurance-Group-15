"""Transaction 04: buy a game that is for sale."""
from __future__ import annotations

from state.system_state import SystemState
from transactions.transaction import Transaction
from state.owned_game import OwnedGame


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
        buyer_account = state.find_account(self._buyer)
        if buyer_account is None:
            return f"Buyer '{self._buyer}' does not exist."
        if state.find_account(self._seller) is None:
            return f"Seller '{self._seller}' does not exist."
        if state.owns_game(self._buyer, self._game_name):
            return f"Buyer '{self._buyer}' already owns '{self._game_name}'."
        if buyer_account.credit_cents < self._price_cents:
            return f"Buyer '{self._buyer}' has insufficient credit."
        return ""

    def apply(self, state: SystemState) -> None:
        """Subtracts the price from the buyer, adds it to the seller, and adds the game to the buyer's collection."""
        state.change_credit(self._buyer, -self._price_cents)
        state.change_credit(self._seller, self._price_cents)
        new_owned_game = OwnedGame(
            game_name=self._game_name,
            owner=self._buyer
        )
        state.add_owned_game(new_owned_game)